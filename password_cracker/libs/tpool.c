
#include "tpool.h"
#include "queue.h"

#include <stdio.h>
#include <pthread.h>

struct tpool {
    //tpool_work_t    *work_first;
    //tpool_work_t    *work_last;
    queue *pqueue;
    pthread_mutex_t  work_mutex;
    pthread_cond_t   work_cond;
    pthread_cond_t   working_cond;
    size_t           working_cnt;
    size_t           thread_cnt;
    bool             stop;
};


static void *worker_start(void *arg)
{

    return NULL;
}

tpool *tpool_create(size_t num)
{
    tpool *tp = malloc(sizeof(tpool));
    pthread_t  thread;
    if (tp == NULL) {
        fprintf(stderr, "tpool create failed, malloc error\n");
        return NULL;
    }
    tp->thread_cnt = num;
    pthread_mutex_init(&tp->work_mutex, NULL);
    pthread_cond_init(&tp->work_cond, NULL);
    pthread_cond_init(&tp->working_cond, NULL);
    tp->working_cnt = 0;
    tp->stop = false;
    tp->pqueue = queue_create(1024);

    for (size_t i = 0; i < num; i++) {
        pthread_create(&thread, NULL, worker_start, tp);
        pthread_detach(thread);
    }

    return tp;
}

void tpool_destroy(tpool *tm)
{

}

bool tpool_add_work(tpool *tm, thread_func_t func, void *arg)
{
    return true;
}

void tpool_wait(tpool *tm)
{

}
