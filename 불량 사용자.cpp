#include <string>
#include <vector>
#include <map>

using namespace std;

int ans = 0; // 경우의 수

// b가 banned_id
bool match(string a, string b) {
    if (a.size() != b.size()) return false;

    for (int i = 0; i < a.size(); i++) {
        if (b[i] == '*') continue;

        if (a[i] != b[i]) return false;
    }

    return true;
}

int visited[9]; // user_id에 대한 방문 여부
map<string, int> m; // 생성된 조합에 대한 방문(중복 체크) 여부

// x: banned_id의 인덱스
void dfs(int x, const vector<string>& user_id, const vector<string>& banned_id) {
    if (x == banned_id.size()) {
        // 이미 만들어진 조합인지
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

    // user_id를 순회하며 banned_id[x]와 일치하는지
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