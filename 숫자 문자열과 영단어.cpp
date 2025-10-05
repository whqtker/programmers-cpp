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
	string num = ""; // 영문자 숫자
	for (int i = 0; i < s.size(); i++) {
		char c = s[i];

		// 숫자가 아니면
		if (c < '0' && c>'9') {
			num += c;
		}
		else {
			// num이 빈 문자열이 아니면 추가하고 빈 문자열로 변환
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