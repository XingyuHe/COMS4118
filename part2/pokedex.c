#include <linux/module.h>
#include <linux/list.h>
#include <linux/printk.h>
#include <linux/slab.h>

struct pokemon {
	char name[32];
	int dex_no;
	struct list_head list;
};

static LIST_HEAD(pokedex);

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
	INIT_LIST_HEAD(&new_poke->list);

	list_add_tail(&new_poke->list, &pokedex);
}

void print_pokedex(void)
{
	/* TODO: write your code here, using print_pokemon() */
	struct pokemon * temp; 
	list_for_each_entry(temp, &pokedex, list) {
		print_pokemon(temp);
	}
}

void delete_pokedex(void)
{
	/* TODO: write your code here */
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
