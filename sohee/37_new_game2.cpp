#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// 말을 겹쳐 올리는 것을 vector로 표현
vector<int> map[12][12];
int color[12][12];
int n, k;
int dx[] = { 0, 0, -1, 1 };
int dy[] = { 1, -1, 0, 0 };
// 반대 방향을 담은 배열
int dir_change[] = { 1, 0, 3, 2 };

// 좌표, 방향
struct horse {
    int x, y, d;
};

horse h[10];

// 4개 이상 쌓인 칸이 있다면 게임 끝
int done() {
    for (int i = 0; i < k; i++) {
        if (map[h[i].x][h[i].y].size() >= 4) return 1;
    }
    return 0;
}

void white(int x, int y, int nx, int ny, int num) {
    int len = map[x][y].size();
    for (int i = 0; i < len; i++) {
        // 옮겨야 할 말을 찾아서
        if (map[x][y][i] != num) continue;
        // 이동할 칸에 해당 말과 그 위에 쌓인 말들을 옮김
        map[nx][ny].insert(map[nx][ny].end(), map[x][y].begin() + i, map[x][y].end());
        // 각 말의 좌표 정보 갱신
        for (int j = i; j < len; j++) {
            h[map[x][y][j]].x = nx;
            h[map[x][y][j]].y = ny;
        }
        // 다 옮긴 말들은 삭제
        map[x][y].erase(map[x][y].begin() + i, map[x][y].end());
        break;
    }
}

void red(int x, int y, int nx, int ny, int num) {
    int len = map[x][y].size();
    for (int i = 0; i < len; i++) {
        if (map[x][y][i] != num) continue;
        // 옮겨야 할 말들의 순서를 미리 바꿈
        // algorithm 라이브러리 필요
        reverse(map[x][y].begin() + i, map[x][y].end());
        map[nx][ny].insert(map[nx][ny].end(), map[x][y].begin() + i, map[x][y].end());
        for (int j = i; j < len; j++) {
            h[map[x][y][j]].x = nx;
            h[map[x][y][j]].y = ny;
        }
        map[x][y].erase(map[x][y].begin() + i, map[x][y].end());
        break;
    }
}

void blue(int x, int y, int num) {
    int len = map[x][y].size();
    for (int i = 0; i < len; i++) {
        if (map[x][y][i] != num) continue;
        h[num].d = dir_change[h[num].d];
        int nx = x + dx[h[num].d];
        int ny = y + dy[h[num].d];
        // 옮긴 이후에도 파란 칸이거나 맵을 벗어나는 경우엔 이동하지 않음
        if (nx < 0 || nx >= n || ny < 0 || ny >= n) break;
        if (color[nx][ny] == 2) break;
        // 이동 위치에 따라 빨강 혹은 하양 룰을 따라야 한다는 점을 놓침
        if (color[nx][ny] == 1) red(x, y, nx, ny, num);
        if (color[nx][ny] == 0) white(x, y, nx, ny, num);
        break;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> color[i][j];
        }
    }
    for (int i = 0; i < k; i++) {
        int x, y, d;
        cin >> x >> y >> d;
        x--; y--; d--;
        h[i] = { x, y, d };
        map[x][y].push_back(i);
    }

    int turn = 1;
    int flag = 0;
    while (turn <= 1000) {
        for (int i = 0; i < k; i++) {
            int x = h[i].x;
            int y = h[i].y;
            int d = h[i].d;
            int nx = x + dx[d];
            int ny = y + dy[d];

            // 현재 좌표, 이동할 좌표, 이동하는 말 정보 가지고 이동
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) blue(x, y, i);
            else if (color[nx][ny] == 2) blue(x, y, i);      
            else if (color[nx][ny] == 0) white(x, y, nx, ny, i);
            else if (color[nx][ny] == 1) red(x, y, nx, ny, i);

            // 말을 움직이기 전에 체크부터하면, 마지막 말을 움직인 후에는 체크하지 못하고 turn이 증가
            if (done()) {
                flag = 1;
                break;
            }
        }

        if (flag) break;

        turn++;
    }

    if (turn > 1000) turn = -1;
    cout << turn;

    return 0;
}