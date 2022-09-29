#include <iostream>
#include <vector>
using namespace std;

// 오, 위, 왼, 아
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };
int map[101][101];

int n, answer;

void getCnt() {
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            if (map[i][j] && map[i + 1][j] && map[i][j + 1] && map[i + 1][j + 1]) answer++;
        }
    }
}

void dfs(int level, int goal, int y, int x, vector<int> v) {
    if (level >= goal) {
        for (int el : v) {
            y += dy[el];
            x += dx[el];
            map[y][x] = 1;
        }
        return;
    }

    vector<int> new_v;

    // 90도 돌린 경로 저장
    int len = v.size();
    for (int i = len - 1; i >= 0; i--) {
        new_v.push_back((v[i] + 1) % 4);
    }

    // 기존 경로 + 추가된 경로
    v.insert(v.end(), new_v.begin(), new_v.end());

    dfs(level + 1, goal, y, x, v);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y, d, g;
        cin >> x >> y >> d >> g;
        map[y][x] = 1;
        dfs(0, g, y, x, { d });
    }

    getCnt();
    cout << answer;

    return 0;
}