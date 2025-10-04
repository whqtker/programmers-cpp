#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> ryan(11);
int max_gap;

void dfs(int n, int idx, const vector<int>& info, vector<int>& answer) {
    // ���� ����
    if (idx > 10 || n == 0) {
        if (n > 0) {
            ryan[10] += n;
        }

        int apeach_score = 0, ryan_score = 0;
        for (int i = 0; i <= 10; i++) {
            int a_cnt = info[i];
            int r_cnt = ryan[i];

            if (a_cnt >= r_cnt) {
                if (a_cnt == 0 && r_cnt == 0) continue;
                apeach_score += 10 - i;
            }
            else {
                ryan_score += 10 - i;
            }
        }

        int gap = ryan_score - apeach_score;
        if (max_gap < gap) {
            max_gap = gap;
            answer = ryan;
        }
        else if (max_gap == gap && gap > 0) {
            for (int i = 10; i >= 0; i--) {
                if (ryan[i] > answer[i]) {
                    answer = ryan;
                    break;
                }
                else if (ryan[i] < answer[i])
                    break;
            }
        }

        if (n > 0)
            ryan[10] -= n;
        return;
    }

    // ���̾��� �ش� ������ �򵵷�
    int a_cnt = info[idx];
    int r_cnt = a_cnt + 1;

    if (n - r_cnt >= 0) {
        ryan[idx] = r_cnt;
        dfs(n - r_cnt, idx + 1, info, answer);
        ryan[idx] = 0;
    }

    // ���� ���� �ʵ���
    ryan[idx] = 0;
    dfs(n, idx + 1, info, answer);
}

vector<int> solution(int n, vector<int> info) {
    vector<int> answer = { -1 };

    // ���̾��� ������ �������� ���� ����ġ ȭ�� �� + 1 �̻��� ����� ��
    // ���� ��������, ������ ��� ������ Ž��
    dfs(n, 0, info, answer);
    return answer;
}