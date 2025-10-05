#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    vector<int> answer;

    map<string, int> m; // id, 신고받은 수
    map<string, vector<string>> report_map; // id, 신고한 id의 벡터

    for (auto s : report) {
        stringstream ss(s);
        string reporter, reported;
        ss >> reporter >> reported;

        // 이미 reporter가 reported 신고한 경우 무효
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