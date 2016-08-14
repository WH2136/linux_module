#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

/* 当模块被加载时执行该函数 */
static int hello_init(void) {
	printk(KERN_ALERT "hello world!\n");
	return 0;
}
/* 当模块被卸载时执行该函数 */
static void hello_exit(void) {
	printk(KERN_ALERT"Goodbye, beautiful world\n");
}

/*
 * module_init指定模块被加载的时候需要执行的函数
 * module_exit指定模块被卸载的时候需要执行的函数
 */
module_init(hello_init);
module_exit(hello_exit);
