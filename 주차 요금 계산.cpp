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

    map<string, int> m; // ������ȣ, ���� ���� �ð�
    map<string, string> in; // ������ȣ, ���� �ð�
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

    // ���� ����� �����ִٸ�
    for (auto e : in) {
        int gap = calc_gap(e.second, "23:59");
        m[e.first] += gap;
    }

    for (auto e : m) {
        int t = e.second;

        // �⺻ �ð� ���ϸ� �⺻ ��� û��
        if (t < fees[0]) {
            answer.push_back(fees[1]);
        }
        // �⺻ ���+�ʰ��� �ð��� ���Ͽ� ���� �ð� �� ���� ��� û��
        else {
            int exceeded = t - fees[0]; // �ʰ��� �ð�
            answer.push_back(fees[1] + ceil((double)exceeded / (double)fees[2]) * fees[3]);
        }
    }
    return answer;
}