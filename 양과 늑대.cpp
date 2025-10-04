#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> graph[18];
int max_sheep = 0;

void dfs(int x, int sheep, int wolf, vector<int>& info, vector<int>& nxt) {
	if (wolf >= sheep) {
		return;
	}

	max_sheep = max(max_sheep, sheep);

	for (int i = 0; i < nxt.size(); i++) {
		vector<int> tmp = nxt;
		int cur = tmp[i];

		tmp.erase(tmp.begin() + i);

		for (int i = 0; i < graph[cur].size(); i++) {
			tmp.push_back(graph[cur][i]);
		}

		if (info[cur] == 0) {
			dfs(cur, sheep + 1, wolf, info, tmp);
		}
		else {
			dfs(cur, sheep, wolf + 1, info, tmp);
		}
	}
}

int solution(vector<int> info, vector<vector<int>> edges) {
	int answer = 0;

	for (int i = 0; i < edges.size(); i++) {
		graph[edges[i][0]].push_back(edges[i][1]);
	}

	vector<int> nxt;
	for (int i = 0; i < graph[0].size(); i++) {
		nxt.push_back(graph[0][i]);
	}
	dfs(0, 1, 0, info, nxt);

	answer = max_sheep;
	return answer;
}