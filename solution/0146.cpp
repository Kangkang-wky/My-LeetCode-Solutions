// LRU 缓存 算法的实现
#include "../include/help.h"

// LRU 方法实现示例
/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

// 使用 hash_map(哈希表) + list(双向链表) 实现 LRU 算法

// get 方法:  访问 key, 如果 LRU 队列中不存在则返回-1,
// 否则得到对应的 value，并且采用put 方法移到 LRU 队列d的队首,

// put 方法:  如果已经存在, 删除LRU队列当前位置的值, 移动到队首, 哈希 key
// 指向新位置 如果不存在, 根据 LRU 队列容量, 删除队列的尾元素, 将当前 key value
// 加入到LRU队首, 哈希 key 指向队首

// 注意 LRU队列中不能只存 value, 当队列容量已经满的时候, 需要删除队尾,
// 同时要删除哈希表中对应的 key, 而目前只有 哈希表指向双向链表迭代器

// 这种哈希表 + 双向链表的方式需要考虑清楚, 每一个操作对于 hashmap 以及
// doubleList 是否都需要更新

/*
需要注意的是为什么这里要采用双向链表, 主要是为了保证 O(1) 操作
同时双向链表要保存 KV 对, 而不是一个 value 的原因是因为, 还得删除
哈希表中的 key 值
*/

// list 效率太低, 可以自己实现一版双向链表
class LRUCache1 {
public:
  // key-value 键值对
  struct Node {
    int _key;
    int _value;
    Node() {}
    Node(int key, int value) : _key(key), _value(value) {}
  };

  // LRUCache 类初始化容量大小
  LRUCache1(int capacity) : capacity(capacity) {}

  int get(int key) {
    if (hashmap.find(key) != hashmap.end()) { // 哈希查找 若存在
      int value = hashmap[key]->_value;
      put(key, value); // 将其放到 LRU队列的队首
      return value;
    }
    return -1;
  }

  void put(int key, int value) {
    // 哈希查找若存在, 将迭代器传递给 LRU_queue
    if (hashmap.find(key) != hashmap.end()) {
      LRU_queue.erase(hashmap[key]);
    }
    // 若超出容量限制
    else if (LRU_queue.size() >= capacity) {
      hashmap.erase(LRU_queue.back()._key); // hashmap 删除队尾
      LRU_queue.pop_back();                 // LRU_queue 删除队尾
    }
    LRU_queue.push_front({key, value}); // LRU队首+1
    hashmap[key] = LRU_queue.begin(); // 哈希将key指向链表的迭代器队首
  }

private:
  int capacity;
  list<Node> LRU_queue; // LRU队列
  unordered_map<int, list<Node>::iterator>
      hashmap; // hashmap 存储 key 和 LRU队列的迭代器
};

class LRUCache2 {
  // key value 双向链表
  struct KV_list {
    int _key;
    int _val;
    KV_list *_next;
    KV_list *_pre;
  };

  // 定义一个带头节点的双向链表
  KV_list *dummy;
  int maxSize;
  int nodeNum;
  // 定义哈希表，key是int，val是双向链表的指针
  unordered_map<int, KV_list *> hashmap;

public:
  LRUCache2(int capacity) : dummy(new KV_list), maxSize(capacity), nodeNum(0) {
    // 带头节点的双向链表初始化
    dummy->_next = dummy;
    dummy->_pre = dummy;
  }
  // 在哈希表中是否存在 key, 通过哈希表访问双向链表, 再得到 value 值
  int get(int key) {
    // 哈希表中找到
    if (hashmap.find(key) != hashmap.end()) {
      KV_list *node = hashmap[key];

      // 在双向链表中移除当前 node
      node->_pre->_next = node->_next;
      node->_next->_pre = node->_pre;

      // 将当前 node 放到双向链表的头部
      // 此时 node 还是放在作为 hashmap 中 key-value 的 value 值, 没有发生更改
      insert_head(node);

      return node->_val;
    }
    return -1;
  }
  // 将放置队首放到这个函数下面
  void put(int key, int value) {
    // 检查是否存在对应键值
    if (hashmap.find(key) != hashmap.end()) {
      // 更新双向链表中的 value 值
      hashmap[key]->_val = value;
      // 双向链表中移除当前, 并放到头节点, 此时哈希表不需要更新
      get(key);
    }
    // 不存在
    else {
      // 缓存未满, 相对容易
      if (nodeNum < maxSize) {
        nodeNum++;
        KV_list *node = new KV_list;
        node->_key = key;
        node->_val = value;

        // 更新哈希表
        hashmap[key] = node;

        // 更新双向链表, 直接插入到头即可
        insert_head(node);
      }
      // 缓存满, 删除 LRU队列中最后一个节点
      else {
        // 通过双向链表头节点的方式来找到 LRU 最后一个节点
        // 更新哈希表
        KV_list *node = dummy->_pre;
        hashmap.erase(node->_key);

        // 更新 hash 表, 并修改当前 node 的值, get 将其插入到正确的位置
        hashmap[key] = node;
        node->_key = key;
        node->_val = value;

        // 更新双向链表, 双向链表中移除当前, 并放到头节点
        get(key);
      }
    }
  }

private:
  // 将 node 节点插入到 head 节点的下一个
  void insert_head(KV_list *node) {
    node->_next = dummy->_next;
    node->_pre = dummy;
    dummy->_next->_pre = node;
    dummy->_next = node;
  }
};

class LRUCache3 {
  // key value 双向链表
  struct KV_list {
    int _key;
    int _val;
    KV_list *_next;
    KV_list *_pre;
  };

  // 定义一个带头节点的双向链表
  KV_list *dummy;
  int maxSize;
  int nodeNum;
  // 定义哈希表，key是int，val是双向链表的指针
  unordered_map<int, KV_list *> hashmap;

public:
  LRUCache3(int capacity) : dummy(new KV_list), maxSize(capacity), nodeNum(0) {
    // 带头节点的双向链表初始化
    dummy->_next = dummy;
    dummy->_pre = dummy;
  }
  // 在哈希表中是否存在 key, 通过哈希表访问双向链表, 再得到 value 值
  int get(int key) {
    // 哈希表中找到
    if (hashmap.find(key) != hashmap.end()) {
      KV_list *node = hashmap[key];
      // 在双向链表中移除当前 node
      node->_pre->_next = node->_next;
      node->_next->_pre = node->_pre;

      // 将当前 node 放到双向链表的头部
      // 此时 node 还是放在作为 hashmap 中 key-value 的 value 值, 没有发生更改
      insert_head(node);
      return node->_val;
    }
    return -1;
  }
  // 将放置队首放到这个函数下面
  void put(int key, int value) {
    // 检查是否存在对应键值
    if (hashmap.find(key) != hashmap.end()) {
      // 更新双向链表中的 key value 值
      hashmap[key]->_val = value;

      // 更新双向链表
      KV_list *node = hashmap[key];
      node->_pre->_next = node->_next;
      node->_next->_pre = node->_pre;

      insert_head(node);
    }
    // 不存在
    else {
      // 缓存未满, 相对容易
      if (nodeNum < maxSize) {
        nodeNum++;
        KV_list *node = new KV_list;
        node->_key = key;
        node->_val = value;

        // 更新 hashmap
        hashmap[key] = node;
        // 更新双向链表
        insert_head(node);
      }
      // 缓存满, 删除 LRU队列中最后一个节点
      else {
        // 通过双向链表头节点的方式来找到 LRU 最后一个节点
        // 更新哈希表
        KV_list *node = dummy->_pre;
        hashmap.erase(node->_key);

        // 更新 hash 表, 并修改当前 node 的值, get 将其插入到正确的位置
        node->_key = key;
        node->_val = value;
        hashmap[key] = node;

        // 更新双向链表
        node->_pre->_next = node->_next;
        node->_next->_pre = node->_pre;

        insert_head(node);
      }
    }
  }

private:
  // 将 node 节点插入到 head 节点的下一个
  void insert_head(KV_list *node) {
    node->_next = dummy->_next;
    node->_pre = dummy;
    dummy->_next->_pre = node;
    dummy->_next = node;
  }
};