#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

int n, m;
int map[8][8];
int arr[64];
vector<pair<int, int>> v;
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };
int wall[3];
int wall_c;

int maxsize = 0;

void check() {
    // 계산을 위해 새로운 맵 생성
    int n_map[8][8] = { 0 };
    memcpy(n_map, map, sizeof(int) * 8 * 8);

    for (int i = 0; i < 3; i++) {
        n_map[wall[i] / m][wall[i] % m] = 1;
    }

    // virus가 퍼질 수 있는 칸의 수
    int cnt = 0;
    for (auto p : v) {
        cnt++;
        queue<pair<int, int>> q;
        q.push({ p.first, p.second });

        while (!q.empty()) {
            pair<int, int> pa = q.front();
            q.pop();
            int x = pa.first;
            int y = pa.second;

            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                if (n_map[nx][ny] != 0) continue;

                cnt++;
                n_map[nx][ny] = 2;
                q.push({ nx, ny });
            }
        }
    }

    // 전체 칸 - 벽의 수 - 바이러스가 퍼진 칸의 수
    int safe = n * m - wall_c - 3 - cnt;
    maxsize = max(maxsize, safe);
}

void dfs(int level, int start) {
    if (level == 3) {
        check();
        return;
    }

    // 2차원을 1차원으로 생각하고 3가지 경우 뽑기
    // 중복되지 않게, 순서는 상관 없이
    for (int i = start; i < n * m; i++) {
        // 빈 곳이 아니면 벽을 세울 수 없으므로 pass
        if (arr[i] != 1) continue;
        wall[level] = i;
        dfs(level + 1, i + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> map[i][j];
            // bfs 시작 지점 저장
            if (map[i][j] == 2) v.push_back({ i, j });
            // 빈 공간에만 벽을 세울 수 있으므로 미리 파악해두기
            if (map[i][j] == 0) arr[i * m + j] = 1;
            // 기본으로 세팅된 벽의 수 파악하기
            if (map[i][j] == 1) wall_c++;
        }
    }

    dfs(0, 0);

    cout << maxsize;

    return 0;
}