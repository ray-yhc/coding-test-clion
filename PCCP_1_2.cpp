#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <iostream>

using namespace std;

int solution(vector<vector<int>> land) {
    vector<int> landSize(1,0);
    int dr[4] = {0,-1,0,1};
    int dc[4] = {1,0,-1,0};


    vector<vector<int>> visited (land.size(), vector<int> (land[0].size(), 0));
    int landIndex = 0;
    for (int i=0; i<land.size(); i++){
        for (int j=0; j<land[0].size(); j++){
            if (land[i][j] == 0) continue;
            if (visited[i][j] > 0) continue;

            queue<vector<int>> q;
            q.push({i,j});
            visited[i][j] = ++landIndex;
            int size = 1;
            while(!q.empty()) {
                int r = q.front()[0];
                int c = q.front()[1];
                q.pop();

                for (int d=0;d<4;d++){
                    int nr = r+dr[d];
                    int nc = c+dc[d];

                    if (nr<0||nr>=land.size()||nc<0||nc>=land[0].size()) continue;
                    if (land[nr][nc] == 0) continue;
                    if (visited[nr][nc]) continue;
                    visited[nr][nc] = landIndex;
                    size++;
                    q.push({nr,nc});
                }
            }
            landSize.push_back(size);
        }
    }

    int maxOil = 0;
    for (int j=0; j<land[0].size(); j++){
        unordered_set<int> landSet;
        for (int i=0; i<land.size(); i++){
            if (visited[i][j]>0){
                landSet.insert(visited[i][j]);
            }
        }
        int oil = 0;
        for (int s : landSet) oil += landSize[s];
        maxOil = max(maxOil, oil);
    }

    return maxOil;
}