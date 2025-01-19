#include "../include/help.h"

/**
 * @brief 电话号码字幕组合, dfs
 * 
 */



class Solution {
private:
    std::unordered_map<string, string> hash_letter;
public:
    void dfs(int step, string &digits, string &temp, std::vector<string> &res){
        if (step >= digits.size()) {
            res.push_back(temp);
        }

        // 处理到第 step 个数
        string hash_digit = hash_letter[digits.substr(step, 1)];

        for (int i = 0; i < hash_digit.size(); i++) {
            temp += hash_digit[i];
            step++;
            dfs(step, digits, temp, res);
            step--;
            temp.erase(temp.size() - 1, 1);
        }

    }


    vector<string> letterCombinations(string digits) {
        
        hash_letter.insert(std::make_pair("2", "abc"));
        hash_letter.insert(std::make_pair("3", "def"));
        hash_letter.insert(std::make_pair("4", "ghi"));
        hash_letter.insert(std::make_pair("5", "jkl"));
        hash_letter.insert(std::make_pair("6", "mno"));
        hash_letter.insert(std::make_pair("7", "pqrs"));
        hash_letter.insert(std::make_pair("8", "tuv"));
        hash_letter.insert(std::make_pair("9", "wxyz"));

        std::vector<string> res;
        string temp;

        if (digits == "") {
            return res;
        }


        dfs(0, digits, temp, res);

        return res;
    }
};