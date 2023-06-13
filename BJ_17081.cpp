#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <unordered_map>

using namespace std;

char map[101][101];
int N, M;


class Monster {
public:
    string name;
    bool isBoss;
    int offence;
    int defence;
    int hp;
    int exp;

    Monster(const string &name, bool isBoss, int offence, int defence, int hp, int exp) : name(name), isBoss(isBoss),
                                                                                          offence(offence),
                                                                                          defence(defence), hp(hp),
                                                                                          exp(exp) {}
};

class Object {
public:
    char type;

    explicit Object(char type) : type(type) {}
};

class AttackObject : public Object {
public:
    int value;

    AttackObject(char type, int value) : Object(type), value(value) {}
};

class DefenceObject : public Object {
public:
    int value;

    DefenceObject(char type, int value) : Object(type), value(value) {}
};

class EffectObject : public Object {
public:
    int effect;

    EffectObject(char type, const string &_effect) : Object(type) {
        effect = getItemIndex(_effect);
    }

    int getItemIndex(string itemString) {
        if (itemString == "HR") return 0;
        else if (itemString == "RE")return 1;
        else if (itemString == "CO")return 2;
        else if (itemString == "EX")return 3;
        else if (itemString == "DX")return 4;
        else if (itemString == "HU")return 5;
        else if (itemString == "CU")return 6;
    }
};

class Result {
public:
    bool isAlive;
    int type; // 0 win 1 mon 2 trap
    string from; // trap or mon name
    Result(bool isAlive, int type, const string &from) : isAlive(isAlive), type(type), from(from) {}
};

unordered_map<int, Monster *> monsterMap;
unordered_map<int, Object *> objectMap;

class Character {
public :
    int r;
    int c;
    int init_r;
    int init_c;

    int lv = 1;
    int hp = 20;
    int hp_max = 20;
    int att = 2;
    int def = 2;
    int exp = 0;
    int exp_max = 5;

    int sword = 0;
    int shild = 0;
    bool item[7]{false};
    int item_num = 0;

    Result *result;

    void init(int ir, int ic) {
        r = init_r = ir;
        c = init_c = ic;

        for (int i = 0; i < 7; ++i) {
            item[i] = false;
        }
        result = nullptr;
    }

    void revive(){
//        assert(item[1]);
        hp = hp_max;

        r = init_r;
        c = init_c;
        // 전투 중이던 몬스터가 있다면 해당 몬스터의 체력도 최대치로 회복된다

        // 소멸한 뒤에 다시 이 장신구를 얻는다면 또 착용한다.
        item[1] = false;
        item_num--;

        result = nullptr;
    }


    void checkLevelUp() {
        if (exp < exp_max) return;

        exp = 0;
        lv += 1;
        exp_max = lv * 5;

        hp_max += 5;
        hp = hp_max;
        att += 2;
        def += 2;
    }

    bool fightMon(int rr, int cc) {
        // 항상 주인공 캐릭터가 선공을 하며,
        // 한 번씩 번갈아가며 공격하여 각자 max(1, 내 공격력 - 상대의 방어력) 만큼의 데미지를 서로에게 한 번씩 입힌다.
        // 한 쪽의 체력이 0 이하가 될 경우 전투는 즉시 종료된다.

        Monster *mon = monsterMap[rr * 100 + cc];
        int myAtt = att + sword;
        int myDef = def + shild;
        int monHp = mon->hp;

        int demageToMe = mon->offence - myDef;
        if (demageToMe < 1)demageToMe = 1;
        int demageToYou = myAtt - mon->defence;
        if (demageToYou < 1) demageToYou = 1;

        int i = 0;
        bool win;
        while (i>=0) {
            if (i == 0) {// first attack
                if (mon->isBoss && item[5]) {
                    // Hunter(HU) : 보스 몬스터와 전투에 돌입하는 순간 체력을 최대치까지 회복하고, 보스 몬스터의 첫 공격에 0의 데미지를 입는다.
                    hp = hp_max;
                    // hp -= 0
                    monHp -= demageToYou;
                    if (monHp <= 0) {
                        win = true;
                        break;
                    }
                }
                if (item[2]) {
                    int demageTemp;
                    if (item[4]) {
                        demageTemp = myAtt * 3 - mon->defence;
                        if (demageTemp < 1) demageTemp = 1;
                        monHp -= demageTemp;
                    } else {
                        demageTemp = myAtt * 2 - mon->defence;
                        if (demageTemp < 1) demageTemp = 1;
                        monHp -= demageTemp;
                    }
                    if (monHp <= 0) {
                        win = true;
                        break;
                    }
                    hp -= demageToMe;
                    if (hp <= 0) {
                        win = false;
                        break;
                    }
                }
                i++;
            } else { // other attacks
                int myturns = hp / demageToMe;
                myturns = (hp % demageToMe == 0) ? myturns : myturns + 1;


                int yuturns = monHp / demageToYou;
                yuturns = (monHp % demageToYou == 0)? yuturns : yuturns+1;

                if (myturns >= yuturns) {
                    win = true;
                    int turns = yuturns;
                    monHp = monHp - demageToYou * turns;
                    turns--;
                    hp = hp - demageToMe * turns;
//                    assert(hp >0);
                } else {
                    win = false;
                    int turns = myturns;
                    monHp = monHp - demageToYou * turns;
                    hp = hp - demageToMe * turns;
//                    if (!(hp < 0))
//                        true;
                }
                break;
            }
        }

        if(win) {
            if ( mon->isBoss)
                result = new Result(true, 0, "");
            map[rr][cc] = '.';

            // HP Regeneration(HR) : 전투에서 승리할 때마다 체력을 3 회복한다. 체력은 최대 체력 수치까지만 회복된다.
            if (item[0]) hp = (hp + 3 > hp_max) ? hp_max : hp + 3;

            // Experience(EX) : 얻는 경험치가 1.2배가 된다. 소수점 아래는 버린다.
            if (item[3])
                exp += (int) (mon->exp * 1.2);
            else
                exp += mon->exp;
        } else {
            result = new Result(false, 1, mon->name);
        }

        return mon->isBoss;
    }

    void getItem(int rr, int cc) {
        Object *ob = objectMap[rr * 100 + cc];
        map[rr][cc] = '.';
        if (ob->type == 'W') {// 무기
            sword = ((AttackObject *) ob)->value;
        } else if (ob->type == 'A') {// 방어구
            shild = ((DefenceObject *) ob)->value;
        } else if (ob->type == 'O') {// 아이템
            int e = ((EffectObject *) ob)->effect;
            if (item_num >= 4 || item[e]) return;
            item_num++;
            item[e] = true;
        }
    }

    void spikeTrap() {
        int dem = 5;
        if (item[4]) dem = 1;

        hp -= dem;
        if (hp <= 0) {
            result = new Result(false, 2, "");
        }
        return;
    }

    bool move(char dir) {
        int dc[4]{1, 0, -1, 0}, dr[4]{0, -1, 0, 1};
        int di=0;
        switch (dir) {
            case 'R':
                di = 0;
                break;
            case 'U':
                di = 1;
                break;
            case 'L':
                di = 2;
                break;
            case 'D':
                di = 3;
                break;
        }
        int nr = r + dr[di];
        int nc = c + dc[di];

        // 벽
        if (nr <= 0 || nr > N || nc <= 0 || nc > M || map[nr][nc] == '#');
            // 가시함정
        else if (map[nr][nc] == '^') {
            r = nr;
            c = nc;
        }
            // 아이템
        else if (map[nr][nc] == 'B') {
            getItem(nr, nc);
            r = nr;
            c = nc;
        }
            // 몬스터
        else if (map[nr][nc] == '&' || map[nr][nc] == 'M') {
            bool isBoss = fightMon(nr, nc);
            r = nr;
            c = nc;
            if (isBoss && hp > 0) {
                checkLevelUp();
                return false;
            }
        }
        else {
            r = nr;
            c = nc;
        }

        if (map[r][c] == '^') {
            spikeTrap();
        }
        checkLevelUp();

        if (hp <= 0) {
            if (item[1]) {
                revive();
                return true;
            }
            hp = 0;
            return false;
        } else return true;
    }

    void printMap(){
        printf("============== \n");
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= M; ++j) {
                if (i==r&&j==c&&(result == nullptr || result->isAlive))
                    printf("@");
                else
                    printf("%c", map[i][j]);
            }
            printf("\n");
        }
    }
    void printResult(int turns) {
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= M; ++j) {
                if (i==r&&j==c&&(result == nullptr || result->isAlive))
                    printf("@");
                else
                    printf("%c", map[i][j]);
            }
            printf("\n");
        }

        if (hp <= 0) hp = 0;
        string res;
        if (result == nullptr)
            res = "Press any key to continue.";
        else if (result->isAlive)
            res = "YOU WIN!";
        else if (result->type == 1)
            res = "YOU HAVE BEEN KILLED BY " + result->from +"..";
        else if (result->type == 2)
            res = "YOU HAVE BEEN KILLED BY SPIKE TRAP..";

        printf("Passed Turns : %d\n"
               "LV : %d\n"
               "HP : %d/%d\n"
               "ATT : %d+%d\n"
               "DEF : %d+%d\n"
               "EXP : %d/%d\n"
               "%s",
               turns, lv, hp, hp_max, att, sword, def, shild, exp, exp_max, res.c_str());
    }
};


// . : 빈칸
// # : 벽
// & : 몬스터
// M : 보스
// ^ : 함정
// B : 아이템상자

void playGame(string steps, int initR, int initC) {
    Character hero;
    hero.init(initR, initC);

//    printf("======= start ======= \n");
    for (int i = 0; i < steps.size(); ++i) {
        bool isContinue = hero.move(steps.at(i));
        if (!isContinue) {
//            printf("======= finish ======= \n");
            hero.printResult(i + 1);
            return;
        }
//        hero.printMap();
    }
//    printf("======= finish ======= \n");
    hero.printResult(steps.size());
    return;
}

int main() {
    int K = 0, L = 0;
    cin >> N >> M;

    int initR, initC;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            cin >> map[i][j];
            if (map[i][j] == '&' || map[i][j] == 'M') {
                K++;
            } else if (map[i][j] == 'B') {
                L++;
            } else if (map[i][j] == '@') {
                initR = i;
                initC = j;
                map[i][j] = '.';
            }
        }
    }
    string move;
    cin >> move;

    string str;
    int r, c, w, a, h, e;
    char ch;
    for (int i = 0; i < K; ++i) {
        cin >> r >> c >> str >> w >> a >> h >> e;
        Monster *mon = new Monster(str, (map[r][c] == 'M'), w, a, h, e);
        monsterMap.emplace(r * 100 + c, mon);
    }
    for (int i = 0; i < L; ++i) {
        cin >> r >> c >> ch;
        Object *ob;
        if (ch == 'W') {
            cin >> w;
            ob = new AttackObject(ch, w);
        } else if (ch == 'A') {
            cin >> w;
            ob = new DefenceObject(ch, w);
        } else {
            cin >> str;
            ob = new EffectObject(ch, str);
        }
        objectMap.emplace(r * 100 + c, ob);
    }


    playGame(move, initR, initC);
    return 0;
}

