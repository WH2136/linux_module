#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/workqueue.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
typedef struct {
	struct	work_struct work;
	int	data;
} work_t;

static work_t *my_work_t;

/** This is the workqueue handler function - a deferred function **/
static void ework_handler(struct work_struct *pwork);

/** Declare the workqueue struct **/
static struct workqueue_struct *eWq = NULL;

static void ework_handler(struct work_struct *pwork)
{
	work_t *temp;
	temp = container_of(pwork, work_t, work);
	printk("The ework_handler...called\r\n");
	printk("the value of data is : %d\r\n", temp->data);
}

static int __init eworkqueue_init(void)
{
	printk("Hello eWorkqueue !!! Welcome!!\r\n");	
	printk("Create work struct object!!\r\n");
	my_work_t = (work_t *)kmalloc(sizeof(work_t), GFP_KERNEL);
	my_work_t->data = 100;
	eWq = create_singlethread_workqueue("eWorkqueue");
	INIT_WORK(&(my_work_t->work), ework_handler);
	queue_work(eWq, &(my_work_t->work));

	return 0;
}

static void __exit eworkqueue_exit(void)
{
	/* clean workqueue */
	flush_workqueue(eWq);
	destroy_workqueue(eWq);
	kfree(my_work_t);
	printk("GoodBye..WorkQueue");
}

module_init(eworkqueue_init);
module_exit(eworkqueue_exit);
