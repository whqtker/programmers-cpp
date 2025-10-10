#include <string>
#include <vector>
#include <unordered_set>
#include <map>
#include <algorithm>

using namespace std;

vector<int> solution(vector<string> gems) {
    vector<int> answer = { 1,(int)gems.size() };

    unordered_set<string> s;
    for (int i = 0; i < gems.size(); i++) {
        s.insert(gems[i]);
    }

    int tot = s.size(); // 유일한 보석의 개수

    int start = 0; // 구간의 시작 인덱스
    int len = gems.size(); // 구간의 최소 길이
    map<string, int> m; // 보석, 구간 내 보석의 수

    for (int i = 0; i < gems.size(); i++) {
        string cur = gems[i];

        // 현재 보석을 구간에 추가
        m[cur]++;

        // 모든 종류의 보석을 포함했다면 start 이동시키면서 구간 최대한 축소
        while (m.size() == tot) {
            // 현재 구간 길이 확인 및 정답 갱신
            if (i - start < len) {
                len = i - start;
                answer[0] = start + 1;
                answer[1] = i + 1;
            }

            // start에 해당하는 보석을 map에서 제거
            m[gems[start]]--;
            if (m[gems[start]] == 0) {
                m.erase(gems[start]);
            }
            // start 이동
            start++;
        }
    }

    return answer;
}