#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

MODULE_INFO(intree, "Y");

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x568fba06, "module_layout" },
	{ 0x9462734, "release_sock" },
	{ 0xdce16e04, "kmem_cache_destroy" },
	{ 0x5a34a45c, "__kmalloc" },
	{ 0xf76003d, "sock_init_data" },
	{ 0x349cba85, "strchr" },
	{ 0x3fa913da, "strspn" },
	{ 0x39b5bc38, "genl_unregister_family" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0x79aa04a2, "get_random_bytes" },
	{ 0x344bf2c0, "sock_no_ioctl" },
	{ 0x4d884691, "malloc_sizes" },
	{ 0xc01cf848, "_raw_read_lock" },
	{ 0x1637ff0f, "_raw_spin_lock_bh" },
	{ 0xb53c5051, "skb_clone" },
	{ 0x16d36caf, "skb_copy" },
	{ 0xf89843f9, "schedule_work" },
	{ 0x63ecad53, "register_netdevice_notifier" },
	{ 0xf32055e7, "dev_base_lock" },
	{ 0x6729d3df, "__get_user_4" },
	{ 0xfb0e29f, "init_timer_key" },
	{ 0x999e8297, "vfree" },
	{ 0x91715312, "sprintf" },
	{ 0x7d11c268, "jiffies" },
	{ 0xfe769456, "unregister_netdevice_notifier" },
	{ 0x3f1a803f, "skb_trim" },
	{ 0xe2d5255a, "strcmp" },
	{ 0xb05e87ce, "sock_no_sendpage" },
	{ 0x760a4192, "__pskb_pull_tail" },
	{ 0x80fe590d, "sock_no_mmap" },
	{ 0x71de9b3f, "_copy_to_user" },
	{ 0xd5f2172f, "del_timer_sync" },
	{ 0xe679b8f2, "sock_no_socketpair" },
	{ 0xf3d18871, "sk_alloc" },
	{ 0xdc8d1dde, "_raw_spin_trylock_bh" },
	{ 0x9021c4eb, "current_task" },
	{ 0x27e1a049, "printk" },
	{ 0x42224298, "sscanf" },
	{ 0x8ee5232f, "lock_sock_nested" },
	{ 0x2fa5a500, "memcmp" },
	{ 0xfaef0ed, "__tasklet_schedule" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0x7ec9bfbc, "strncpy" },
	{ 0x85abc85f, "strncmp" },
	{ 0xa14cb06d, "sock_no_listen" },
	{ 0x672144bd, "strlcpy" },
	{ 0xd4e45d05, "kmem_cache_free" },
	{ 0x16305289, "warn_slowpath_null" },
	{ 0xd9c8d495, "skb_push" },
	{ 0x4377b430, "sock_no_accept" },
	{ 0xdad8052c, "sk_free" },
	{ 0x704819ff, "dev_remove_pack" },
	{ 0x8834396c, "mod_timer" },
	{ 0xf699bae9, "netlink_unicast" },
	{ 0x394637c6, "genl_register_family_with_ops" },
	{ 0x86856070, "skb_pull" },
	{ 0x3775290c, "init_net" },
	{ 0x82072614, "tasklet_kill" },
	{ 0xc6cbbc89, "capable" },
	{ 0xfedaeb91, "proto_register" },
	{ 0x9f984513, "strrchr" },
	{ 0x190b27b, "kmem_cache_alloc" },
	{ 0xb2fd5ceb, "__put_user_4" },
	{ 0x9c0f1700, "__alloc_skb" },
	{ 0xba63339c, "_raw_spin_unlock_bh" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x3bd1b1f6, "msecs_to_jiffies" },
	{ 0x5b7661a7, "sock_register" },
	{ 0xd62c833f, "schedule_timeout" },
	{ 0x1000e51, "schedule" },
	{ 0xbb0ebf03, "kfree_skb" },
	{ 0x42c1d00d, "proto_unregister" },
	{ 0x6b2dc060, "dump_stack" },
	{ 0x43ec913a, "put_cmsg" },
	{ 0xfdd549e4, "pskb_expand_head" },
	{ 0x1057f529, "skb_copy_datagram_iovec" },
	{ 0x7a172b67, "kmem_cache_alloc_trace" },
	{ 0xd52bf1ce, "_raw_spin_lock" },
	{ 0xb14a346e, "kmem_cache_create" },
	{ 0xcf21d241, "__wake_up" },
	{ 0x5c3edd59, "_raw_write_unlock_bh" },
	{ 0x1e047854, "warn_slowpath_fmt" },
	{ 0xfdee7d42, "_raw_read_lock_bh" },
	{ 0xf37260ab, "_raw_read_unlock_bh" },
	{ 0xa9bd2676, "__vmalloc" },
	{ 0x37a0cba, "kfree" },
	{ 0x5c8b5ce8, "prepare_to_wait" },
	{ 0x62737e1d, "sock_unregister" },
	{ 0x32eeaded, "_raw_write_lock_bh" },
	{ 0xfa66f77c, "finish_wait" },
	{ 0x50720c5f, "snprintf" },
	{ 0xe6fdf77c, "dev_add_pack" },
	{ 0xa3a5be95, "memmove" },
	{ 0x2e9620c6, "dev_queue_xmit" },
	{ 0xfac00f33, "skb_put" },
	{ 0x77e2f33, "_copy_from_user" },
	{ 0x2937c70b, "skb_copy_bits" },
	{ 0x2482e688, "vsprintf" },
	{ 0xe914e41e, "strcpy" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "02706F207F28866453A7CC9");
