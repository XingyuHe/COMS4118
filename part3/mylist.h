#include <linux/types.h>
/* 
struct list_head {
	struct list_head *next, *prev;
};

note that list head needs to have the pointer to the 
previous list head and a pointer to the later list head 

*/


#define my_LIST_HEAD_INIT(name) {&(name), &(name)}

/**
 * my_LIST_HEAD - return a list_head struct with the name @name
 * @name:      the name of the list_head
 * 
 * When list_head is initialized, there is no prev or next since it's circular
 */
#define my_LIST_HEAD(name) \
    struct list_head name = my_LIST_HEAD_INIT(name)


/**
 * my_offsetof - find the difference a struct and its member
 * @type:      the type of the struct
 * @member:    the name of the member inside the struct
 */

#define my_offsetof(type, member) \
    ((size_t) &((type *) 0)->member)

/**
 * my_container_of - get the structure that contains the member
 * @ptr:       pointer to the member
 * @type:      the type of the struct
 * @member:    the name of the member inside the struct
 */
#define my_container_of(ptr, type, member) ({ \
    void * __mptr = (void *) (ptr);     \
    ((type *) (__mptr - my_offsetof(type, member))); \
})

/**
 * my_list_entry - get the structure that contains the list_head
 * @ptr:       pointer to the list_head
 * @type:      the type of the struct
 * @member:    the name of the list_head inside the struct
 */
#define my_list_entry(ptr, type, member) \
    my_container_of(ptr, type, member)
    
/**
 * my_list_first_entry - get the first entry of the linkedlist
 * @ptr:       pointer to the list_head
 * @type:      the type of the struct
 * @member:    the name of the list_head inside the struct
 */
#define my_list_first_entry(ptr, type, member) \
    my_list_entry((ptr)->next, type, member)

/**
 * my_list_entry_is_head - check if the entry point points to the head of the list
 * @ptr:       pointer to the list_head
 * @type:      the type of the struct
 * @member:    the name of the list_head inside the struct
 */
#define my_list_entry_is_head(pos, head, member) \
    (&pos->member == (head))
    
/**
 * my_list_next_entry - find the next entry after the current entry
 * @pos:        type * to use as a loop cursor
 * @member:     the name of the list_head in entry
 */
#define my_list_next_entry(pos, member) \
    my_list_entry((pos)->member.next, typeof(*(pos)), member)

/**
 * my_list_for_each_entry - itereate through each entry in a list_head
 * @pos:        type * to use as a loop cursor 
 * @head:       the head of the list
 * @member:     the name of the list_head in entry
 */
#define my_list_for_each_entry(pos, head, member) \
    for (pos = my_list_first_entry(head, typeof(*pos), member);  \
        !my_list_entry_is_head(pos, head, member); \
        pos = my_list_next_entry(pos, member))

/**
 * my_list_for_each_entry - itereate through each entry in a list_head safely against deletion
 * @pos:        type * to use as a loop cursor 
 * @n:          another type * to use as a loop cursor that points the next entry
 * @head:       the head of the list
 * @member:     the name of the list_head in entry
 */
#define my_list_for_each_entry_safe(pos, n, head, member) \
    for (pos = my_list_first_entry(head, typeof(*pos), member), \
        n = my_list_next_entry(pos, member); \
        !my_list_entry_is_head(pos, head, member); \
        pos = n,  \
        n = my_list_next_entry(n, member))


static inline void __my_list_add(struct list_head *new, struct list_head *prev, struct list_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    WRITE_ONCE(prev->next, new);
}

static inline void my_list_add_tail(struct list_head *new, struct list_head *head)
{
    __my_list_add(new, head->prev, head);
}

static inline void my_INIT_LIST_HEAD(struct list_head *list)
{
    WRITE_ONCE(list->next, list);
    list->prev = list;
}
