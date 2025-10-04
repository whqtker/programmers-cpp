// imos¹ý
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int cumsum[1002][1002];

int solution(vector<vector<int>> board, vector<vector<int>> skill) {
    int answer = 0;

    for (int i = 0; i < skill.size(); i++) {
        int type = skill[i][0];
        int r1 = skill[i][1];
        int c1 = skill[i][2];
        int r2 = skill[i][3];
        int c2 = skill[i][4];
        int degree = skill[i][5];

        if (type == 1) {
            cumsum[r1][c1] += -degree;
            cumsum[r1][c2 + 1] += degree;
            cumsum[r2 + 1][c1] += degree;
            cumsum[r2 + 1][c2 + 1] += -degree;
        }
        else {
            cumsum[r1][c1] += degree;
            cumsum[r1][c2 + 1] += -degree;
            cumsum[r2 + 1][c1] += -degree;
            cumsum[r2 + 1][c2 + 1] += degree;
        }
    }

    for (int i = 0; i < board.size(); i++) {
        int cur = 0;
        for (int j = 0; j < board[i].size(); j++) {
            cur += cumsum[i][j];
            cumsum[i][j] = cur;
        }
    }

    for (int i = 0; i < board[0].size(); i++) {
        int cur = 0;
        for (int j = 0; j < board.size(); j++) {
            cur += cumsum[j][i];
            cumsum[j][i] = cur;
        }
    }

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] + cumsum[i][j] > 0)
                answer++;
        }
    }

    return answer;
}