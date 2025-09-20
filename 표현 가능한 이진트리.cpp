#include <string>
#include <vector>
#include <cmath>

using namespace std;

// ��������� ���� ������ �����ϴ��� Ȯ���Ѵ�.
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

    // ������ ��ȭ ����Ʈ�� ���� (n: ����� ��)
    // - ������ ����� ��ȣ�� 2^k-1 ��
    // - ���� ����� ��ȣ�� ¦��, ���� ����� ��ȣ�� Ȧ��
    // - ��Ʈ ����� ��ȣ�� (n+1)/2

    // ������ ���� �� �� ���� ����
    // - ¦�� ��Ʈ�� 0�̳� �ڽ� Ȧ�� ��Ʈ�� 1�� ���

    for (int i = 0; i < numbers.size(); i++) {
        long long cur = numbers[i];
        string binary = "";
        while (cur) {
            binary = to_string(cur % 2) + binary;
            cur /= 2;
        }

        // ��ȭ ����Ʈ�� ũ�⸦ �����ϴ� �������� ��ȯ
        while (log2(binary.size() + 1) != (int)log2(binary.size() + 1)) {
            binary = "0" + binary;
        }

        if (sol(binary)) answer.push_back(1);
        else answer.push_back(0);
    }

    return answer;
}