#include <string>
#include <vector>
#include <sstream>
#include <stack>
#include <tuple>
#include <iostream>

using namespace std;

int removed[1000001]; // 삭제된 행 추적

string solution(int n, int k, vector<string> cmd) {
    string answer = "";

    stack<int> recent; // 최근에 삭제된 행 번호 k

    vector<int> prev(n); // 이전 행 추적
    vector<int> nxt(n); // 다음 행 추적

    // 존재하지 않는 행은 -1을 저장하도록
    for (int i = 0; i < n; i++) {
        prev[i] = i - 1;
        nxt[i] = i + 1;
    }
    nxt[n - 1] = -1;

    for (string s : cmd) {
        char command = s[0];

        // soft delete 방법을 취하므로 U 또는 D에서 삭제된 행을 조심해야 함
        if (command == 'U') {
            int num = stoi(s.substr(2));

            // 위로 거슬러 올라감
            for (int i = 0; i < num; i++) {
                k = prev[k];
            }
        }
        else if (command == 'D') {
            int num = stoi(s.substr(2));

            // 아래로 내려감
            for (int i = 0; i < num; i++) {
                k = nxt[k];
            }
        }
        else if (command == 'C') {
            // 현재 행 삭제
            removed[k] = 1;
            recent.push(k);

            // a->k->b에서 k 삭제하면 nxt[a]=b, prev[b]=a로 설정해주어야 함
            int previous = prev[k];
            int next = nxt[k];

            if (previous != -1) nxt[previous] = next;
            if (next != -1) prev[next] = previous;

            //cout<<k<<"행 삭제, ";
            if (next != -1) {
                k = next;
            }
            else {
                k = previous;
            }
            //cout<<"삭제 후 "<<k<<"행 선택\n";
        }
        else if (command == 'Z') {
            int recovered = recent.top();
            removed[recovered] = 0;
            recent.pop();

            // k행 복원해서 a->k->b 되었다면 복원해야 함
            int previous = prev[recovered];
            int next = nxt[recovered];

            if (previous != -1) nxt[previous] = recovered;
            if (next != -1) prev[next] = recovered;
        }
    }

    for (int i = 0; i < n; i++) {
        if (removed[i] == 1)
            answer += 'X';
        else
            answer += 'O';
    }
    return answer;
}