#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

int visited[26][26][4]; // 비용 저장

// 우, 하, 좌, 상
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

bool OOM(int x, int y, int n) {
    return x < 0 || y < 0 || x >= n || y >= n;
}

int solution(vector<vector<int>> board) {
    int answer = 1e9;
    int n = board.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            visited[i][j][0] = 1e9;
            visited[i][j][1] = 1e9;
            visited[i][j][2] = 1e9;
            visited[i][j][3] = 1e9;
        }
    }

    queue<tuple<int, int, int>> q; // x좌표, y좌표, 어디서 왔는지
    q.push({ 0,0,-1 });
    visited[0][0][0] = 0;
    visited[0][0][1] = 0;
    visited[0][0][2] = 0;
    visited[0][0][3] = 0;

    while (!q.empty()) {
        int x = get<0>(q.front());
        int y = get<1>(q.front());
        int dir = get<2>(q.front());
        q.pop();

        if (x == n - 1 && y == n - 1) {
            answer = min(answer, visited[x][y][dir]);
            continue;
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // 유효한 경로인 경우
            if (!OOM(nx, ny, n) && board[nx][ny] == 0) {

                // 코너인 경우: dir과 i 차이가 홀수
                if (dir != -1 && (dir - i + 4) % 2 == 1) {
                    int ncost = visited[x][y][dir] + 600;
                    if (ncost <= visited[nx][ny][i]) {
                        q.push({ nx,ny,i });
                        visited[nx][ny][i] = ncost;
                    }
                }
                else {
                    int ncost = visited[x][y][dir] + 100;
                    if (ncost <= visited[nx][ny][i]) {
                        q.push({ nx,ny,i });
                        visited[nx][ny][i] = ncost;
                    }
                }
            }
        }
    }
    return answer;
}