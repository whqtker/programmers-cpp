#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int conv2int(string str) {
    string h = str.substr(0, 2);
    string m = str.substr(3, 2);
    string s = str.substr(6, 2);

    return stoi(s) + 60 * stoi(m) + 3600 * stoi(h);
}

string conv2str(int i) {
    int h = i / 3600;
    i %= 3600;

    int m = i / 60;
    i %= 60;

    int s = i;

    string str_h, str_m, str_s;
    if (h < 10)
        str_h = "0" + to_string(h);
    else
        str_h = to_string(h);

    if (m < 10)
        str_m = "0" + to_string(m);
    else
        str_m = to_string(m);

    if (s < 10)
        str_s = "0" + to_string(s);
    else
        str_s = to_string(s);

    return str_h + ":" + str_m + ":" + str_s;
}

string solution(string play_time, string adv_time, vector<string> logs) {
    string answer = "00:00:00";

    // 시간을 모두 초 단위로 변환
    int adt = conv2int(adv_time);
    int pt = conv2int(play_time);
    vector<int> t(pt + 1);

    // 시작 시간에는 1, 종료 시간에는 -1 할당
    for (int i = 0; i < logs.size(); i++) {
        int st = conv2int(logs[i].substr(0, 8));
        int et = conv2int(logs[i].substr(9));

        t[st] += 1;
        t[et] += -1;
    }

    // 이후 누적합 계산 -> 특정 시간에 시청 중인 사람 수 구할 수 있음
    for (int i = 1; i < t.size(); i++) {
        t[i] += t[i - 1];
    }

    // 슬라이딩 윈도우 초기 세팅
    long long sum = 0;
    for (int i = 0; i < adt; i++) {
        sum += t[i];
    }

    long long max_sum = sum;
    for (int i = adt; i < pt; i++) {
        sum += t[i] - t[i - adt];

        if (sum > max_sum) {
            max_sum = sum;
            answer = conv2str(i - adt + 1);
        }
    }

    return answer;
}