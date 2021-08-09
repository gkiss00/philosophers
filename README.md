# philosophers

Solve the philosophers problem in three different way.
They should not die.

## One

Each philosopher is a thread and has a fork at his left and right. Each fork is a mutex.

## Two

Each philosopher is a thread. All the forks are at the center of the table. Each fork is represented by a semaphore.

## Three

Each philosopher is a process. All the forks are at the center of the table. Each fork is represented by a semaphore.