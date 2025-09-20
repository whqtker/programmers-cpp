#include <string>
#include <vector>
#include <cmath>

using namespace std;

// 재귀적으로 문제 조건을 위반하는지 확인한다.
bool sol(string binary) {
    if (binary.size() == 1) return true;

    int root = binary.size() / 2; // 0-index

    if (binary[root] == '0' && (binary[root - (root / 2 + 1)] == '1' || binary[root + (root / 2 + 1)] == '1')) {
        return false;
    }

    return sol(binary.substr(0, root)) && sol(binary.substr(root + 1));
}

vector<int> solution(vector<long long> numbers) {
    vector<int> answer;

    // 문제의 포화 이진트리 조건 (n: 노드의 수)
    // - 마지막 노드의 번호는 2^k-1 꼴
    // - 내부 노드의 번호는 짝수, 리프 노드의 번호는 홀수
    // - 루트 노드의 번호는 (n+1)/2

    // 문제의 답이 될 수 없는 조건
    // - 짝수 비트는 0이나 자식 홀수 비트가 1인 경우

    for (int i = 0; i < numbers.size(); i++) {
        long long cur = numbers[i];
        string binary = "";
        while (cur) {
            binary = to_string(cur % 2) + binary;
            cur /= 2;
        }

        // 포화 이진트리 크기를 만족하는 이진수로 변환
        while (log2(binary.size() + 1) != (int)log2(binary.size() + 1)) {
            binary = "0" + binary;
        }

        if (sol(binary)) answer.push_back(1);
        else answer.push_back(0);
    }

    return answer;
}