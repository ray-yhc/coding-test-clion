#include <iostream>
#include <vector>
#include <list>

using namespace std;

int solution(vector<string> inputs) {
    vector<int> tree(300, -1);

    //for (auto input: inputs) {
    for (int i = 0; i < inputs.size(); ++i) {
        string input = inputs[i];
        int root = 1;
        for (int c = 0; c < input.size()-1; ++c) {
            tree[root] = i + 1;
            root = input[c] == '0' ? (root << 2) : (root << 2 | 1);
        }
    }



    return totalPower;
}

int main() {
//    freopen("./txts/1009.txtㅇㅇ", "rt", stdin);
    cout << solution({"100110", "1001", "1001111"});
    cout << solution({"000", "1110", "01", "001", "110", "11"});
}