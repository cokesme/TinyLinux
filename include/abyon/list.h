/*
 * include/abyon/list.h
 * Copyright (C) <2014>  <@RKX1209>
 */

#ifndef _ABYON_LIST_H
#define _ABYON_LIST_H

#define LIST_POISON1  ((void *) 0x00100100)
#define LIST_POISON2  ((void *) 0x00200200)

struct list_head{
struct list_head *next,*prev;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

#define INIT_LIST_HEAD(ptr) do {					\
(ptr)->next = (ptr); (ptr)->prev = (ptr); \
} while (0)

static inline void __list_add(struct list_head *add,
			      struct list_head *prev,
			      struct list_head *next){
  next->prev = add;
  add->next = next;
  add->prev = prev;
  prev->next = add;
}

static inline void list_add(struct list_head *add, struct list_head *head){
  __list_add(add, head, head->next);
}

static inline void __list_del(struct list_head * prev, struct list_head * next){
  next->prev = prev;
  prev->next = next;
}

static inline void list_del(struct list_head *entry){
	__list_del(entry->prev, entry->next);
	entry->next = LIST_POISON1;
	entry->prev = LIST_POISON2;
}
static inline void list_add_tail(struct list_head *new, struct list_head *head){
  __list_add(new, head->prev, head);
}

static inline int list_empty(const struct list_head *head){
  return head->next == head;
}
static inline void __list_splice(struct list_head *list,
				 struct list_head *head){
  struct list_head *first = list->next;
  struct list_head *last = list->prev;
  struct list_head *at = head->next;

  first->prev = head;
  head->next = first;

  last->next = at;
  at->prev = last;
}

static inline void list_splice(struct list_head *list, struct list_head *head){
	if (!list_empty(list))
		__list_splice(list, head);
}

static inline void list_splice_init(struct list_head *list,
				    struct list_head *head){
  if (!list_empty(list)) {
    __list_splice(list, head);
    INIT_LIST_HEAD(list);
  }
}

#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

struct hlist_head {
	struct hlist_node *first;
};

struct hlist_node {
	struct hlist_node *next, **pprev;
};

#define HLIST_HEAD_INIT { .first = 0 }
#define HLIST_HEAD(name) struct hlist_head name = {  .first = 0 }
#define INIT_HLIST_HEAD(ptr) ((ptr)->first = 0)
#define INIT_HLIST_NODE(ptr) ((ptr)->next = 0, (ptr)->pprev = 0)
#endif
