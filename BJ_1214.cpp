#include <iostream>
#include <vector>
#include <cstring>

using namespace std;


int doit(int res, int p, int q, int pc, int qc, int price){
    if (price>=res) return price;

    int a = doit(res, p, q, pc + 1, qc, price + p);
    int b = doit(res, p, q, pc, qc + 1, price + q);
    return (a > b) ? b : a;
}

int main() {
    int res, a, b;
    cin >> res >> a >> b;

    cout << doit(res,a,b,0,0,0) << endl;



    return 0;
}
