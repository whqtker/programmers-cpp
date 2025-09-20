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

		int cur_delivery = 0; // 배달한 수
		int cur_pickup = 0; // 수거한 수
		for (int i = delivery_rightmost; i >= 0; i--) {
			if (cur_delivery > cap) break;

			int able = cap - cur_delivery; // 배달 가능 양
			int real = min(able, deliveries[i]); // 실제 배달 양
			cur_delivery += real;
			deliveries[i] -= real;

			// 현재 집의 배달이 완료된 경우
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
			int able = cap - cur_pickup; // 수거 가능 양
			int real = min(able, pickups[i]); // 실제 수거 양
			cur_pickup += real;
			pickups[i] -= real;

			// 현재 집의 수거가 완료된 경우
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