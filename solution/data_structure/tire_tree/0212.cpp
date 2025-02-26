#include "../include/help.h"

/**
 * @brief 字典树使用, 主要有两点需要注意：
 *        一是除叶子节点外, word 都为空, 表示非叶子节点, 非叶子节点的部分保存在哈希表 unordered_map 中
 *        二是对于叶子节点, 字符串保存在 word 中
 */


struct TrieNode {
    string word;                    
    unordered_map<char,TrieNode *> children;
    TrieNode() {
        this->word = "";
    }   
};

void insertTrie(TrieNode * root,const string & word) {
    TrieNode * node = root;
    for (auto c : word){        // 遍历每一个字符
        if (!node->children.count(c)) {
            node->children[c] = new TrieNode();     // 如果当前子树中的字符, 并不存在于 TrieNode 的节点上
        }
        node = node->children[c];
    }
    node->word = word;
}

class Solution {
public:
    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    bool dfs(vector<vector<char>>& board, int x, int y, TrieNode * root, set<string> & res) {
        char ch = board[x][y];
        if (!root->children.count(ch)) {
            return false;
        }
        
        root = root->children[ch];

        // 如果到达了叶子节点，插入到结果 set 中 
        if (root->word.size() > 0) {
            res.insert(root->word);
        }

        board[x][y] = '#';      // 把已经搜索的地方置为 "#"
        for (int i = 0; i < 4; ++i) {
            int nx = x + dirs[i][0];
            int ny = y + dirs[i][1];
            if (nx >= 0 && nx < board.size() && ny >= 0 && ny < board[0].size()) {
                if (board[nx][ny] != '#') {
                    dfs(board, nx, ny, root,res);
                }
            }
        }
        board[x][y] = ch;       // 回溯, 

        return true;      
    }

    vector<string> findWords(vector<vector<char>> & board, vector<string> & words) {
        TrieNode * root = new TrieNode();
        set<string> res;        // 利用 set 来做字符串的去重操作
        vector<string> ans;

        for (auto & word: words){
            insertTrie(root,word);
        }
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                dfs(board, i, j, root, res);            // 对每个节点做 dfs 操作
            }
        }        
        for (auto & word: res) {
            ans.emplace_back(word);
        }
        return ans;        
    }
};