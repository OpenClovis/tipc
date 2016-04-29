#define TIPC_LOCAL_MEM_MGMT

#ifdef TIPC_LOCAL_MEM_MGMT
#define MAX_ETH_FRAME_SIZE 1530
#define MAX_TIPC_PACKET_FRAME_SIZE  MAX_ETH_FRAME_SIZE
#define TIPC_MEM_MGMT_MAX_QUEUE_SIZE  500

extern void tipc_mem_mgmt_timer_stop(void);
extern void tipc_mem_mgmt_timer_start(void);
extern void kfree_skb_list(struct sk_buff *segs);
extern void tipc_mem_mgmt_stop(void);
extern void tipc_mem_mgmt_init(void);
// extern void tipc_mem_mgmt_free_buf(struct sk_buff *skb);

extern struct sk_buff  *tipc_mem_mgmt_get_buf(u32 size);

#endif
