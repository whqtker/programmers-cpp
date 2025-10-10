#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

long long solution(string expression) {
    long long answer = 0;

    vector<char> op = { '+','-','*' };
    sort(op.begin(), op.end());

    // operators[i] 에 해당하는 피연산자의 인덱스는 i, i+1이다.
    vector<long long> operands;
    vector<char> operators;
    string str = "";
    for (int i = 0; i < expression.size(); i++) {
        if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*') {
            operands.push_back(stoll(str));
            str = "";
            operators.push_back(expression[i]);
        }
        else {
            str += expression[i];
        }
    }
    operands.push_back(stoll(str));

    do {
        vector<long long> tmp_operands = operands;
        vector<char> tmp_operators = operators;

        for (int i = 0; i < 3; i++) {
            char cur_op = op[i];

            if (cur_op == '+') {
                for (int j = 0; j < tmp_operators.size(); j++) {
                    if (tmp_operators[j] == '+') {
                        long long ret = tmp_operands[j] + tmp_operands[j + 1];
                        tmp_operands[j] = ret;
                        tmp_operands.erase(tmp_operands.begin() + j + 1);
                        tmp_operators.erase(tmp_operators.begin() + j);
                        j--;
                    }
                }
            }
            else if (cur_op == '-') {
                for (int j = 0; j < tmp_operators.size(); j++) {
                    if (tmp_operators[j] == '-') {
                        long long ret = tmp_operands[j] - tmp_operands[j + 1];
                        tmp_operands[j] = ret;
                        tmp_operands.erase(tmp_operands.begin() + j + 1);
                        tmp_operators.erase(tmp_operators.begin() + j);
                        j--;
                    }
                }
            }
            else if (cur_op == '*') {
                for (int j = 0; j < tmp_operators.size(); j++) {
                    if (tmp_operators[j] == '*') {
                        long long ret = tmp_operands[j] * tmp_operands[j + 1];
                        tmp_operands[j] = ret;
                        tmp_operands.erase(tmp_operands.begin() + j + 1);
                        tmp_operators.erase(tmp_operators.begin() + j);
                        j--;
                    }
                }
            }
        }

        answer = max(answer, abs(tmp_operands[0]));

    } while (next_permutation(op.begin(), op.end()));

    return answer;
}