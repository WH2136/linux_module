#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/jiffies.h>

#define RDTSC(qp) \
do { \
	unsigned long lowPart, highPart; \
	__asm__ __volatile__("rdtsc" : "=a"(lowPart), "=d"(highPart)); \
	qp = (((unsigned long long) highPart) << 32) | lowPart; \
}while(0)

static struct tasklet_struct *tsk;

static void task_fn(unsigned long arg)
{
#if 0
	/* typedef unsigned long long u64 */
	u64	start, end;
	start = get_jiffies_64();
#endif
	unsigned long long	start = 0, end = 0;
	RDTSC(start);
	printk("calculating spend time...\r\n");
	RDTSC(end);
#if 0
	end = get_jiffies_64();
	printk("tsk spent time is %llu\r\n", end-start);
#endif
	printk("tsk spent time is %llu\r\n", end-start);
}

static int __init tsk_init(void)
{
	tsk = (struct tasklet_struct *)kmalloc(sizeof(struct tasklet_struct), GFP_KERNEL);
	tasklet_init(tsk, task_fn, 0);
	tasklet_schedule(tsk);

	return 0;
}

static void __exit tsk_exit(void)
{
	printk("Good bye!\r\n");
}

MODULE_LICENSE("GPL");
module_init(tsk_init);
module_exit(tsk_exit);
