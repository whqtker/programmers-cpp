#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> queue1, vector<int> queue2) {
    int answer = -2;

    queue<int> q1, q2;
    long long sum1 = 0, sum2 = 0;
    for (int e : queue1) {
        sum1 += e;
        q1.push(e);
    }
    for (int e : queue2) {
        sum2 += e;
        q2.push(e);
    }

    // �� ��� �� ���� ���� ���� ����
    if ((sum1 + sum2) % 2)
        return -1;

    int cnt = 0;
    int max_op = queue1.size() * 4; // ť�� ���̸� n�̶� �� ��, ��ȯ�ϴ� �� 4n
    while (sum1 != sum2) {
        // 1 vs all
        if (q1.empty() || q2.empty()) {
            return -1;
        }

        if (max_op < cnt) {
            return -1;
        }

        if (sum1 > sum2) {
            int e = q1.front();
            q2.push(e);
            q1.pop();
            sum1 -= e;
            sum2 += e;
        }
        else if (sum1 < sum2) {
            int e = q2.front();
            q1.push(e);
            q2.pop();
            sum1 += e;
            sum2 -= e;
        }

        cnt++;
    }

    answer = cnt;
    return answer;
}