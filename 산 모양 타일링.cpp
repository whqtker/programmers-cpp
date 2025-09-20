#include <string>
#include <vector>

using namespace std;

// �� -> �� -> �� ���� numbering
// tops�� ��ġ�ϴ� �ﰢ������ ��ȣ�� 3�� ����� ��.
// ���� ����, ������ �ﰢ���� ��ȣ�� 3n+1
int dp[300001][2]; // dp[i][j]���� i�� ° �ﰢ���� j==0: ���ﰢ������, j==1: �������

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
		// tops�� �ش��ϴ� �ε��� ó��
		if (i % 3 == 0) {
			// tops�� �ﰢ���� �������� ���� ��
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