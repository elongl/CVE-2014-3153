#define _GNU_SOURCE
#include <stdatomic.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/futex.h>

int futex(int *uaddr, int futex_op, int val, uint32_t val2, int *uaddr2, int val3)
{
    return syscall(SYS_futex, uaddr, futex_op, val, val2, uaddr2, val3);
}

int flock(int *uaddr)
{
    return futex(uaddr, FUTEX_LOCK_PI, 0, 0, NULL, 0);
}

int funlock(int *uaddr)
{
    return futex(uaddr, FUTEX_UNLOCK_PI, 0, 0, NULL, 0);
}

int fwait_requeue(int *src, int *dst, int expected_val)
{
    return futex(src, FUTEX_WAIT_REQUEUE_PI, expected_val, 0, dst, 0);
}

int frequeue(int *src, int *dst, int max_requeued_waiters, int expected_val)
{
    return futex(src, FUTEX_CMP_REQUEUE_PI, 1, max_requeued_waiters, dst, expected_val);
}
