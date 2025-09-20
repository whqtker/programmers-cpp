#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Coor {
	int x;
	int y;

	Coor(int x, int y) :x(x), y(y) {}
};

// 사전 순: d -> l -> r -> u
int dx[4] = { 1,0,0,-1 };
int dy[4] = { 0,-1,1,0 };
char dir[4] = { 'd','l','r','u' };
int visited[51][51][2501]; // visited[x][y][k]: (x, y)를 k 거리로 움직였을 때 방문 여부

string solution(int n, int m, int x, int y, int r, int c, int k) {
	string answer = "";

	visited[x - 1][y - 1][0] = 1;
	queue <pair<Coor, string>> q;
	q.push({ Coor(x - 1,y - 1),answer });

	bool able = false;
	while (!q.empty()) {
		int x = q.front().first.x;
		int y = q.front().first.y;
		string s = q.front().second;
		int distance = s.size();
		q.pop();

		if (distance > k)
			break;

		if (x == r - 1 && y == c - 1 && distance == k) {
			able = true;
			answer = s;
			break;
		}

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			char nd = dir[i];

			if (0 <= nx && nx < n && 0 <= ny && ny < m && !visited[nx][ny][distance + 1]) {
				visited[nx][ny][distance + 1] = 1;
				q.push({ Coor(nx, ny), s + nd });
			}
		}
	}

	if (!able) answer = "impossible";
	return answer;
}