#include <string>
#include <vector>
#include <iostream>

using namespace std;

string solution(string new_id) {
    string answer = "";

    // �빮�� -> �ҹ���
    for (int i = 0; i < new_id.size(); i++) {
        if (new_id[i] >= 'A' && new_id[i] <= 'Z') {
            new_id[i] = tolower(new_id[i]);
        }
    }

    // ���ǿ� ���� �ʴ� ���� ����
    for (int i = 0; i < new_id.size(); i++) {
        if ((new_id[i] < 'a' || new_id[i]>'z') && (new_id[i] < '0' || new_id[i]>'9') && new_id[i] != '-' && new_id[i] != '_' && new_id[i] != '.') {
            new_id.erase(i, 1);
            i--;
        }
    }

    // ��ħǥ ġȯ
    for (int i = 0; i < new_id.size() - 1; i++) {
        if (new_id[i] == '.' && new_id[i + 1] == '.') {
            for (int j = i + 1; j < new_id.size(); j++) {
                if (new_id[j] == '.') {
                    new_id[j] = '!';
                }
                else {
                    i = j;
                    break;
                }
            }
        }
    }
    for (int i = 0; i < new_id.size(); i++) {
        if (new_id[i] == '!') {
            new_id.erase(i, 1);
            i--;
        }
    }

    // ó���� ���� ��ħǥ��� ����
    if (new_id[0] == '.') new_id.erase(0, 1);
    if (new_id[new_id.size() - 1] == '.') new_id.erase(new_id.size() - 1, 1);

    // �� ���ڿ��̶�� a ����
    if (new_id.empty()) {
        new_id += 'a';
    }

    // 16�� �̻��̶�� 15�� ���� ���� ������ ����, �� ��ħǥ ����
    if (new_id.size() >= 16) {
        new_id.erase(15);
    }
    if (new_id[new_id.size() - 1] == '.') new_id.erase(new_id.size() - 1, 1);

    // ���� 2�� ������ ��� 3�� �� ������
    while (new_id.size() <= 2) {
        new_id += new_id[new_id.size() - 1];
    }

    answer = new_id;
    return answer;
}