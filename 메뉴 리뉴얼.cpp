#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;

    for (int i = 0; i < orders.size(); i++) {
        sort(orders[i].begin(), orders[i].end());
    }

    map<string, int> m; // 코스메뉴, 등장 횟수
    for (int i = 0; i < orders.size(); i++) {
        for (int j = 0; j < course.size(); j++) {
            // 단품들로 코스를 만들어본다.
            // 해당 단품 개수보다 코스에 필요한 개수가 더 많은 경우
            if (orders[i].size() < course[j]) {
                continue;
            }

            // 순열을 생성할 때 사용할 배열
            // course[j] 만큼 0, orders[i].size()-course[j] 만큼 1
            vector<int> v;
            for (int k = 0; k < course[j]; k++) {
                v.push_back(0);
            }
            for (int k = 0; k < orders[i].size() - course[j]; k++) {
                v.push_back(1);
            }

            do {
                string menu = "";
                for (int k = 0; k < v.size(); k++) {
                    if (v[k] == 0) {
                        menu += orders[i][k];
                    }
                }

                m[menu]++;

            } while (next_permutation(v.begin(), v.end()));
        }
    }


    // map을 순회하며 코스의 개수에 대하여 가장 많이 등장한 횟수를 구한다.
    map<int, int> max_cnt; // 코스의 개수, 등장 횟수
    for (auto it : m) {
        int len = it.first.size();
        int cnt = it.second;

        max_cnt[len] = max(max_cnt[len], cnt);
    }


    for (auto it : m) {
        string menu = it.first;
        int cnt = it.second;

        if (cnt >= 2 && cnt == max_cnt[menu.size()]) {
            answer.push_back(it.first);
        }
    }

    return answer;
}