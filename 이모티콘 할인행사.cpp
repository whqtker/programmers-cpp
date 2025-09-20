#include <string>
#include <vector>
#include <map>

using namespace std;

int max_members;
int max_profit;

void dfs(int depth, const vector<vector<int>>& users, const vector<int>& rate, const vector<int>& emoticons, vector<int>& cur) {
    if (depth == emoticons.size()) {
        int cur_members = 0; // 현재 구독한 사람
        int cur_profit = 0; // 현재 이모티콘 수익
        for (int i = 0; i < users.size(); i++) {
            int profit = 0; // 현재 사용자의 이모티콘 수익(구독 시 반영 X)
            int p = users[i][0];
            int limit = users[i][1];

            for (int j = 0; j < emoticons.size(); j++) {
                int cur_p = cur[j];
                if (p <= cur_p) {
                    profit += emoticons[j] * (100 - cur_p) / 100;
                }
            }

            // 조건에 맞는 이모티콘을 구매했는데 사용자의 제한 가격을 넘은 경우
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
        // 구독한 수는 같으나 이모티콘 이익이 더 큰 경우
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

    // 이모티콘 할인율은 10, 20, 30, 40%이다.
    vector<int> rate = { 10,20,30,40 };

    // 할인율로 가능한 최대 경우의 수는 4^7 = 16384
    vector<int> cur;
    dfs(0, users, rate, emoticons, cur);

    answer.push_back(max_members);
    answer.push_back(max_profit);
    return answer;
}