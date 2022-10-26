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
    // ����� ���� ���ο� �� ����
    int n_map[8][8] = { 0 };
    memcpy(n_map, map, sizeof(int) * 8 * 8);

    for (int i = 0; i < 3; i++) {
        n_map[wall[i] / m][wall[i] % m] = 1;
    }

    // virus�� ���� �� �ִ� ĭ�� ��
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

    // ��ü ĭ - ���� �� - ���̷����� ���� ĭ�� ��
    int safe = n * m - wall_c - 3 - cnt;
    maxsize = max(maxsize, safe);
}

void dfs(int level, int start) {
    if (level == 3) {
        check();
        return;
    }

    // 2������ 1�������� �����ϰ� 3���� ��� �̱�
    // �ߺ����� �ʰ�, ������ ��� ����
    for (int i = start; i < n * m; i++) {
        // �� ���� �ƴϸ� ���� ���� �� �����Ƿ� pass
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
            // bfs ���� ���� ����
            if (map[i][j] == 2) v.push_back({ i, j });
            // �� �������� ���� ���� �� �����Ƿ� �̸� �ľ��صα�
            if (map[i][j] == 0) arr[i * m + j] = 1;
            // �⺻���� ���õ� ���� �� �ľ��ϱ�
            if (map[i][j] == 1) wall_c++;
        }
    }

    dfs(0, 0);

    cout << maxsize;

    return 0;
}