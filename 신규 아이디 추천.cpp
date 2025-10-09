#include <string>
#include <vector>
#include <iostream>

using namespace std;

string solution(string new_id) {
    string answer = "";

    // 대문자 -> 소문자
    for (int i = 0; i < new_id.size(); i++) {
        if (new_id[i] >= 'A' && new_id[i] <= 'Z') {
            new_id[i] = tolower(new_id[i]);
        }
    }

    // 조건에 맞지 않는 문자 제거
    for (int i = 0; i < new_id.size(); i++) {
        if ((new_id[i] < 'a' || new_id[i]>'z') && (new_id[i] < '0' || new_id[i]>'9') && new_id[i] != '-' && new_id[i] != '_' && new_id[i] != '.') {
            new_id.erase(i, 1);
            i--;
        }
    }

    // 마침표 치환
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

    // 처음과 끝이 마침표라면 제거
    if (new_id[0] == '.') new_id.erase(0, 1);
    if (new_id[new_id.size() - 1] == '.') new_id.erase(new_id.size() - 1, 1);

    // 빈 문자열이라면 a 대입
    if (new_id.empty()) {
        new_id += 'a';
    }

    // 16자 이상이라면 15개 문자 제외 나머지 제거, 끝 마침표 제거
    if (new_id.size() >= 16) {
        new_id.erase(15);
    }
    if (new_id[new_id.size() - 1] == '.') new_id.erase(new_id.size() - 1, 1);

    // 길이 2자 이하인 경우 3이 될 때까지
    while (new_id.size() <= 2) {
        new_id += new_id[new_id.size() - 1];
    }

    answer = new_id;
    return answer;
}