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

    map<string, int> m; // �ڽ��޴�, ���� Ƚ��
    for (int i = 0; i < orders.size(); i++) {
        for (int j = 0; j < course.size(); j++) {
            // ��ǰ��� �ڽ��� ������.
            // �ش� ��ǰ �������� �ڽ��� �ʿ��� ������ �� ���� ���
            if (orders[i].size() < course[j]) {
                continue;
            }

            // ������ ������ �� ����� �迭
            // course[j] ��ŭ 0, orders[i].size()-course[j] ��ŭ 1
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


    // map�� ��ȸ�ϸ� �ڽ��� ������ ���Ͽ� ���� ���� ������ Ƚ���� ���Ѵ�.
    map<int, int> max_cnt; // �ڽ��� ����, ���� Ƚ��
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