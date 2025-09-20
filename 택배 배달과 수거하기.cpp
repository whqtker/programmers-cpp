#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long solution(int cap, int n, vector<int> deliveries, vector<int> pickups) {
	long long answer = 0;

	int delivery_rightmost = -1;
	int pickup_rightmost = -1;
	for (int i = 0; i < n; i++) {
		if (deliveries[i])
			delivery_rightmost = i;
		if (pickups[i])
			pickup_rightmost = i;
	}

	while (delivery_rightmost >= 0 || pickup_rightmost >= 0) {
		answer += (max(delivery_rightmost, pickup_rightmost) + 1) * 2;

		int cur_delivery = 0; // ����� ��
		int cur_pickup = 0; // ������ ��
		for (int i = delivery_rightmost; i >= 0; i--) {
			if (cur_delivery > cap) break;

			int able = cap - cur_delivery; // ��� ���� ��
			int real = min(able, deliveries[i]); // ���� ��� ��
			cur_delivery += real;
			deliveries[i] -= real;

			// ���� ���� ����� �Ϸ�� ���
			if (deliveries[i] == 0 ) {
				delivery_rightmost = i - 1;
			}
			else {
				delivery_rightmost = i;
				break;
			}
		}

		for (int i = pickup_rightmost; i >= 0; i--) {
			if (cur_pickup > cap) break;
			int able = cap - cur_pickup; // ���� ���� ��
			int real = min(able, pickups[i]); // ���� ���� ��
			cur_pickup += real;
			pickups[i] -= real;

			// ���� ���� ���Ű� �Ϸ�� ���
			if (pickups[i] == 0) {
				pickup_rightmost = i - 1;
			}
			else {
				pickup_rightmost = i;
				break;
			}
		}
	}
	return answer;
}