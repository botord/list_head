/*************************************************************************
	> File Name: list_head.c
	> Author: 
	> Mail: 
	> Created Time: 2015年09月15日 星期二 15时44分15秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <linux/errno.h>

struct list_head {
    struct list_head *next, *prev;
};

#define INIT_LIST_HEAD(ptr) do {\
    (ptr)->next = (ptr); (ptr)->prev = (ptr); \
} while (0)

static inline void __list_add(struct list_head *list, struct list_head *prev,
                              struct list_head *next) {
    next -> prev = list;
    list -> next = next;
    list -> prev = prev;
    prev -> next = list;
}

static inline void list_add(struct list_head *list, struct list_head *head) {
    __list_add(list, head->prev, head);
}

static inline void list_add_tail(struct list_head *list, struct list_head *head) {
    __list_add(list, head->prev, head);
}

static inline void __list_del(struct list_head *prev, struct list_head *next) {
    next->prev = prev;
    prev->next = next;
}
static inline void list_del(struct list_head *entry){
   __list_del(entry->prev, entry->next); 
}

struct list_node {
    int val;
    struct list_head list;
};

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

/*calculate the offset of member*/
#define container_of(ptr, type, member) \
    ((type *)((void *)(ptr) - (unsigned long)(&((type *)0)->member)))

#define list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next) 

int main()
{
    struct list_head *head, *p;

    struct list_node a, b, c;

    a.val = 1;
    b.val = 2;
    c.val = 3;

    head = malloc(sizeof(struct list_head));

    if (!head) {
        return -ENOMEM;
    }
    INIT_LIST_HEAD(head);

    list_add_tail(&a.list, head);
    list_add_tail(&b.list, head);
    list_add_tail(&c.list, head);

    list_for_each(p, head) {
        struct list_node *node = list_entry(p, struct list_node, list);
        /* get the upper list_node through list_head pointer 
          #define list_entry(ptr, type, member) container_of(ptr, type, member)
        */
        printf("val = %d\n", node->val);
    }

    struct list_node d, e;
    d.val = 4;
    e.val = 5;

    list_add_tail(&d.list, head);
    list_add_tail(&e.list, head);

    list_for_each (p, head) {
        struct list_node *node = list_entry(p, struct list_node, list);
        printf("val = %d\n", node->val);
    }

    return 0;
}
