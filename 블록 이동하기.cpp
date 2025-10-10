#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Robot {
    int x1, y1, x2, y2;
    Robot(int _x1, int _y1, int _x2, int _y2)
        : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {
    }
};

int visited[101][101][101][101];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

bool OOM(int x, int y, int n) {
    return x < 0 || y < 0 || x >= n || y >= n;
}

int solution(vector<vector<int>> board) {
    int n = board.size();

    queue<Robot> q;
    q.push(Robot(0, 0, 0, 1));
    visited[0][0][0][1] = 1;

    while (!q.empty()) {
        Robot r = q.front();
        q.pop();

        int x1 = r.x1, y1 = r.y1;
        int x2 = r.x2, y2 = r.y2;

        if ((x1 == n - 1 && y1 == n - 1) || (x2 == n - 1 && y2 == n - 1)) {
            return visited[x1][y1][x2][y2] - 1;
        }

        // 상하좌우 이동
        for (int i = 0; i < 4; i++) {
            int nx1 = x1 + dx[i], ny1 = y1 + dy[i];
            int nx2 = x2 + dx[i], ny2 = y2 + dy[i];

            if (!OOM(nx1, ny1, n) && !OOM(nx2, ny2, n) &&
                !board[nx1][ny1] && !board[nx2][ny2]) {
                if (!visited[nx1][ny1][nx2][ny2] &&
                    !visited[nx2][ny2][nx1][ny1]) {
                    visited[nx1][ny1][nx2][ny2] = visited[x1][y1][x2][y2] + 1;
                    visited[nx2][ny2][nx1][ny1] = visited[x1][y1][x2][y2] + 1;
                    q.push(Robot(nx1, ny1, nx2, ny2));
                }
            }
        }

        // 가로 배치인 경우
        if (x1 == x2) {
            // 위아래로 회전 가능
            for (int d : {-1, 1}) {
                int nx = x1 + d;
                // (x1,y1) 축 회전
                if (!OOM(nx, y1, n) && !board[nx][y1] && !board[nx][y2]) {
                    if (!visited[x1][y1][nx][y1] && !visited[nx][y1][x1][y1]) {
                        visited[x1][y1][nx][y1] = visited[x1][y1][x2][y2] + 1;
                        visited[nx][y1][x1][y1] = visited[x1][y1][x2][y2] + 1;
                        q.push(Robot(x1, y1, nx, y1));
                    }
                }
                // (x2,y2) 축 회전
                if (!OOM(nx, y2, n) && !board[nx][y1] && !board[nx][y2]) {
                    if (!visited[x2][y2][nx][y2] && !visited[nx][y2][x2][y2]) {
                        visited[x2][y2][nx][y2] = visited[x1][y1][x2][y2] + 1;
                        visited[nx][y2][x2][y2] = visited[x1][y1][x2][y2] + 1;
                        q.push(Robot(x2, y2, nx, y2));
                    }
                }
            }
        }
        // 세로 배치인 경우
        else if (y1 == y2) {
            // 좌우로 회전 가능
            for (int d : {-1, 1}) {
                int ny = y1 + d;
                // (x1,y1) 축 회전
                if (!OOM(x1, ny, n) && !board[x1][ny] && !board[x2][ny]) {
                    if (!visited[x1][y1][x1][ny] && !visited[x1][ny][x1][y1]) {
                        visited[x1][y1][x1][ny] = visited[x1][y1][x2][y2] + 1;
                        visited[x1][ny][x1][y1] = visited[x1][y1][x2][y2] + 1;
                        q.push(Robot(x1, y1, x1, ny));
                    }
                }
                // (x2,y2) 축 회전
                if (!OOM(x2, ny, n) && !board[x1][ny] && !board[x2][ny]) {
                    if (!visited[x2][y2][x2][ny] && !visited[x2][ny][x2][y2]) {
                        visited[x2][y2][x2][ny] = visited[x1][y1][x2][y2] + 1;
                        visited[x2][ny][x2][y2] = visited[x1][y1][x2][y2] + 1;
                        q.push(Robot(x2, y2, x2, ny));
                    }
                }
            }
        }
    }

    return 0;
}
