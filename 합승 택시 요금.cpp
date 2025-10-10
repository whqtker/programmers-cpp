#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int dist[201][201];

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = 1e8;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) dist[i][j] = 0;
            else dist[i][j] = 1e8;
        }
    }

    for (int i = 0; i < fares.size(); i++) {
        int x = fares[i][0];
        int y = fares[i][1];
        int w = fares[i][2];

        dist[x][y] = w;
        dist[y][x] = w;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        answer = min(answer, dist[s][i] + dist[i][a] + dist[i][b]);
    }
    return answer;
}