#include <linux/module.h>
#include <linux/printk.h>
#include "mylist.h"
#include <linux/slab.h>

/*
 * Undefine commonly used macros -- DO NOT MODIFY
 * Please also do not use other macros and functions defined in <linux/list.h>,
 * such as INIT_LIST_HEAD, list_add, list_add_tail, list_del, list_empty,
 * or any of the internal helper functions beginning with __.
 */
#undef LIST_HEAD
#undef LIST_HEAD_INIT
#undef list_entry
#undef list_for_each_entry
#undef list_for_each_entry_safe
#undef container_of
#undef offsetof
#undef READ_ONCE
#undef WRITE_ONCE



struct pokemon {
	char name[32];
	int dex_no;
	struct list_head list;
};

static my_LIST_HEAD(pokedex);

void print_pokemon(struct pokemon *p)
{
	printk(KERN_INFO "%s: National Dex No. #%d\n", p->name, p->dex_no);
}

/* TODO: declare a single static struct list_head, named pokedex */

void add_pokemon(char *name, int dex_no)
{
	/* TODO: write your code here */
	struct pokemon * new_poke;
	new_poke = kmalloc(sizeof(*new_poke), GFP_KERNEL);
	new_poke->dex_no = dex_no;
	strcpy(new_poke->name, name);
	my_INIT_LIST_HEAD(&new_poke->list);

	my_list_add_tail(&new_poke->list, &pokedex);
}

void print_pokedex(void)
{
	/* TODO: write your code here, using print_pokemon() */
	struct pokemon * temp; 
	my_list_for_each_entry(temp, &pokedex, list) {
		print_pokemon(temp);
	}
}

void delete_pokedex(void)
{
	/* TODO: write your code here */
	struct pokemon * curr, * next; 
	my_list_for_each_entry_safe(curr, next, &pokedex, list) {
		list_del(&curr->list);
		kfree(curr);
	}
}

int pokedex_init(void)
{
	printk(KERN_INFO "Loading Module\n");

	add_pokemon("Porygon-Z", 474);
	add_pokemon("Exeggutor", 103);
	add_pokemon("Poliwhirl", 61);
	add_pokemon("Infernape", 392);

	print_pokedex();

	return 0;
}

void pokedex_exit(void)
{
	printk(KERN_INFO "Removing Module\n");

	print_pokedex();

	delete_pokedex();
}

module_init( pokedex_init );
module_exit( pokedex_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A handy Pokedex module");
MODULE_AUTHOR("SGG");