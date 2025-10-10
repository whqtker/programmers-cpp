#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
#include <unordered_set>

using namespace std;

vector<int> solution(string s) {
    vector<string> v;
    // s�� ǥ���ϴ� ������ ���Ϳ� ����, {} ����
    for (int i = 1; i <= s.size() - 1; i++) {
        if (s[i] == '{') {
            string str = "";
            while (s[i] != '}') {
                str += s[i];
                i++;
            }
            str += s[i]; // }
            v.push_back(str);
        }
    }

    vector<vector<int>> nums; // string -> vector<int>
    unordered_set<int> us;
    for (int i = 0; i < v.size(); i++) {
        string str = v[i];
        //cout<<str<<" ";

        vector<int> set;
        string tok;
        istringstream iss(str.substr(1, str.size() - 2)); // �� �� �߰�ȣ ����
        while (getline(iss, tok, ',')) {
            set.push_back(stoi(tok));
            us.insert(stoi(tok));
        }
        nums.push_back(set);
    }

    map<int, int> m; // ����, Ʃ���� �ε���
    for (auto it : us) {
        m[it] = 1e9;
    }

    vector<int> answer(nums.size());
    for (int i = 0; i < nums.size(); i++) {
        for (int j = 0; j < nums[i].size(); j++) {
            m[nums[i][j]] = min(m[nums[i][j]], (int)nums[i].size());
        }
    }

    for (auto it : m) {
        answer[it.second - 1] = it.first;
    }
    return answer;
}