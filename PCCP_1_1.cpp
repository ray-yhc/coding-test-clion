#include <string>
#include <vector>

using namespace std;

int solution(vector<int> bandage, int health, vector<vector<int>> attacks) {
    int hp = health;
    int ts = 0;

    for (auto a:attacks) {
        int attackTime = a[0];
        int attack = a[1];

        int healTime = attackTime - ts - 1;
        hp += healTime * bandage[1];
        if (healTime >= bandage[0]) hp += bandage[2] * (healTime / bandage[0]);
        if (hp > health) hp = health;

        hp -= attack;
        if (hp<=0) return -1;
        ts = attackTime;
    }

    return hp;
}