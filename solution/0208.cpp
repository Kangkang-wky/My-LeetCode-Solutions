// trie 前缀树或者字典树实现
// 可参考维基实现 https://zh.wikipedia.org/zh-hans/Trie
#include "../include/help.h"

// tire tree 实际上是一个多叉树, 26 个字母对应 26 个 叉
// 只是节点分叉指向的可能是一个空链接

// c version
class Trie1 {
private:
  bool is_word;
  Trie1 *next[26];

public:
  // 初始化所有链接置为 nullptr, is_word 都为 false
  Trie1() {
    is_word = false;
    for (size_t i = 0; i < 26; i++) {
      next[i] = nullptr;
    }
  }

  void insert(string word) {
    Trie1 *node = this;
    for (const auto &c : word) {
      if (node->next[c - 'a'] == NULL) {
        node->next[c - 'a'] = new Trie1();
      }
      node = node->next[c - 'a'];
    }
    node->is_word = true;
  }

  bool search(string word) {
    Trie1 *node = this;
    for (const auto &c : word) {
      node = node->next[c - 'a'];
      if (node == NULL) {
        return false;
      }
    }
    return node->is_word;
  }

  bool startsWith(string prefix) {
    Trie1 *node = this;
    for (const auto &c : prefix) {
      node = node->next[c - 'a'];
      if (node == NULL) {
        return false;
      }
    }
    return true;
  }
};

// modern c++ version
// string_view & unique_ptr
class Trie2 {
private:
  // unique_ptr 默认初始化为 nullptr, is_word 都初始化为 false
  unique_ptr<Trie2> children[26];
  bool is_word = false;

  Trie2 *findNode(string_view word, bool insert = false) {
    auto *node = this;

    for (const auto &c : word) {
      int index = c - 'a';
      // 如果在当前节点并不存在这样的 char
      if (!node->children[index]) {
        // 如果是 search 或者 startswith 类型 直接返回 nullptr
        if (!insert) {
          return nullptr;
        }
        // 如果是 insert 类型创建 Tire2
        node->children[index] = make_unique<Trie2>();
      }
      // 向下寻找
      node = node->children[index].get();
    }
    return node;
  }

public:
  void insert(string_view word) {
    auto *cur = findNode(word, /* insert type */ true);
    // 插入后, 在终点 word 上标记 true
    cur->is_word = true;
  }

  bool search(string_view word) {
    auto *cur = findNode(word, /* insert type */ false);
    // search 到对应 word 的要求是, 返回的当前节点不是 null 且 它是 word 的终点
    return !!cur && cur->is_word;
  }

  bool startsWith(string_view prefix) {
    auto *cur = findNode(prefix, /* insert type */ false);
    // startsWith 的要求是, 返回的当前节点不是 null 就可以了
    return !!cur;
  }
};