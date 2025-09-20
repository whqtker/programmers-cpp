#include <string>
#include <vector>
#include <map>

using namespace std;

int max_members;
int max_profit;

void dfs(int depth, const vector<vector<int>>& users, const vector<int>& rate, const vector<int>& emoticons, vector<int>& cur) {
    if (depth == emoticons.size()) {
        int cur_members = 0; // ���� ������ ���
        int cur_profit = 0; // ���� �̸�Ƽ�� ����
        for (int i = 0; i < users.size(); i++) {
            int profit = 0; // ���� ������� �̸�Ƽ�� ����(���� �� �ݿ� X)
            int p = users[i][0];
            int limit = users[i][1];

            for (int j = 0; j < emoticons.size(); j++) {
                int cur_p = cur[j];
                if (p <= cur_p) {
                    profit += emoticons[j] * (100 - cur_p) / 100;
                }
            }

            // ���ǿ� �´� �̸�Ƽ���� �����ߴµ� ������� ���� ������ ���� ���
            if (limit <= profit) {
                cur_members++;
            }
            else {
                cur_profit += profit;
            }
        }

        if (cur_members > max_members) {
            max_members = cur_members;
            max_profit = cur_profit;
        }
        // ������ ���� ������ �̸�Ƽ�� ������ �� ū ���
        else if (cur_members == max_members && cur_profit > max_profit) {
            max_profit = cur_profit;
        }

        return;
    }

    for (int i = 0; i < rate.size(); i++) {
        cur.push_back(rate[i]);
        dfs(depth + 1, users, rate, emoticons, cur);
        cur.pop_back();
    }
}

vector<int> solution(vector<vector<int>> users, vector<int> emoticons) {
    vector<int> answer;

    // �̸�Ƽ�� �������� 10, 20, 30, 40%�̴�.
    vector<int> rate = { 10,20,30,40 };

    // �������� ������ �ִ� ����� ���� 4^7 = 16384
    vector<int> cur;
    dfs(0, users, rate, emoticons, cur);

    answer.push_back(max_members);
    answer.push_back(max_profit);
    return answer;
}