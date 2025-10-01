#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#define INF 1e9

using namespace std;

int dp[301][301]; // dp[i][j]: 알고력 i, 코딩력 j에 도달하기 위한 최소 시간

int solution(int alp, int cop, vector<vector<int>> problems) {
    int answer = 0;

    int max_alp = -1;
    int max_cop = -1;
    for (vector<int> p : problems) {
        max_alp = max(max_alp, p[0]);
        max_cop = max(max_cop, p[1]);
    }

    alp = min(alp, max_alp);
    cop = min(cop, max_cop);

    for (int i = alp; i <= max_alp; i++) {
        for (int j = cop; j <= max_cop; j++) {
            dp[i][j] = INF;
        }
    }

    dp[alp][cop] = 0;

    for (int i = alp; i <= max_alp; i++) {
        for (int j = cop; j <= max_cop; j++) {
            int nxt_alp = min(max_alp, i + 1);
            int nxt_cop = min(max_cop, j + 1);
            dp[nxt_alp][j] = min(dp[nxt_alp][j], dp[i][j] + 1); // 알고 공부
            dp[i][nxt_cop] = min(dp[i][nxt_cop], dp[i][j] + 1); // 코딩 공부

            // 문제 풀기
            for (vector<int> p : problems) {
                if (i >= p[0] && j >= p[1]) {
                    nxt_alp = min(max_alp, i + p[2]);
                    nxt_cop = min(max_cop, j + p[3]);
                    dp[nxt_alp][nxt_cop] = min(dp[nxt_alp][nxt_cop], dp[i][j] + p[4]);
                }
            }
        }
    }

    answer = dp[max_alp][max_cop];
    return answer;
}