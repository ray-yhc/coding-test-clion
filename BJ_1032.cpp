#include <iostream>
#include "string"
#include "vector"

using namespace std;

int lastNum(int a, int b) {
    int number = 1;

    for (int i = 0; i < b; ++i) {
        number = (number * a) % 10;
    }

    return number == 0 ? 10 : number;
}

string getPattern(vector<string> list) {
    string result = "";

    for (int i = 0; i < list.at(0).length(); ++i) {

        for (int j = 1; j < list.size(); ++j) {
            if (list.at(0).at(i) != list.at(j).at(i)) {
                result = result + "?";
                break;
            }
        }

        if (result.length() != i + 1)
            result = result + list.at(0).at(i);
    }

    return result;
}

int main() {
//    freopen("./txts/1009.txt", "rt", stdin);

    int T;
    cin >> T;
    vector<string> list;
    for (int i = 0; i < T; ++i) {
        string str;
        cin >> str;
        list.push_back(str);
    }
    cout << getPattern(list) << endl;
    return 0;
}