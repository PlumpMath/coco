#ifndef LIBCOCO_CC_ROUTINE_H
#define LIBCOCO_CC_ROUTINE_H

#include <stdint.h>
#include <sys/poll.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct st_co_routine_s st_co_routine_t;
typedef struct st_share_stack_s st_share_stack_t;

struct st_co_routine_attr_s {
    size_t stack_size;
    st_share_stack_t *share_stack;
};
typedef struct st_co_routine_attr_s st_co_routine_attr_t;

static inline void st_co_routine_attr_init(st_co_routine_attr_t *attr) {
    attr->stack_size = 128 * 1024;
    attr->share_stack = NULL;
}

typedef struct st_co_epoll_s st_co_epoll_t;
typedef int (*pfn_co_eventloop_t)(void *);
typedef void *(*pfn_co_routine_t)(void *);

int co_create(st_co_routine_t **co, const st_co_routine_attr_t *attr, pfn_co_routine_t routine, void *arg);
void co_resume(st_co_routine_t *co);
void co_yield(st_co_routine_t *co);
void co_yield_ct();
void co_release(st_co_routine_t *co);

st_co_routine_t *co_self();

int co_poll(st_co_epoll_t *ctx, struct pollfd fds[], nfds_t nfds, int timeout_ms);
void co_eventloop(st_co_epoll_t *ct, pfn_co_eventloop_t pfn, void *arg);

#endif //LIBCOCO_CC_ROUTINE_H