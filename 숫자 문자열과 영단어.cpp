#include <string>
#include <vector>
#include <map>

using namespace std;

int solution(string s) {
	int answer = 0;

	map<string, int> m;
	m["zero"] = 0;
	m["one"] = 1;
	m["two"] = 2;
	m["three"] = 3;
	m["four"] = 4;
	m["five"] = 5;
	m["six"] = 6;
	m["seven"] = 7;
	m["eight"] = 8;
	m["nine"] = 9;

	string ans = "";
	string num = ""; // ������ ����
	for (int i = 0; i < s.size(); i++) {
		char c = s[i];

		// ���ڰ� �ƴϸ�
		if (c < '0' && c>'9') {
			num += c;
		}
		else {
			// num�� �� ���ڿ��� �ƴϸ� �߰��ϰ� �� ���ڿ��� ��ȯ
			if (num != "") {
				ans += m[num] + '0';
				num = "";
			}
			ans += c;
		}
	}
	answer = stoi(ans);
	return answer;
}