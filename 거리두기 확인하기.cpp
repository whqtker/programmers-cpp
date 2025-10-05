#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

int visited[6][6];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

void clear() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			visited[i][j] = -1;
		}
	}
}

vector<int> solution(vector<vector<string>> places) {
	vector<int> answer;

	for (int i = 0; i < 5; i++) {
		bool flag = false; // 거리두기 안 지킨 사람 있는지
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				if (places[i][j][k] == 'P') {
					queue<pair<int, int>> q;
					clear();
					q.push({ j,k });
					visited[j][k] = 0;

					while (!q.empty()) {
						int x = q.front().first;
						int y = q.front().second;
						q.pop();

						if (places[i][x][y] == 'P' && visited[x][y] > 0 && visited[x][y] <= 2) {
							flag = true;
							break;
						}

						for (int dir = 0; dir < 4; dir++) {
							int nx = x + dx[dir];
							int ny = y + dy[dir];

							if (nx >= 0 && ny >= 0 && nx < 5 && ny < 5 && visited[nx][ny] == -1 && places[i][nx][ny] != 'X') {
								visited[nx][ny] = visited[x][y] + 1;
								q.push({ nx,ny });
							}
						}
						if (flag) break;
					}
				}
			}
		}

		if (flag) answer.push_back(0);
		else answer.push_back(1);
	}

	return answer;
}