#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// ���� ���� �ø��� ���� vector�� ǥ��
vector<int> map[12][12];
int color[12][12];
int n, k;
int dx[] = { 0, 0, -1, 1 };
int dy[] = { 1, -1, 0, 0 };
// �ݴ� ������ ���� �迭
int dir_change[] = { 1, 0, 3, 2 };

// ��ǥ, ����
struct horse {
    int x, y, d;
};

horse h[10];

// 4�� �̻� ���� ĭ�� �ִٸ� ���� ��
int done() {
    for (int i = 0; i < k; i++) {
        if (map[h[i].x][h[i].y].size() >= 4) return 1;
    }
    return 0;
}

void white(int x, int y, int nx, int ny, int num) {
    int len = map[x][y].size();
    for (int i = 0; i < len; i++) {
        // �Űܾ� �� ���� ã�Ƽ�
        if (map[x][y][i] != num) continue;
        // �̵��� ĭ�� �ش� ���� �� ���� ���� ������ �ű�
        map[nx][ny].insert(map[nx][ny].end(), map[x][y].begin() + i, map[x][y].end());
        // �� ���� ��ǥ ���� ����
        for (int j = i; j < len; j++) {
            h[map[x][y][j]].x = nx;
            h[map[x][y][j]].y = ny;
        }
        // �� �ű� ������ ����
        map[x][y].erase(map[x][y].begin() + i, map[x][y].end());
        break;
    }
}

void red(int x, int y, int nx, int ny, int num) {
    int len = map[x][y].size();
    for (int i = 0; i < len; i++) {
        if (map[x][y][i] != num) continue;
        // �Űܾ� �� ������ ������ �̸� �ٲ�
        // algorithm ���̺귯�� �ʿ�
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
        // �ű� ���Ŀ��� �Ķ� ĭ�̰ų� ���� ����� ��쿣 �̵����� ����
        if (nx < 0 || nx >= n || ny < 0 || ny >= n) break;
        if (color[nx][ny] == 2) break;
        // �̵� ��ġ�� ���� ���� Ȥ�� �Ͼ� ���� ����� �Ѵٴ� ���� ��ħ
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

            // ���� ��ǥ, �̵��� ��ǥ, �̵��ϴ� �� ���� ������ �̵�
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) blue(x, y, i);
            else if (color[nx][ny] == 2) blue(x, y, i);      
            else if (color[nx][ny] == 0) white(x, y, nx, ny, i);
            else if (color[nx][ny] == 1) red(x, y, nx, ny, i);

            // ���� �����̱� ���� üũ�����ϸ�, ������ ���� ������ �Ŀ��� üũ���� ���ϰ� turn�� ����
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