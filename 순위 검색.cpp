#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> solution(vector<string> info, vector<string> query) {
	vector<int> answer;

	map<string, vector<int>> m;
	for (int i = 0; i < info.size(); i++) {
		string lan, pos, career, food, score;
		stringstream ss(info[i]);
		ss >> lan >> pos >> career >> food >> score;

		m[lan + pos + career + food].push_back(stoi(score));

		// '-' 경우 고려
		string hyphen = "-";
		m[hyphen + pos + career + food].push_back(stoi(score));
		m[lan + hyphen + career + food].push_back(stoi(score));
		m[lan + pos + hyphen + food].push_back(stoi(score));
		m[lan + pos + career + hyphen].push_back(stoi(score));

		m[hyphen + hyphen + career + food].push_back(stoi(score));
		m[lan + hyphen + hyphen + food].push_back(stoi(score));
		m[lan + pos + hyphen + hyphen].push_back(stoi(score));
		m[hyphen + pos + career + hyphen].push_back(stoi(score));
		m[hyphen + pos + hyphen + food].push_back(stoi(score));
		m[lan + hyphen + career + hyphen].push_back(stoi(score));

		m[hyphen + hyphen + hyphen + food].push_back(stoi(score));
		m[lan + hyphen + hyphen + hyphen].push_back(stoi(score));
		m[hyphen + pos + hyphen + hyphen].push_back(stoi(score));
		m[hyphen + hyphen + career + hyphen].push_back(stoi(score));

		m[hyphen + hyphen + hyphen + hyphen].push_back(stoi(score));
	}

	for (auto& it : m) {
		sort(it.second.begin(), it.second.end());
	}

	for (int i = 0; i < query.size(); i++) {
		vector<string> token;
		string tok;
		istringstream iss(query[i]);
		int cnt = 0;

		while (getline(iss, tok, ' ')) {
			token.push_back(tok);
		}

		string lan = token[0];
		string pos = token[2];
		string career = token[4];
		string food = token[6];
		string score = token[7];

		vector<int> scores = m[lan + pos + career + food];
		int idx = lower_bound(scores.begin(), scores.end(), stoi(score)) - scores.begin();

		answer.push_back(scores.size() - idx);
	}
	return answer;
}