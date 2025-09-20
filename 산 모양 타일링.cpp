#include <string>
#include <vector>

using namespace std;

// 좌 -> 우 -> 상 으로 numbering
// tops에 위치하는 삼각형들의 번호는 3의 배수가 됨.
// 가장 우측, 마지막 삼각형의 번호는 3n+1
int dp[300001][2]; // dp[i][j]에서 i번 째 삼각형을 j==0: 정삼각형으로, j==1: 마름모로

int solution(int n, vector<int> tops) {
	int answer = 0;

	dp[1][0] = 1;
	dp[1][1] = 0;

	dp[2][0] = 1;
	dp[2][1] = 1;

	if (tops[0] == 1) {
		dp[3][0] = 2;
		dp[3][1] = 1;
	}
	else {
		dp[3][0] = 1;
		dp[3][1] = 1;
	}

	for (int i = 4; i <= 3 * n + 1; i++) {
		// tops에 해당하는 인덱스 처리
		if (i % 3 == 0) {
			// tops에 삼각형이 존재하지 않을 때
			if (tops[i / 3 - 1] == 0) {
				dp[i][0] = dp[i - 1][0];
				dp[i][1] = dp[i - 1][1];
			}
			else {
				dp[i][0] = dp[i - 1][0] + dp[i - 1][1];
				dp[i][1] = dp[i - 2][0] + dp[i - 2][1];
				dp[i][0] %= 10007;
				dp[i][1] %= 10007;
			}

		}
		else if (i % 3 == 1) {
			dp[i][0] = dp[i - 1][0] + dp[i - 1][1];
			dp[i][1] = dp[i - 3][0] + dp[i - 3][1];
			dp[i][0] %= 10007;
			dp[i][1] %= 10007;
		}
		else {
			dp[i][0] = dp[i - 1][0] + dp[i - 1][1];
			dp[i][1] = dp[i - 2][0] + dp[i - 2][1];
			dp[i][0] %= 10007;
			dp[i][1] %= 10007;
		}
	}

	answer = (dp[3 * n + 1][0] + dp[3 * n + 1][1]) % 10007;
	return answer;
}