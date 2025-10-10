#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool able(const vector<int>& stones, int m, int k) {
    int cnt = 0; // 0 ���� �� ���� ���ӵ� ��
    for (int i = 0; i < stones.size(); i++) {
        if (stones[i] - m < 0) {
            cnt++;

            if (cnt == k)
                return false;
        }
        else {
            cnt = 0;
        }
    }

    return true;
}

int solution(vector<int> stones, int k) {
    int answer = 0;

    // �ִ�� �ǳ� �� �ִ� ����� ��
    int r = *max_element(stones.begin(), stones.end());
    int l = 0;
    int m;

    while (l <= r) {
        m = (l + r) / 2;
        if (able(stones, m, k)) {
            answer = m;
            l = m + 1;
        }
        else {
            r = m - 1;
        }
    }
    return answer;
}