#include <string>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

string i2s(int x) {
	if (x < 10) return "0" + to_string(x);
	return to_string(x);
}

vector<int> solution(string today, vector<string> terms, vector<string> privacies) {
	vector<int> answer;

	// today�� ��, ��, �Ϸ� �ɰ���
	vector<int> ret; // ��, ��, ��
	istringstream iss(today);
	string token;

	while (getline(iss, token, '.')) {
		ret.push_back(stoi(token));
	}

	map<string, string> expiry_date;
	for (int i = 0; i < terms.size(); i++) {
		string term;
		string duration;
		stringstream ss(terms[i]);
		ss >> term >> duration;

		int year = ret[0];
		int month = ret[1] - stoi(duration);
		int day = ret[2];

		// �� ����� ���� ������ �ƴ� ��� ����
		while (month <= 0) {
			year--;
			month += 12;
		}

		string date = to_string(year) + "." + i2s(month) + "." + i2s(day);
		expiry_date.insert({ term,date });
	}

	for (int i = 0; i < privacies.size(); i++) {
		stringstream ss(privacies[i]);
		string date, term;
		ss >> date >> term;

		if (expiry_date[term] >= date) {
			answer.push_back(i + 1);
		}
	}
	return answer;
}