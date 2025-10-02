#include <string>
#include <vector>
#include <map>

using namespace std;

string solution(vector<string> survey, vector<int> choices) {
    string answer = "";

    map<char, int> m;
    for (int i = 0;i < survey.size();i++) {
        string s = survey[i];
        int n = choices[i];

        if (n > 4) {
            m[s[0]] += 4 - n;
        }
        else if (n < 4) {
            m[s[1]] += n - 4;
        }
    }

    if (m['R'] >= m['T']) answer += 'R';
    else answer += 'T';

    if (m['C'] >= m['F']) answer += 'C';
    else answer += 'F';

    if (m['J'] >= m['M']) answer += 'J';
    else answer += 'M';

    if (m['A'] >= m['N']) answer += 'A';
    else answer += 'N';

    return answer;
}