#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <cmath>

using namespace std;

int calc_gap(string start, string end) {
    int sh = stoi(start.substr(0, 2));
    int sm = stoi(start.substr(3));
    int eh = stoi(end.substr(0, 2));
    int em = stoi(end.substr(3));

    return (eh - sh) * 60 + em - sm;
}

vector<int> solution(vector<int> fees, vector<string> records) {
    vector<int> answer;

    map<string, int> m; // 차량번호, 누적 주차 시간
    map<string, string> in; // 차량번호, 입차 시간
    for (string s : records) {
        stringstream ss(s);
        string t, num, type;
        ss >> t >> num >> type;

        if (type == "IN") {
            in[num] = t;
        }
        else {
            int gap = calc_gap(in[num], t);
            m[num] += gap;
            in.erase(num);
        }
    }

    // 입차 기록이 남아있다면
    for (auto e : in) {
        int gap = calc_gap(e.second, "23:59");
        m[e.first] += gap;
    }

    for (auto e : m) {
        int t = e.second;

        // 기본 시간 이하면 기본 요금 청구
        if (t < fees[0]) {
            answer.push_back(fees[1]);
        }
        // 기본 요금+초과된 시간에 대하여 단위 시간 당 단위 요금 청구
        else {
            int exceeded = t - fees[0]; // 초과된 시간
            answer.push_back(fees[1] + ceil((double)exceeded / (double)fees[2]) * fees[3]);
        }
    }
    return answer;
}