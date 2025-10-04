// minimax �˰���
#include <string>
#include <vector>
#include <algorithm>

#define MAX_TURNS 26

using namespace std;

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

// return: ���� ���� �̱� �� �ִ���, �ɸ� ���� ��
pair<bool,int> dfs(int ax, int ay, int bx, int by, vector<vector<int>>& board) {
    int r = board.size(); // ���� ����
    int c = board[0].size(); // ���� ����

    // ���� ������ ������ �̹� ������ٸ� �й�
    if (board[ax][ay] == 0)
        return { false, 0 };

    bool flag = false; // ������ �� �ִ°�
    int win_turns = 26; // �ּҷ�
    int lose_turns = -1; // �ִ��

    for (int i = 0; i < 4; ++i) {
        int nx = ax + dx[i];
        int ny = ay + dy[i];

        if (nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
        if (board[nx][ny] == 0) continue;

        flag = true;

        board[ax][ay] = 0;
        pair<bool, int> result = dfs(bx, by, nx, ny, board);
        board[ax][ay] = 1;

        // �̱� �� �ִٸ� �� �ּҷ�
        if (!result.first) {
            win_turns = min(win_turns, result.second + 1);
        }
        // ���ٸ� �� �ִ��
        else {
            lose_turns = max(lose_turns, result.second + 1);
        }
    }

    // ������ �� ���� ���
    if (!flag)
        return { false, 0 };

    // �̱�� ��찡 �ִٸ�
    if (win_turns != MAX_TURNS)
        return { true, win_turns };

    // �� �� ���� �й�
    return { false, lose_turns };
}

int solution(vector<vector<int>> board, vector<int> aloc, vector<int> bloc) {
	int answer = -1;

    pair<bool, int> result = dfs(aloc[0], aloc[1], bloc[0], bloc[1], board);
    answer = result.second;
	return answer;
}