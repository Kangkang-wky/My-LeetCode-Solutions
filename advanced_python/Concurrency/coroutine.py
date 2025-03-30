#!/usr/bin/env python
# -*- coding: utf-8 -*-

import time
import asyncio
import random

from threading import Thread
from asyncio.futures import Future
from collections.abc import Generator, Coroutine


# yield from 使用

def jump_range(n):
    idx = 0

    while idx < n:
        jump = yield idx
        print('[idx: {}, jump: {}]'.format(idx, jump))

        if jump is None:
            jump = 1

        idx += jump


def test_jump_range():
    itr = jump_range(6)
    print(next(itr))
    print(itr.send(2))
    print(next(itr))
    print(itr.send(-1))
    print(next(itr))
    print(next(itr))


def test_yield_from():
    a_str = 'Leo'
    a_list = [1, 2, 3]
    a_dict = {'name': 'Leo', 'gender': 'Male'}
    a_gen = (idx for idx in range(4, 8))

    def gen(*args, **kwargs):
        for item in args:
            for ele in item:
                yield ele

    new_gen = gen(a_str, a_list, a_dict, a_gen)
    print(list(new_gen))

    a_gen = (idx for idx in range(4, 8))

    def gen_from(*args, **kwargs):
        for item in args:
            yield from item

    new_gen = gen_from(a_str, a_list, a_dict, a_gen)
    print(list(new_gen))


def average_gen():
    total = 0
    count = 0
    average = 0

    while True:
        num = yield average

        if num is None:
            break

        count += 1
        total += num
        average = total / count

    return total, count, average


def proxy_gen():
    while True:
        total, count, average = yield from average_gen()
        print(
            '计算完毕，共输入 {} 个数值，总和 {}，平均值 {}'.format(
                count, total, average
            )
        )


def test_proxy_average_gen():
    calc_average = proxy_gen()
    next(calc_average)
    print(calc_average.send(10))
    print(calc_average.send(20))
    print(calc_average.send(30))
    calc_average.send(None)


async def async_func(name):
    print('Hello,', name)


def test_async_func():
    coroutine = async_func('World')
    print(isinstance(coroutine, Coroutine))


@asyncio.coroutine
def coroutine_func(name):
    print('Hello, ', name)
    yield from asyncio.sleep(1)
    print('Bye, ', name)


def test_coroutine_func():
    coroutine = coroutine_func('World')
    print(isinstance(coroutine, Generator))
    print(isinstance(coroutine, Coroutine))


async def hello(name):
    print('Hello,', name)


def test_coroutine_process():
    # 定义协程
    coroutine = hello('World')
    # 定义事件循环
    loop = asyncio.get_event_loop()
    # 创建任务
    task = loop.create_task(coroutine)
    # 将任务交由时间循环并执行
    loop.run_until_complete(task)


# await 用于挂起阻塞的异步调用接口，其作用在一定程度上类似于 yield。
# yield from 后面可接可迭代对象，也可接 future 对象或协程对象；
# await 后面必须接 future 对象或协程对象。

async def await_hello(name):
    await asyncio.sleep(2)
    print('Hello,', name)


def test_await_hello():
    coroutine = await_hello('World')
    
    # asyncio.ensure_future 使用
    # 将协程转为 task 对象
    task = asyncio.ensure_future(coroutine)
    print(isinstance(task, Future))


async def _sleep(x):
    time.sleep(x)
    return '暂停了 {} 秒'.format(x)


# 异步 IO 的实现原理就是在 IO 高的地方挂起，等 IO 结束后再继续执行。
# 绝大部分情况下，后续代码的执行是需要依赖 IO 的返回值的，这就需要使用**回调**。

# 回调的实现有两种，一种是在同步编程中直接获取返回结果：

def test_result():
    coroutine = _sleep(2)
    loop = asyncio.get_event_loop()
    task = asyncio.ensure_future(coroutine)

    loop.run_until_complete(task)
    print('返回结果：{}'.format(task.result()))


# 另一种是通过添加回调函数来实现：

def callback(future):
    print('回调返回结果：{}'.format(future.result()))

def test_callback():
    coroutine = _sleep(2)
    loop = asyncio.get_event_loop()
    task = asyncio.ensure_future(coroutine)

    task.add_done_callback(callback)
    loop.run_until_complete(task)



# asyncio 实现并发需要多个协程来完成，每当有任务阻塞时需要 await，然后让其他协程继续工作。

async def do_some_work(x):
    print('等待中 ...')
    await asyncio.sleep(x)
    print('{} 秒后结束'.format(x))
    return x


def test_asyncio_parallel():
    coroutine1 = do_some_work(1)
    coroutine2 = do_some_work(2)
    coroutine3 = do_some_work(4)

    tasks = [
        asyncio.ensure_future(coroutine1),
        asyncio.ensure_future(coroutine2),
        asyncio.ensure_future(coroutine3),
    ]

    loop = asyncio.get_event_loop()
    loop.run_until_complete(asyncio.wait(tasks))

    for task in tasks:
        print('任务结果：{}'.format(task.result()))


# 协程之间可以进行嵌套，即在一个协程中 await 另一个协程：

async def out_do_some_work():
    coroutine1 = do_some_work(1)
    coroutine2 = do_some_work(2)
    coroutine3 = do_some_work(4)

    tasks = [
        asyncio.ensure_future(coroutine1),
        asyncio.ensure_future(coroutine2),
        asyncio.ensure_future(coroutine3),
    ]

    dones, pendings = await asyncio.wait(tasks)

    for task in dones:
        print('任务结果：{}'.format(task.result()))


def test_nest_asyncio_parallel():
    loop = asyncio.get_event_loop()
    loop.run_until_complete(out_do_some_work())


# 协程（准确的说是 Future 或 Task 对象）包含如下状态：

# Pending：已创建，未执行
# Running：执行中
# Done：执行完毕
# Cancelled：被取消

def test_asyncio_status():
    coroutine = _sleep(10)
    loop = asyncio.get_event_loop()
    task = loop.create_task(coroutine)

    print('Pending')

    try:
        t = Thread(target=loop.run_until_complete, args=(task,))
        t.start()
        print('Running')
        t.join()
    except KeyboardInterrupt as e:
        task.cancel()
        print('Cancelled')
    finally:
        print('Done')


# asyncio.wait() 可以通过参数控制何时返回：

async def random_sleep():
    await asyncio.sleep(random.uniform(0.5, 6))

def test_asyncio_wait():
    loop = asyncio.get_event_loop()
    tasks = [random_sleep() for _ in range(1, 10)]

    dones, pendings = loop.run_until_complete(
        asyncio.wait(tasks, return_when=asyncio.FIRST_COMPLETED)
    )
    print('第一次完成的任务数：{}'.format(len(dones)))

    dones, pendings = loop.run_until_complete(asyncio.wait(pendings, timeout=2))
    print('第二次完成的任务数: {}'.format(len(dones)))

    dones, pendings = loop.run_until_complete(asyncio.wait(pendings))
    print('第三次完成的任务数：{}'.format(len(dones)))


if __name__ == '__main__':
    line_sep = '-' * 60

    print(line_sep)
    print('测试 Yield Send')
    print(line_sep)
    test_jump_range()
    print(line_sep)

    print(line_sep)
    print('测试 Yield From')
    print(line_sep)
    test_yield_from()
    print(line_sep)

    print(line_sep)
    print('测试委托生成器')
    print(line_sep)
    test_proxy_average_gen()
    print(line_sep)

    print(line_sep)
    print('测试委托生成器')
    print(line_sep)
    test_async_func()
    print(line_sep)

    print(line_sep)
    print('测试 Coroutine')
    print(line_sep)
    test_coroutine_func()
    print(line_sep)

    print(line_sep)
    print('测试协程流程')
    print(line_sep)
    test_coroutine_process()
    print(line_sep)

    print(line_sep)
    print('测试 Future')
    print(line_sep)
    test_await_hello()
    print(line_sep)

    print(line_sep)
    print('测试 result')
    print(line_sep)
    test_result()
    print(line_sep)

    print(line_sep)
    print('测试 callback')
    print(line_sep)
    test_callback()
    print(line_sep)

    print(line_sep)
    print('测试 asyncio 并发')
    print(line_sep)
    test_asyncio_parallel()
    print(line_sep)

    print(line_sep)
    print('测试嵌入 asyncio 并发')
    print(line_sep)
    test_nest_asyncio_parallel()
    print(line_sep)

    print(line_sep)
    print('测试 asyncio 状态')
    print(line_sep)
    test_asyncio_status()
    print(line_sep)

    print(line_sep)
    print('测试何时返回')
    print(line_sep)
    test_asyncio_wait()
    print(line_sep)