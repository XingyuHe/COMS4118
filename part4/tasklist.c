#include <linux/module.h>
#include <linux/sched/task.h>

void depth_first_search(struct task_struct * curr_task, int curr_level)
{
	int num_spaces = 4 * min(curr_level, 20);
	struct task_struct * pos1;

	// Visit one's own node first
	if (curr_level != 0) {
		printk(KERN_INFO "%*s\\_ [%i] %s", num_spaces, " ", curr_task->pid, curr_task->comm);
	}

	// Go through all the children
	// Note that children is the list head, while sibling points to the next child of curr_task
	// In other words, list_head * children->next points the next sibling's list_head
	// curr_task -> children do not have any structure that embeds it
	list_for_each_entry(pos1, &curr_task->children, sibling) {
		depth_first_search(pos1, curr_level + 1);
	}
}

int tasklist_init(void)
{
	printk(KERN_INFO "Loading Module\n");
	printk(KERN_INFO "-- [%i] %s", init_task.pid, init_task.comm);
	depth_first_search(&init_task, 0);

	return 0;
}


void tasklist_exit(void)
{
	printk(KERN_INFO "Removing Module\n");
}

module_init( tasklist_init );
module_exit( tasklist_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Tasklist Module");
MODULE_AUTHOR("SGG");


