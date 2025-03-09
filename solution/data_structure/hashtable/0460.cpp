#include "../include/help.h"

/**
 * @brief LFU算法
        LFU frenquency 为原来的 LRU 的变形
        LRU 算法的淘汰策略是 Least Recently Used
        每次淘汰那些最久没被使用的数据
        LFU 算法的淘汰策略是 Least Frequently Used
        算法是淘汰访问频次最低的数据，如果访问频次最低的数据有多条，需要淘汰最旧的数据。
 */

struct Node {
    int key, value, freq;
    Node() : key(0), value(0), freq(1) {}
    Node(int key, int value) : key(key), value(value), freq(1) {}
};

class LFUCache {
private:
    int capacity_, minFreq_;
    std::unordered_map<int, Node*> keyNode_; //从键到节点的映射
    std::unordered_map<int, std::list<Node*>> freqList_; //从频率到节点链表的映射
    std::unordered_map<Node*, std::list<Node*>::iterator> nodeIter_; //从节点到其在列表中位置的映射

    // 无论使用 get 还是 put 方法都会导致节点频率的增加
    void updateFrequency(Node* node) {
        int freq = node->freq;
        auto& nodeList = freqList_[freq]; //获取该频率对应的节点链表
        nodeList.erase(nodeIter_[node]); // 从该链表中删除该节点，因为该节点的频率注定被改变了
        // 如果当前频率的节点链表为空，删除该频率并更新最小频率
        if (nodeList.empty()) {
            freqList_.erase(freq);
            if (minFreq_ == freq) minFreq_++; //当前删除的频率链表为最小频率时，更新最小频率
        }
        //增加节点的频率，并将其插入到新的频率-节点链表的最前面
        node->freq++;
        freqList_[node->freq].push_front(node);
        nodeIter_[node] = freqList_[node->freq].begin(); //记录每个节点在各自链表中的位置
    }
public:
    LFUCache(int capacity) : capacity_(capacity), minFreq_(0) {}

    int get(int key) {
        if (keyNode_.find(key) == keyNode_.end()) {
            return -1;
        } else {
            Node* node = keyNode_[key];
            updateFrequency(node);
            return node->value;
        }
    }

    void put(int key, int value) {
        if (capacity_ == 0) return; //容量为0，直接返回

        // 更新值、更新频率
        if (keyNode_.find(key) != keyNode_.end()) {
            Node* node = keyNode_[key];
            node->value = value;
            updateFrequency(node);
        } else {
            // 容量已满
            if (keyNode_.size() == capacity_) {
                auto& nodeList = freqList_[minFreq_]; //找到最小频率的那个 nodelist
                Node* node = nodeList.back(); //最小频率的最久未使用节点
                keyNode_.erase(node->key); //从键到节点的映射中删除该节点
                nodeIter_.erase(node);  // 从节点到其所属位置映射中删除该节点
                nodeList.pop_back(); //从获取到的频率链表中删除该节点
                if (nodeList.empty()) freqList_.erase(minFreq_); //如果频率列表为空，删除该频率链表
                delete node;
            }
            //如果缓存未满的情况下，插入新节点并更新相关映射
            Node* newNode = new Node(key, value);
            keyNode_[key] = newNode;
            freqList_[1].push_front(newNode);
            nodeIter_[newNode] = freqList_[1].begin();
            minFreq_ = 1; //重置最小频率
        }
    }
};

