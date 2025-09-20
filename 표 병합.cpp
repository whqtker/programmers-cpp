#include <string>
#include <vector>
#include <sstream>

using namespace std;

string arr[51][51];
int parent[2501];

// 2D 좌표를 1D 좌표료 변환
int convert(int x, int y) {
    return (x - 1) * 50 + y;
}

// 1D 좌표를 2D 좌표로 변환
pair<int, int> convert(int x) {
    return { (x - 1) / 50 + 1,(x - 1) % 50 + 1 };
}

int Find(int x) {
    if (x == parent[x]) return x;
    else return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
    x = Find(x);
    y = Find(y);

    if (x != y)
        parent[y] = x;
}

vector<string> solution(vector<string> commands) {
    vector<string> answer;

    for (int i = 1; i < 2501; i++) {
        parent[i] = i;
    }

    for (int i = 0; i < commands.size(); i++) {
        stringstream ss(commands[i]);
        string cmd;
        ss >> cmd;

        if (cmd == "UPDATE") {
            string x, y, z;
            ss >> x >> y;

            // UPDATE r c value
            if (ss >> z) {
                int idx = convert(stoi(x), stoi(y));
                int p = Find(idx);
                pair<int, int> root = convert(p);
                arr[root.first][root.second] = z;
            }
            // UPDATE value1 value2
            else {
                for (int i = 1; i < 2501; i++) {
                    // root인 경우
                    if (parent[i] == i) {
                        pair<int, int> root = convert(i);

                        if (arr[root.first][root.second] == x) {
                            arr[root.first][root.second] = y;
                        }
                    }
                }
            }
        }
        else if (cmd == "MERGE") {
            string x, y, a, b;
            ss >> x >> y >> a >> b;

            int idx1 = convert(stoi(x), stoi(y));
            int idx2 = convert(stoi(a), stoi(b));

            int p1 = Find(idx1);
            int p2 = Find(idx2);

            // 셀의 부모가 다르면 병합
            if (p1 != p2) {
                pair<int, int> root1 = convert(p1);
                pair<int, int> root2 = convert(p2);

                // 두 셀 중 한 셀이 값을 가지면 해당 셀로 값을 모두 할당
                string val = arr[root1.first][root1.second];
                if (val.empty()) val = arr[root2.first][root2.second];

                // p1을 새로운 루트로 하여 병합
                Union(p1, p2);

                // 새로운 루트에 값 할당
                arr[root1.first][root1.second] = val;
                arr[root2.first][root2.second].clear();
            }
        }
        else if (cmd == "UNMERGE") {
            string x, y;
            ss >> x >> y;

            int idx = convert(stoi(x), stoi(y));
            int p = Find(idx);
            pair<int, int> root = convert(p);
            string val = arr[root.first][root.second];

            vector<int> unmerge;
            for (int i = 1; i <= 2500; i++) {
                if (Find(i) == p) {
                    unmerge.push_back(i);
                }
            }

            for (int j : unmerge) {
                parent[j] = j;
                pair<int, int> root = convert(j);
                arr[root.first][root.second] = "";
            }

            arr[stoi(x)][stoi(y)] = val;
        }
        else if (cmd == "PRINT") {
            string x, y;
            ss >> x >> y;

            int idx = convert(stoi(x), stoi(y));
            int p = Find(idx);
            pair<int, int> root = convert(p);

            if (arr[root.first][root.second] == "") {
                answer.push_back("EMPTY");
            }
            else answer.push_back(arr[root.first][root.second]);
        }
    }
    return answer;
}