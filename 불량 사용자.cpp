#include <string>
#include <vector>
#include <map>

using namespace std;

int ans = 0; // ����� ��

// b�� banned_id
bool match(string a, string b) {
    if (a.size() != b.size()) return false;

    for (int i = 0; i < a.size(); i++) {
        if (b[i] == '*') continue;

        if (a[i] != b[i]) return false;
    }

    return true;
}

int visited[9]; // user_id�� ���� �湮 ����
map<string, int> m; // ������ ���տ� ���� �湮(�ߺ� üũ) ����

// x: banned_id�� �ε���
void dfs(int x, const vector<string>& user_id, const vector<string>& banned_id) {
    if (x == banned_id.size()) {
        // �̹� ������� ��������
        string str = "";
        for (int i = 0; i < user_id.size(); i++) {
            if (visited[i]) str += user_id[i];
        }
        if (m.find(str) == m.end()) {
            ans++;
            m[str]++;
        }

        return;
    }

    // user_id�� ��ȸ�ϸ� banned_id[x]�� ��ġ�ϴ���
    for (int i = 0; i < user_id.size(); i++) {
        if (!visited[i] && match(user_id[i], banned_id[x])) {
            visited[i] = 1;
            dfs(x + 1, user_id, banned_id);
            visited[i] = 0;
        }
    }
}

int solution(vector<string> user_id, vector<string> banned_id) {
    int answer = 0;

    dfs(0, user_id, banned_id);
    answer = ans;
    return answer;
}