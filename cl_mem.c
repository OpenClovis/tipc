#include <linux/ktime.h>
#include <linux/timer.h>
#include <linux/skbuff.h>
#include <linux/vmalloc.h>
#include "core.h"


// The Linux net memory subsystem is not capable of allocating new memory
// when in interrupt context.  This can lead to TIPC packet drops if
// the net layer runs out of sk_buffs and TIPC requests one in interrupt
// context.  This code creates a dedicated pool of sk_buff memory
// to be used if the linux network sk_buff allocation fails.

// We replenish the dedicated sk_buff pool every second.


struct sk_buff *tipc_alloc_skb(u32 size)
{
	struct sk_buff *skb;
	unsigned int buf_size = (BUF_HEADROOM + size + 3) & ~3u;
    
	skb = alloc_skb_fclone(buf_size, GFP_ATOMIC);
    
	return skb;
}


#if 0
void kfree_skb_list(struct sk_buff *segs)
{
	while (segs) {
		struct sk_buff *next = segs->next;

		kfree_skb(segs);
		segs = next;
	}
}
#endif

#ifdef TIPC_LOCAL_MEM_MGMT

// struct sk_buff_head tipc_mem_mgmt_queue_head;
static struct timer_list internal_buffer_timer;

#define REPLENISH_INTERVAL 100L
#define MS_TO_NS(x)	(x * 1E6L)

// Number of buffer groups.  This MUST correspond to the size of the next 2 arrays
#define tipc_dedicated_buffer_groups 4

// The size in bytes of buffers to reserve, ordered smallest first
unsigned int tipc_dedicated_buf_sizes[tipc_dedicated_buffer_groups] = 
{
    // ctrl msgs, eth frame size, a likely size, tipc max size
    256, 1530, 10000, (( TIPC_MAX_USER_MSG_SIZE + BUF_HEADROOM + 3) & ~3u)
};

// The number of buffers to reserve of each size
unsigned int tipc_dedicated_buf_counts[tipc_dedicated_buffer_groups] = 
{
    500, 200, 100, 50
};

struct sk_buff_head tipc_dedicated_bufs[tipc_dedicated_buffer_groups];

    
static void tipc_dedicated_buf_replenish(void)
{
    unsigned int grp;
    unsigned int index;
	struct sk_buff *skb;
    
    for (grp = 0; grp < tipc_dedicated_buffer_groups; grp++)
    {
      unsigned int curlen =   skb_queue_len(&tipc_dedicated_bufs[grp]);
        
	  if (curlen <= (tipc_dedicated_buf_counts[grp]/2))
      {
		for(index = curlen; index < tipc_dedicated_buf_counts[grp]; index++)
        {
			skb = tipc_alloc_skb(tipc_dedicated_buf_sizes[grp]);  // tipc_buf_acquire(MAX_TIPC_PACKET_FRAME_SIZE);
			if (skb)
            {
				skb_queue_tail(&tipc_dedicated_bufs[grp], skb);
            }
            else
            {
                printk( "Unable to replenish TIPC dedicated message buffers");
                break;  // No memory to get
            }
        }
      }        
    }  
}


static void tipc_mem_mgmt_timer_callback(unsigned long data)
{
	//printk( "TIPC Internal Memory Mgmnt timer called at time (%ld), data(%ld).\n", jiffies, data );
    tipc_dedicated_buf_replenish();    
	mod_timer(&internal_buffer_timer, jiffies + REPLENISH_INTERVAL);
}

void tipc_mem_mgmt_timer_start()
{
    init_timer(&internal_buffer_timer);
    internal_buffer_timer.function = tipc_mem_mgmt_timer_callback;
    internal_buffer_timer.data = 1UL;
    internal_buffer_timer.expires = jiffies + REPLENISH_INTERVAL;
    add_timer(&internal_buffer_timer);
}

void tipc_mem_mgmt_timer_stop()
{
	del_timer_sync(&internal_buffer_timer);
}

struct sk_buff  *tipc_mem_mgmt_get_buf(u32 size)
{
    unsigned int grp;
    
    // printk( "Using TIPC dedicated message buffer size [%d]\n",size);

    if (size > tipc_dedicated_buf_sizes[tipc_dedicated_buffer_groups-1])
    {
        printk( "Allocation of [%d] is too big.  We have [%d]\n", size, tipc_dedicated_buf_sizes[tipc_dedicated_buffer_groups-1]);
        return NULL;
    }
    
    for (grp = 0; grp < tipc_dedicated_buffer_groups; grp++)
    {
        if (size <= tipc_dedicated_buf_sizes[grp]) // If the allocation will fit in this size buffer, then grab from this list
        {
          struct sk_buff *skb = skb_dequeue(&tipc_dedicated_bufs[grp]);  // returns NULL if empty
          if (skb) return skb;
        }            
    }
    
    printk("TIPC dedicated buffer queue is empty for size [%d]", size);
    return NULL;
}

#if 0  // not going to work, need to clear the internal skb structure before putting it back on a list
void tipc_mem_mgmt_free_buf(struct sk_buff *skb)
{
	if (skb) {
		skb_queue_tail(&tipc_mem_mgmt_queue_head, skb);
	}
}
#endif

void tipc_mem_mgmt_init(void)
{
    unsigned int grp;
    
    
    // zero out the dedicated buffer lists
    for (grp = 0; grp < tipc_dedicated_buffer_groups; grp++)
    {
        skb_queue_head_init(&tipc_dedicated_bufs[grp]);
        //tipc_dedicated_bufs[grp].next = tipc_dedicated_bufs[grp].prev = (struct sk_buff *)&tipc_dedicated_bufs[grp];
    }
    // fill them up
    tipc_dedicated_buf_replenish();

    // set up periodic timer to replenish them
	tipc_mem_mgmt_timer_start();
}

void tipc_mem_mgmt_stop(void)
{
    unsigned int grp;
    
    // stop the buffer replenish timer
	tipc_mem_mgmt_timer_stop();

    // Clean up all unused buffers
    for (grp = 0; grp < tipc_dedicated_buffer_groups; grp++)
    {
        skb_queue_purge(&tipc_dedicated_bufs[grp]);   
    }
}
#endif
