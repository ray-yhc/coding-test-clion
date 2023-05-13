#include <iostream>

using namespace std;

int lastNum(int a, int b) {
    int number = 1;

    for (int i = 0; i < b; ++i) {
        number = (number * a) % 10;
    }

    return number == 0 ? 10 : number;
}

int main() {
//    freopen("./txts/1009.txt", "rt", stdin);

    int T;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        int a, b;
        cin >> a >> b;
        cout << lastNum(a, b) << endl;
    }
    return 0;
}