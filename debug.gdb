## Saving the to-be forged waiter.
break futex_wait_requeue_pi
commands
set $waiter = &rt_waiter
cont
end


## Watch the forged waiter struct.
break ___sys_sendmsg


## Corrupting the waiters list.
break task_blocks_on_rt_mutex
