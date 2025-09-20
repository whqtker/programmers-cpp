#include <string>
#include <vector>
#include <set>

using namespace std;

bool canMakePair(set<int>& s1, set<int>& s2, int n) {
	for (auto e : s1) {
		// e�� ��Ī�� �Ǵ� ī�尡 �����Ѵٸ�
		auto iter = s2.find(n + 1 - e);
		if (iter != s2.end()) {
			s1.erase(e);
			s2.erase(*iter);
			return true;
		}
	}

	return false;
}

int solution(int coin, vector<int> cards) {
	int answer = 1;
	int n = cards.size();

	set<int> pick, draw; // ���� ī��, ���� ī��

	// n/3 �� �̱�
	for (int i = 0; i < n / 3; i++) {
		pick.insert(cards[i]);
	}

	for (int i = n / 3; i < n; i += 2) {
		draw.insert(cards[i]);
		draw.insert(cards[i + 1]);

		if (canMakePair(pick, pick, n)) {

		}
		else if (coin >= 1 && canMakePair(pick, draw, n)) {
			coin -= 1;
		}
		else if (coin >= 2 && canMakePair(draw, draw, n)) {
			coin -= 2;
		}
		else break;

		answer++;
	}

	return answer;
}