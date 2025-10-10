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

    int tot = s.size(); // ������ ������ ����

    int start = 0; // ������ ���� �ε���
    int len = gems.size(); // ������ �ּ� ����
    map<string, int> m; // ����, ���� �� ������ ��

    for (int i = 0; i < gems.size(); i++) {
        string cur = gems[i];

        // ���� ������ ������ �߰�
        m[cur]++;

        // ��� ������ ������ �����ߴٸ� start �̵���Ű�鼭 ���� �ִ��� ���
        while (m.size() == tot) {
            // ���� ���� ���� Ȯ�� �� ���� ����
            if (i - start < len) {
                len = i - start;
                answer[0] = start + 1;
                answer[1] = i + 1;
            }

            // start�� �ش��ϴ� ������ map���� ����
            m[gems[start]]--;
            if (m[gems[start]] == 0) {
                m.erase(gems[start]);
            }
            // start �̵�
            start++;
        }
    }

    return answer;
}