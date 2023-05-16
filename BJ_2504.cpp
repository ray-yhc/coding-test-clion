#include <iostream>

using namespace std;

int getNum(string s) {
    int stack[30];
    int sp = 0;
    int score = 0;
    int sc = 0;
    for (char c: s) {
        switch (c) {
            case '(':
            case '[':
                stack[++sp] = (c == '(') ? -2 : -3;
                break;
            case ')':
                sc = 0;
                while (stack[sp] != -2) {
                    if (stack[sp] > 0)
                        sc += stack[sp];
                    else return 0;
                    sp--;
                }
                sp--;
                sc = (sc == 0) ? 2 : sc * 2;
                stack[++sp] = sc;
                break;
            case ']':
                sc = 0;
                while (stack[sp] != -3) {
                    if (stack[sp] > 0)
                        sc += stack[sp];
                    else return 0;
                    sp--;
                }
                sp--;
                sc = (sc == 0) ? 3 : sc * 3;
                stack[++sp] = sc;
                break;
//                if (stack[sp--] == '[')
//                    sc *= 3;
//                else return 0;
//                break;
            default:
                return 0;
        }
    }

    while (sp > 0) {
        if (stack[sp] < 0) return 0;
        score += stack[sp--];
    }

    return score;
}

int main() {

    string s;
    cin >> s;
    cout << getNum(s) << endl;

    // solved.ac
    // #implementation *g


//    freopen("input_data/2504.txt", "r", stdin);
//    int t;
//    cin >> t;
//    for (int i = 0; i < t; ++i) {
//        cin >> s;
//        cout << s << "\t" << getNum(s) << endl;
//    }

    return 0;
}