#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

vector<int> getList(int N) {
    vector<int> list;
    for (int number = 1; number <= N; ++number) {
//        int n = number - 1;
        int dn = 0;
        for (int n = number-1; n > 0; --n) {
            dn = n +
                 n / 1000 +
                 (n % 1000) / 100 +
                 (n % 100) / 10 +
                 (n % 10);

            if (dn == number)
                break;
        }

        if (dn == number)
            continue;
        else
            list.push_back(number);
    }
    return list;
}

int main() {
//    freopen("./input_data/2504.txt", "rt", stdin);
    vector<int> list = getList(10000);

    for (int i: list) {
        printf("%d\n", i);
    }
    return 0;
}