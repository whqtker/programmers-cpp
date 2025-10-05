#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    vector<int> answer;

    map<string, int> m; // id, �Ű���� ��
    map<string, vector<string>> report_map; // id, �Ű��� id�� ����

    for (auto s : report) {
        stringstream ss(s);
        string reporter, reported;
        ss >> reporter >> reported;

        // �̹� reporter�� reported �Ű��� ��� ��ȿ
        if (find(report_map[reporter].begin(), report_map[reporter].end(), reported) != report_map[reporter].end()) {
            continue;
        }
        m[reported]++;
        report_map[reporter].push_back(reported);
    }

    for (auto reporter : id_list) {
        int cnt = 0;
        for (auto id : report_map[reporter]) {
            if (m[id] >= k) {
                cnt++;
            }
        }

        answer.push_back(cnt);
    }
    return answer;
}