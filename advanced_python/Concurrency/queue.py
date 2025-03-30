from queue import Queue

# maxsize=0 表示不限大小
# maxsize>0 且消息数达到限制时，put() 方法会阻塞
q = Queue(maxsize=0)

# 默认阻塞程序，等待队列消息，可设置超时时间
q.get(block=True, timeout=None)

# 发送消息，默认会阻塞程序至队列中有空闲位置放入数据
q.put(item, block=True, timeout=None)

# 等待所有的消息都被消费完
q.join()

# 通知队列任务处理已经完成，当所有任务都处理完成时，join() 阻塞将会解除
q.task_done()

# 查询当前队列的消息个数
q.qsize()

# 队列消息是否都被消费完，返回 True/False
q.empty()

# 检测队列里消息是否已满
q.full()
