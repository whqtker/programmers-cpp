#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

bool is_prime(long long num) {
	if (num < 2) return false;

	for (long long i = 2; i * i <= num; i++) {
		if (num % i == 0) return false;
	}
	return true;
}

int solution(int n, int k) {
	int answer = 0;

	// ��ȯ�� k�������� 0�� ���Ե��� �ʴ� �Ҽ��� ã��
	string str = "";
	while (n / k) {
		str += n % k + '0';
		n /= k;
	}
	str += n % k + '0';
	reverse(str.begin(), str.end());

	vector<string> ret;
	istringstream iss(str);
	string tok;
	while (getline(iss, tok, '0')) {
		ret.push_back(tok);
	}

	for (string s : ret) {
		if (!s.empty() && is_prime(stoll(s)))
			answer++;
	}
	return answer;
}