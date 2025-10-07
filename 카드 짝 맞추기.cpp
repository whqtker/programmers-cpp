#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

bool OOM(int x, int y) {
	return x < 0 || y < 0 || x >= 4 || y >= 4;
}

int bfs(int x, int y, int a, int b, vector<vector<int>>& board) {
	int visited[4][4] = { 0 };
	queue<tuple<int, int, int>> q; // x좌표, y좌표, 이동 횟수
	q.push({ x,y,0 });
	visited[x][y] = 1;

	while (!q.empty()) {
		int x = get<0>(q.front());
		int y = get<1>(q.front());
		int cnt = get<2>(q.front());
		q.pop();

		if (x == a && y == b) {
			return cnt;
		}

		// 방향키
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (!OOM(nx, ny)&&!visited[nx][ny]) {
				q.push({ nx,ny,cnt + 1 });
				visited[nx][ny] = 1;
			}
		}

		// 컨트롤 방향키
		for (int i = 0; i < 4; i++) {
			int nx = x;
			int ny = y;
			while (1) {
				nx += dx[i];
				ny += dy[i];
				if (OOM(nx, ny)) {
					nx -= dx[i];
					ny -= dy[i];
					break;
				}
				if (board[nx][ny] != 0) {
					break;
				}
			}

			if (!visited[nx][ny]) {
				q.push({ nx,ny,cnt + 1 });
				visited[nx][ny] = 1;
			}
		}
	}

	return 1e9;
}

int solution(vector<vector<int>> board, int r, int c) {
	int answer = 1e9;

	int max_num = 0; // 가장 큰 카드 번호
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			max_num = max(max_num, board[i][j]);
		}
	}

	vector<int> v; // 방문할 카드 번호 순서
	for (int i = 1; i <= max_num; i++) {
		v.push_back(i);
	}

	do {
		vector<vector<int>> tmp = board;
		int tmp_r = r;
		int tmp_c = c;
		int cnt = 0;
		for (int i = 0; i < v.size(); i++) {
			int card = v[i];
			int x1 = -1, y1 = -1, x2 = -1, y2 = -1;
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					if (tmp[j][k] == card) {
						if (x1 == -1 && y1 == -1) {
							x1 = j;
							y1 = k;
						}
						else {
							x2 = j;
							y2 = k;
						}
					}
				}
			}
			// 현재 커서 -> 첫 번째 카드 -> 두 번째 카드까지의 최단 거리 구하기
			int dist1 = bfs(tmp_r, tmp_c, x1, y1, tmp) + bfs(x1, y1, x2, y2, tmp) + 2;

			// 현재 커서 -> 두 번째 카드 -> 첫 번째 카드까지의 최단 거리 구하기
			int dist2 = bfs(tmp_r, tmp_c, x2, y2, tmp) + bfs(x2, y2, x1, y1, tmp) + 2;

			if (dist1 < dist2) {
				cnt += dist1;
				tmp_r = x2;
				tmp_c = y2;
			}
			else {
				cnt += dist2;
				tmp_r = x1;
				tmp_c = y1;
			}

			tmp[x1][y1] = 0;
			tmp[x2][y2] = 0;
		}

		answer = min(answer, cnt);

	} while (next_permutation(v.begin(), v.end()));

	return answer;
}