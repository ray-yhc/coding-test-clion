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
            cout << cube[i][j][k] ;
        }
        cout << endl;
    }
}

void printWhole() {
    cout << "=====================" <<endl;
    int i = 0;
    for (int j = 0; j < 3; ++j) {
        cout<<"    ";
        for (int k = 0; k < 3; ++k) {
            cout << cube[i][j][k];
        }
        cout << endl;
    }

    for (int j = 0; j < 3; ++j) {
        i = 4;
        for (int k = 0; k < 3; ++k)
            cout << cube[i][j][k];
        cout<<" ";
        i = 2;
        for (int k = 0; k < 3; ++k)
            cout << cube[i][j][k];
        cout<<" ";
        i = 5;
        for (int k = 0; k < 3; ++k)
            cout << cube[i][j][k];
        cout<<" ";
        i = 3;
        for (int k = 0; k < 3; ++k)
            cout << cube[i][j][k];
        cout << endl;
    }
    i = 1;
    for (int j = 0; j < 3; ++j) {
        cout<<"    ";
        for (int k = 0; k < 3; ++k) {
            cout << cube[i][j][k];
        }
        cout << endl;
    }
    cout << "=====================" <<endl;
}

void rotate(int i) {
    int t = cube[i][0][0];
    cube[i][0][0] = cube[i][2][0];
    cube[i][2][0] = cube[i][2][2];
    cube[i][2][2] = cube[i][0][2];
    cube[i][0][2] = t;

    t = cube[i][1][0];
    cube[i][1][0] = cube[i][2][1];
    cube[i][2][1] = cube[i][1][2];
    cube[i][1][2] = cube[i][0][1];
    cube[i][0][1] = t;
}

void up_clockwise() {
    char t;
    for (int i = 0; i < 3; ++i) {
        t = cube[2][0][i];
        cube[2][0][i] = cube[5][0][i];
        cube[5][0][i] = cube[3][0][i];
        cube[3][0][i] = cube[4][0][i];
        cube[4][0][i] = t;
    }
    rotate(0);
}

void down_clockwise() {
    char t;
    for (int i = 0; i < 3; ++i) {
        t = cube[4][2][i];
        cube[4][2][i] = cube[3][2][i];
        cube[3][2][i] = cube[5][2][i];
        cube[5][2][i] = cube[2][2][i];
        cube[2][2][i] = t;
    }
    rotate(1);
}
void forward_clockwise() {
    char t;
    for (int i = 0; i < 3; ++i) {
        t = cube[0][2][i];
        cube[0][2][i] = cube[4][2-i][2];
        cube[4][2-i][2] = cube[1][0][2-i];
        cube[1][0][2-i] = cube[5][i][0];
        cube[5][i][0] = t;
    }
    rotate(2);
}

void backward_clockwise() {
    char t;
    for (int i = 0; i < 3; ++i) {
        t = cube[0][0][i];
        cube[0][0][i] = cube[5][i][2];
        cube[5][i][2] = cube[1][2][2-i];
        cube[1][2][2-i] = cube[4][2-i][0];
        cube[4][2-i][0] = t;
    }
    rotate(3);
}
void right_clockwise() {
    char t;
    for (int i = 0; i < 3; ++i) {
        t = cube[2][i][2];
        cube[2][i][2] = cube[1][i][2];
        cube[1][i][2] = cube[3][2-i][0];
        cube[3][2-i][0] = cube[0][i][2];
        cube[0][i][2] = t;
    }
    rotate(5);
}
void left_clockwise() {
    char t;
    for (int i = 0; i < 3; ++i) {
        t = cube[2][i][0];
        cube[2][i][0] = cube[0][i][0];
        cube[0][i][0] = cube[3][2-i][2];
        cube[3][2-i][2] = cube[1][i][0];
        cube[1][i][0] = t;
    }
    rotate(4);
}

void rotateCube(char cmd, bool dir){

    switch (cmd) {
        case 'U':
            if (dir) { // U +
                up_clockwise();
            } else { // U-
                up_clockwise();
                up_clockwise();
                up_clockwise();
            }
            break;
        case 'D':
            if (dir) { // D +
                down_clockwise();
            } else { // D-
                down_clockwise();
                down_clockwise();
                down_clockwise();
            }
            break;
        case 'F':
            if (dir) {
                forward_clockwise();
            } else {
                forward_clockwise();
                forward_clockwise();
                forward_clockwise();
            }
            break;
        case 'B':
            if (dir) {
                backward_clockwise();
            } else {
                backward_clockwise();
                backward_clockwise();
                backward_clockwise();
            }
            break;
        case 'L':
            if (dir) {
                left_clockwise();
            } else {
                left_clockwise();
                left_clockwise();
                left_clockwise();
            }
            break;
        case 'R':
            if (dir) {
                right_clockwise();
            } else {
                right_clockwise();
                right_clockwise();
                right_clockwise();
            }
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
        init();
//        printWhole();
        cin >> N;
        for (int i = 0; i < N; ++i) {
            string s;
            cin >> s;
            rotateCube(s.at(0), (s.at(1) == '+'));

//            printWhole();
        }
        printResult();
    }
    return 0;
}