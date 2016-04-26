#include <net/sock.h>

/*
 * Take into account size of receive queue and backlog queue
 * Do not take into account this skb truesize,
 * to allow even a single big packet to come.
 */
static inline bool cl_sk_rcvqueues_full(const struct sock *sk, const struct sk_buff *skb,
				     unsigned int limit)
{
	unsigned int qsize = sk->sk_backlog.len + atomic_read(&sk->sk_rmem_alloc);

	return qsize > limit;
}

/* The per-socket spinlock must be held here. */
static inline __must_check int cl_sk_add_backlog(struct sock *sk, struct sk_buff *skb, unsigned int limit)
{
	if (cl_sk_rcvqueues_full(sk, skb, limit))
		return -ENOBUFS;
    
	__sk_add_backlog(sk, skb);
	sk->sk_backlog.len += skb->truesize;
	return 0;
}
