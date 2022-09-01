/*

���� ������ �Ķ� ������ ��ġ�� ������ bfs
���� ���� �Ķ� ���� ��ġ�� ���� �پ��� ����� ���� ���� �� ����

*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m;
int map[11][11];

struct pos {
    pair<int, int> red;
    pair<int, int> blue;
    int cnt;
};

int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };
queue<pos> q;

// flag : ���� ���� �������� �� �� ���ϱ�
// 0 : red ����
// 1 : blue ����
// -1 ��ȯ : �Ķ� ���� �Բ� ������ ���
int move(pair<int, int> ball[2], int dir, int flag, int cnt) {
    int first = flag;
    int second = (flag + 1) % 2;

    int x = ball[first].first;
    int y = ball[first].second;

    struct pos newPos = { {-1, -1}, {-1, -1}, cnt };
    // red
    int flagRed = 0;

    // ���� �Ķ� ���� ������ ������ return
    // ���� ���� ������ ������ ���
    while (1) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        if (nx < 0 || nx >= n || ny < 0 || ny >= m || map[nx][ny] == 1) {
            if (flag) newPos.blue = { x, y };
            else newPos.red = { x, y };
            break;
        }
        if (map[nx][ny] == -1) {
            if (flag) return 0;
            else {
                flagRed = 1;
                break;
            }
        }

        x = nx;
        y = ny;
    }

    x = ball[second].first;
    y = ball[second].second;

    // �ٸ� ���� �浹�ϴ��� �߰������� �˻�
    while (1) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        if (nx < 0 || nx >= n || ny < 0 || ny >= m || map[nx][ny] == 1) {
            if (flag) newPos.red = { x, y };
            else newPos.blue = { x, y };
            break;
        }
        if ((nx == newPos.red.first && ny == newPos.red.second) || (nx == newPos.blue.first && ny == newPos.blue.second)) {
            if (flag) newPos.red = { x, y };
            else newPos.blue = { x, y };
            break;
        }
        if (map[nx][ny] == -1) {
            if (flag) {
                flagRed = 1;
                break;
            }
            else return 0;
        }

        x = nx;
        y = ny;
    }

    // ���� ���� ���ۿ� ���ٸ� ����
    if (flagRed) return 1;
    
    // �� �� �� ���� ������ ���� queue�� ����
    q.push(newPos);
    return 0;
}

void bfs() {
    while (!q.empty()) {
        pos now = q.front();
        q.pop();

        if (now.cnt >= 10) {
            cout << -1;
            return;
        }

        int result = 0;
        for (int i = 0; i < 4; i++) {
            int rx = now.red.first;
            int ry = now.red.second;
            int bx = now.blue.first;
            int by = now.blue.second;

            pair<int, int> ball[2];
            ball[0] = now.red;
            ball[1] = now.blue;
            // ��, �������� ���� ���� ���
            if (i == 0 || i == 2) {
                // ���� ���� �����Ѵٸ� ��ġ�� ���� ���� ����
                if (ry == by) {
                    if (rx < bx) {
                        if (i == 0) {
                            result = move(ball, i, 1, now.cnt + 1);
                        }
                        else {
                            result = move(ball, i, 0, now.cnt + 1);
                        }
                    }
                    else {
                        if (i == 0) {
                            result = move(ball, i, 0, now.cnt + 1);
                        }
                        else {
                            result = move(ball, i, 1, now.cnt + 1);
                        }
                    }
                }
                else {
                    result = move(ball, i, 0, now.cnt + 1);
                }
            }
            // ��, �������� ���� ���� ���
            else if (i == 1 || i == 3) {
                // ���� �࿡ �����Ѵٸ� ��ġ�� ���� ���� ����
                if (rx == bx) {
                    if (ry < by) {
                        if (i == 1) {
                            result = move(ball, i, 1, now.cnt + 1);
                        }
                        else {
                            result = move(ball, i, 0, now.cnt + 1);
                        }
                    }
                    else {
                        if (i == 1) {
                            result = move(ball, i, 0, now.cnt + 1);
                        }
                        else {
                            result = move(ball, i, 1, now.cnt + 1);
                        }
                    }
                }
                else {
                    result = move(ball, i, 0, now.cnt + 1);
                }
            }

            // ���� ���� ���ۿ� �����ٸ� Ƚ�� ��� �� return
            if (result) {
                cout << now.cnt + 1;
                return;
            }
        }
    }

    cout << -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> n >> m;
    pos start;
    start.cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            if (c == '#') map[i][j] = 1;
            else if (c == 'B') start.blue = { i, j };
            else if (c == 'R') start.red = { i, j };
            else if (c == 'O') map[i][j] = -1;
        }
    }

    q.push(start);
    bfs();

    return 0;
}