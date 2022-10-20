#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<tuple>
#include<cstring>
using namespace std;

int map[50][50];
int visited[50][50];
int n, m, ans=1e9;
vector<pair<int, int>> vi;
queue<pair<int, int>> q;
vector<int> turn;

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

int bfs() {
    memset(visited, -1, sizeof(visited));
    for (int i = 0; i < turn.size(); i++) {
        if (turn[i] == 1) {
            q.push({ vi[i].first,vi[i].second });
            visited[vi[i].first][vi[i].second] = 0;
        }
    }
    int ans = 0;
    while (!q.empty()) {
        int x, y;
        tie(x, y) = q.front(); q.pop();
        if (map[x][y] != 8) {
            ans = max(ans, visited[x][y]);
        }
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n)continue;
            if (map[nx][ny] == 1)continue;
            if (visited[nx][ny] != -1)continue;
            visited[nx][ny] = visited[x][y] + 1;
            q.push({ nx,ny });
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (map[i][j] == 0 && visited[i][j] == -1) {
                return 100;
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> map[i][j];
            if (map[i][j] == 2) {
                vi.push_back({ i,j });
                map[i][j] = 8;
            }
        }
    }
    int tmp = vi.size() - m;
    for (int i = 0; i < tmp; i++) {
        turn.push_back(0);
    }
    for (int i = 0; i < m; i++) {
        turn.push_back(1);
    }
    do {
        for (int i = 0; i < turn.size(); i++) {
            if (turn[i] == 1) {
                map[vi[i].first][vi[i].second] = 2;
            }
        }
        int tmp = bfs();
        ans = min(ans, tmp);
        for (int i = 0; i < turn.size(); i++) {
            if (turn[i] == 1) {
                map[vi[i].first][vi[i].second] = 8;
            }
        }
    } while (next_permutation(turn.begin(), turn.end()));
    if (ans == 100) {
        cout << -1;
        return 0;
    }
    cout << ans;

}
