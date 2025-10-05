#include <string>
#include <vector>
#include <sstream>
#include <stack>
#include <tuple>
#include <iostream>

using namespace std;

int removed[1000001]; // ������ �� ����

string solution(int n, int k, vector<string> cmd) {
    string answer = "";

    stack<int> recent; // �ֱٿ� ������ �� ��ȣ k

    vector<int> prev(n); // ���� �� ����
    vector<int> nxt(n); // ���� �� ����

    // �������� �ʴ� ���� -1�� �����ϵ���
    for (int i = 0; i < n; i++) {
        prev[i] = i - 1;
        nxt[i] = i + 1;
    }
    nxt[n - 1] = -1;

    for (string s : cmd) {
        char command = s[0];

        // soft delete ����� ���ϹǷ� U �Ǵ� D���� ������ ���� �����ؾ� ��
        if (command == 'U') {
            int num = stoi(s.substr(2));

            // ���� �Ž��� �ö�
            for (int i = 0; i < num; i++) {
                k = prev[k];
            }
        }
        else if (command == 'D') {
            int num = stoi(s.substr(2));

            // �Ʒ��� ������
            for (int i = 0; i < num; i++) {
                k = nxt[k];
            }
        }
        else if (command == 'C') {
            // ���� �� ����
            removed[k] = 1;
            recent.push(k);

            // a->k->b���� k �����ϸ� nxt[a]=b, prev[b]=a�� �������־�� ��
            int previous = prev[k];
            int next = nxt[k];

            if (previous != -1) nxt[previous] = next;
            if (next != -1) prev[next] = previous;

            //cout<<k<<"�� ����, ";
            if (next != -1) {
                k = next;
            }
            else {
                k = previous;
            }
            //cout<<"���� �� "<<k<<"�� ����\n";
        }
        else if (command == 'Z') {
            int recovered = recent.top();
            removed[recovered] = 0;
            recent.pop();

            // k�� �����ؼ� a->k->b �Ǿ��ٸ� �����ؾ� ��
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