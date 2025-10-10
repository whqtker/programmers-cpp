#include <string>
#include <vector>
#include <cmath>

using namespace std;

string solution(vector<int> numbers, string hand) {
    string answer = "";

    // 왼, 오가 마지막으로 누른 숫자
    int left = 10; // *
    int right = 12; // #
    // 키패드에서 0은 11로 간주한다. 아래 공식으로 거리 계산하기 위해
    for (int i = 0; i < numbers.size(); i++) {
        int num = numbers[i];
        if (num == 0) num = 11;

        if (num == 1 || num == 4 || num == 7) {
            answer += 'L';
            left = num;
        }
        else if (num == 3 || num == 6 || num == 9) {
            answer += 'R';
            right = num;
        }
        else {
            int left_gap = abs(left - num) / 3 + abs(left - num) % 3;
            int right_gap = abs(right - num) / 3 + abs(right - num) % 3;

            if (left_gap == right_gap) {
                if (hand == "right") {
                    answer += 'R';
                    right = num;
                }
                else {
                    answer += 'L';
                    left = num;
                }
            }
            else if (left_gap < right_gap) {
                answer += 'L';
                left = num;
            }
            else {
                answer += 'R';
                right = num;
            }
        }
    }
    return answer;
}