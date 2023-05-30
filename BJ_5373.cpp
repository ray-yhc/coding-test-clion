#include <iostream>
#include <vector>

using namespace std;

char cube[6][3][3]{0};
char initCube[6][3][3]{
        // 0 : 윗면
        'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w',
        // 1 : 아랫면
        'y', 'y', 'y', 'y', 'y', 'y', 'y', 'y', 'y',
        // 2 : 앞
        'r', 'r', 'r', 'r', 'r', 'r', 'r', 'r', 'r',
        // 3 : 뒤
        'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
        //4 : 왼
        'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g',
        // 5 : 오
        'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b',
};

void init() {

    memcpy(cube, initCube, sizeof(char) * 6 * 3 * 3);

//    for (int i = 0; i < 6; ++i) {
//        for (int j = 0; j < 3; ++j) {
//            for (int k = 0; k < 3; ++k) {
//                cout << cube[i][j][k] << " ";
//            }
//            cout << endl;
//        }
//        cout << endl;
//    }
}

void printResult() {
    int i = 0;
    for (int j = 0; j < 3; ++j) {
        for (int k = 0; k < 3; ++k) {
            cout << cube[i][j][k] << " ";
        }
        cout << endl;
    }
}

void rotateCube(char cmd, bool dir){
    char t;

    switch (cmd) {
        case 'U':
            if (dir) { // U +
                for (int i = 0; i < 3; ++i) {
                    t = cube[2][0][i];
                    cube[2][0][i] = cube[5][0][i];
                    cube[5][0][i] = cube[3][0][i];
                    cube[3][0][i] = cube[4][0][i];
                    cube[4][0][i] = t;
                }
            } else { // U-
                for (int i = 0; i < 3; ++i) {
                    t = cube[2][0][i];
                    cube[2][0][i] = cube[4][0][i];
                    cube[4][0][i] = cube[3][0][i];
                    cube[3][0][i] = cube[5][0][i];
                    cube[5][0][i] = t;
                }
            }
            break;

        case 'D':
            break;
        case 'F':
            break;
        default:
            break;
    }




}


int main() {
//    freopen("./txts/1009.txt", "rt", stdin);

    int T, N;
    cin >> T;

    for (int t = 0; t < T; ++t) {
        cin >> N;
        for (int i = 0; i < N; ++i) {
            init();
            string s;
            cin >> s;
            rotateCube(s.at(0), (s.at(1) == '+'));

            printResult();
        }
    }
    return 0;
}