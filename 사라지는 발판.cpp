// minimax 알고리즘
#include <string>
#include <vector>
#include <algorithm>

#define MAX_TURNS 26

using namespace std;

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

// return: 현재 내가 이길 수 있는지, 걸린 턴의 수
pair<bool,int> dfs(int ax, int ay, int bx, int by, vector<vector<int>>& board) {
    int r = board.size(); // 세로 길이
    int c = board[0].size(); // 가로 길이

    // 현재 차례의 발판이 이미 사라졌다면 패배
    if (board[ax][ay] == 0)
        return { false, 0 };

    bool flag = false; // 움직일 수 있는가
    int win_turns = 26; // 최소로
    int lose_turns = -1; // 최대로

    for (int i = 0; i < 4; ++i) {
        int nx = ax + dx[i];
        int ny = ay + dy[i];

        if (nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
        if (board[nx][ny] == 0) continue;

        flag = true;

        board[ax][ay] = 0;
        pair<bool, int> result = dfs(bx, by, nx, ny, board);
        board[ax][ay] = 1;

        // 이길 수 있다면 턴 최소로
        if (!result.first) {
            win_turns = min(win_turns, result.second + 1);
        }
        // 진다면 턴 최대로
        else {
            lose_turns = max(lose_turns, result.second + 1);
        }
    }

    // 움직일 수 없는 경우
    if (!flag)
        return { false, 0 };

    // 이기는 경우가 있다면
    if (win_turns != MAX_TURNS)
        return { true, win_turns };

    // 그 외 전부 패배
    return { false, lose_turns };
}

int solution(vector<vector<int>> board, vector<int> aloc, vector<int> bloc) {
	int answer = -1;

    pair<bool, int> result = dfs(aloc[0], aloc[1], bloc[0], bloc[1], board);
    answer = result.second;
	return answer;
}