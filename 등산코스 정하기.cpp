#include <string>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 1e7+1

using namespace std;

int dist[50001];
vector<pair<int, int>> graph[50001];
int isSummit[50001];

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
	// 다익스트라를 통해 gate -> summit 간 최대 경로를 구한다.
	vector<int> answer;

	for (int s : summits) {
		isSummit[s] = 1;
	}

	// 인접 리스트 구현
	for (auto v : paths) {
		for (int i = 0; i < v.size(); i++) {
			int x = v[0];
			int y = v[1];
			int w = v[2];

			graph[x].push_back({ y,w });
			graph[y].push_back({ x,w });
		}
	}

	for (int i = 1; i <= n; i++) {
		dist[i] = INF;
	}

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	for (auto g : gates) {
		dist[g] = 0;
		pq.push({ 0,g });
	}

	while (!pq.empty()) {
		int w = pq.top().first;
		int node = pq.top().second;
		pq.pop();

		if (dist[node] < w || isSummit[node])
			continue;

		for (int i = 0; i < graph[node].size(); i++) {
			int nnode = graph[node][i].first;
			int nw = max(w, graph[node][i].second);

			if (nw < dist[nnode]) {
				dist[nnode] = nw;
				pq.push({ nw,nnode });
			}
		}
	}

	answer = { 0, (int)INF };
	sort(summits.begin(), summits.end());

	for (int s : summits) {
		if (dist[s] < answer[1]) {
			answer[1] = dist[s];
			answer[0] = s;
		}
	}

	return answer;
}