// LFU算法
// TODO:尝试写一下LFU算法
// LFU frenquency 为原来的 LRU 的变形
// LRU 算法的淘汰策略是 Least Recently Used
// 每次淘汰那些最久没被使用的数据
// LFU 算法的淘汰策略是 Least Frequently Used
// 每次淘汰那些使用次数最少得数据

// 尝试两种写法

// 一是哈希表 + 平衡二叉树(set)

// 一种是双哈希表