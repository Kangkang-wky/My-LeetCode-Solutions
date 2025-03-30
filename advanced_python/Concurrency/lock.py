#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import time
import random

from threading import Thread, Lock, RLock

LOCK = Lock()


# 无锁状态
def job1(n=10):
    global C

    for idx in range(n):
        C += 1
        print('Job1: {}'.format(C))
        time.sleep(random.random())

def job2(n=10):
    global C

    for idx in range(n):
        C += 10
        print('Job2: {}'.format(C))
        time.sleep(random.random())

def test_job():
    global C
    C = 0

    t1 = Thread(target=job1)
    t2 = Thread(target=job2)

    t1.start()
    t2.start()

    t1.join()
    t2.join()


# 有锁状态
def job1_with_lock(n=10):
    global C, LOCK

    LOCK.acquire()

    for idx in range(n):
        C += 1
        print('Job1: {}'.format(C))
        time.sleep(random.random())

    LOCK.release()

def job2_with_lock(n=10):
    global C, LOCK

    LOCK.acquire()

    for idx in range(n):
        C += 10
        print('Job2: {}'.format(C))
        time.sleep(random.random())

    LOCK.release()

def test_job_with_lock():
    global C, LOCK

    C = 0
    LOCK = Lock()

    t1 = Thread(target=job1_with_lock)
    t2 = Thread(target=job2_with_lock)

    t1.start()
    t2.start()

    t1.join()
    t2.join()


# 在同一个线程中，我们可能会多次请求同一个资源，这称为嵌套锁。
# 可则无法正常运行，因为第二次获取锁时，锁已经被同一线程获取，
# 从而无法运行后续代码。由于后续代码无法运行则无法释放锁，
# 从而上述的嵌套锁会造成**死锁**。

def lock_with_lock(n=10):
    c = 0
    lock = Lock()

    with lock:
        for idx in range(n):
            c += 1
            with lock:
                print(c)


def test_lock_with_lock():
    t = Thread(target=lock_with_lock)
    t.start()
    t.join(timeout=3)


# 可重入锁解决上述的问题
def rlock_with_lock(n=10):
    c = 0
    lock = RLock()

    with lock:
        for idx in range(n):
            c += 1
            with lock:
                print(c)


def test_rlock_with_lock():
    t = Thread(target=rlock_with_lock)
    t.start()
    t.join()


# 全局解释器锁 #
# 全局解释器锁（Global Interpreter Lock，GIL），是计算机程序设计语言解释器用于同步线程的一种机制，
# 它使得任何时刻仅有一个线程在执行。
# 任何 Python 线程执行前，必须先获得 GIL 锁，然后，每执行 100 条字节码，解释器就自动释放 GIL 锁，
# 让别的线程有机会执行。这个 GIL 全局锁实际上把所有线程的执行代码都给上了锁，
# 所以，多线程在 Python 中只能交替执行，即使 100 个线程跑在 100 核 CPU 上，也只能用到 1 个核。


if __name__ == '__main__':
    line_sep = '-' * 60

    print(line_sep)
    print('无锁')
    print(line_sep)
    test_job()
    print(line_sep)

    print(line_sep)
    print('有锁')
    print(line_sep)
    test_job_with_lock()
    print(line_sep)

    print(line_sep)
    print('锁嵌套 - Lock')
    print(line_sep)
    test_lock_with_lock()
    print(line_sep)

    print(line_sep)
    print('锁嵌套 - RLock')
    print(line_sep)
    test_rlock_with_lock()
    print(line_sep)

    sys.exit()