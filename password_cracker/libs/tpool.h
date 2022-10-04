#ifndef __TPOOL_H__
#define __TPOOL_H__

#include <stdbool.h>
#include <stddef.h>

typedef struct tpool tpool;
typedef void (*thread_func_t)(void *arg);

tpool *tpool_create(size_t num);
void tpool_destroy(tpool *tm);
bool tpool_add_work(tpool *tm, thread_func_t func, void *arg);
void tpool_wait(tpool *tm);

#endif // end of __TPOOL_H__
