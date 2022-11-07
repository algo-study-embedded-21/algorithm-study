#include <iostream>
#include <queue>
using namespace std;

int map[20][20];
int score[20][20];
int n, m, k;

//row, col
int dice[][4] = { { 4, 1, 3, 6 },
                { 2, 1, 5, 6 } };

int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };
int change_dir[] = { 2, 3, 0, 1 };

int x, y, d;
int ans;

void calcScore(int r, int c) {
    int num = map[r][c];
    int visited[20][20] = { 0 };
    queue<pair<int, int>> q;
    q.push({ r, c });
    visited[r][c] = 1;
    int cnt = 1;

    while (!q.empty()) {
        pair<int, int> now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = now.first + dx[i];
            int ny = now.second + dy[i];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (visited[nx][ny]) continue;
            if (map[nx][ny] != num) continue;
            visited[nx][ny] = 1;
            cnt++;
            q.push({ nx, ny });
        }
    }

    score[r][c] = cnt;
}

void roll() {
    // 굴리는 방향
    int r = 0, c = 0;
    switch (d) {
    case 0:
        r = 0; c = 0;
        break;
    case 1:
        r = 1; c = 0;
        break;
    case 2:
        r = 0; c = 1;
        break;
    case 3:
        r = 1; c = 1;
        break;
    }

    if (c == 0) {
        int temp = dice[r][3];
        for (int i = 3; i > 0; i--) {
            dice[r][i] = dice[r][i - 1];
        }
        dice[r][0] = temp;
    }
    else {
        int temp = dice[r][0];
        for (int i = 0; i < 3; i++) {
            dice[r][i] = dice[r][i + 1];
        }
        dice[r][3] = temp;
    }

    int temp = dice[r][3];
    dice[0][3] = temp; dice[1][3] = temp;
    temp = dice[r][1];
    dice[0][1] = temp; dice[1][1] = temp;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> map[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            calcScore(i, j);
        }
    }

    for (int i = 0; i < k; i++) {
        int nx = x + dx[d];
        int ny = y + dy[d];

        if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
            d = change_dir[d];
            nx = x + dx[d];
            ny = y + dy[d];
        }

        x = nx;
        y = ny;

        // 주사위 돌리기
        roll();

        if (dice[0][3] > map[x][y]) d = (d + 1) % 4;
        // d - 1로 했다가 d가 -1 됨
        else if (dice[0][3] < map[x][y]) d = (d + 3) % 4;

        // 점수 계산
        ans += (map[x][y] * score[x][y]);
    }

    cout << ans;

    return 0;
}