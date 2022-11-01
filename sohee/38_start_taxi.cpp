#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m, fuel;
int map[22][22];
// �ý� ��ġ
int tx, ty;

struct person {
    int sx, sy;
    int fx, fy;
    int cnt;
};
vector<person> p;

int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };

// �������� �̵�
void go(int num) {
    queue<person> q;
    q.push({ tx, ty, p[num].fx, p[num].fy, 0 });
    // 0���� �θ� ���ΰ� �� �������µ� ����� ���� ��� fuel���� �۾Ƽ� ���ó����
    int dist = 2134567890;
    int visited[22][22] = { 0 };
    visited[tx][ty] = 1;

    while (!q.empty()) {
        person now = q.front();
        q.pop();

        if (now.sx == now.fx && now.sy == now.fy) {
            dist = now.cnt;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nx = now.sx + dx[i];
            int ny = now.sy + dy[i];

            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if (map[nx][ny] == -1) continue;
            if (visited[nx][ny]) continue;
            visited[nx][ny] = 1;
            q.push({ nx, ny, now.fx, now.fy, now.cnt + 1 });
        }
    }

    if (fuel >= dist) {
        fuel += dist;
        // �ý� �ű� ��ġ�� ���� 
        tx = p[num].fx;
        ty = p[num].fy;
        p[num].sy = -1;
    }
    else {
        fuel = -1;
    }
}

// �մ� ����
void setPerson() {
    int pnum = 0;
    int x = 2134567890, y = 2134567890;
    int dist = 2134567890;
    queue<person> q;
    q.push({ tx, ty, 0, 0, 0 });
    int visited[22][22] = { 0 };
    // �� �κ� �����ؼ� �޸� �ʰ� ��
    visited[tx][ty] = 1;

    while (!q.empty()) {
        person now = q.front();
        q.pop();

        if (dist < now.cnt) break;
        if (map[now.sx][now.sy] > 0) {
            if (now.sx > x) continue;
            // now.sy > y�� ����ߴٰ� Ʋ��
            if (now.sx == x && now.sy > y) continue;
            pnum = map[now.sx][now.sy];
            dist = now.cnt;
            x = now.sx;
            y = now.sy;
        }

        for (int i = 0; i < 4; i++) {
            int nx = now.sx + dx[i];
            int ny = now.sy + dy[i];

            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if (map[nx][ny] == -1) continue;
            if (visited[nx][ny]) continue;
            visited[nx][ny] = 1;
            q.push({ nx, ny, 0, 0, now.cnt + 1 });
        }
    }

    if (fuel > dist) {
        fuel -= dist;
        tx = x;
        ty = y;
        map[x][y] = 0;
        go(pnum - 1);
    }
    else {
        fuel = -1;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    // �ʱ�ȭ
    cin >> n >> m >> fuel;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> map[i][j];
            if (map[i][j] == 1) map[i][j] = -1;
        }
    }
    cin >> tx >> ty;
    tx--; ty--;
    for (int i = 0; i < m; i++) {
        int sx, sy, fx, fy;
        cin >> sx >> sy >> fx >> fy;
        sx--; sy--; fx--; fy--;
        map[sx][sy] = i + 1;
        p.push_back({ sx, sy, fx, fy, 0 });
    }

    for (int i = 0; i < m; i++) {
        setPerson();
        if (fuel == -1) break;
    }

    cout << fuel;

    return 0;
}