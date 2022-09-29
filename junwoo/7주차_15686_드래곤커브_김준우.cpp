#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

struct node {
    int x;
    int y;
};

int N;
int dx[] = { 0,-1,0,1 };
int dy[] = { 1,0,-1,0 };
int MAP[101][101];
int cnt;
vector<int> v[21];
vector<node> spoint;



void dragon() {

    for (int i = 0; i < N; i++) {
        node now = spoint[i];
        for (int j = 0; j < v[i].size(); j++) {
            int nx = now.x + dx[v[i][j]];
            int ny = now.y + dy[v[i][j]];

            MAP[nx][ny] = 1;
            now = { nx,ny };
        }
    }

}
void isSqr(int i, int j) {
    if (MAP[i + 1][j] && MAP[i][j + 1] && MAP[i + 1][j + 1])
        cnt++;
}

int main() {
    cin >> N;

    for (int i = 0; i < N; i++) {
        int x, y, d, g;
        cin >> x >> y >> d >> g;

        MAP[y][x] = 1;
        spoint.push_back({ y,x });
        v[i].push_back(d);

        for (int j = 0; j < g; j++) {
            for (int k = (int)(v[i].size() - 1); k >= 0; k--) {
                int num = (v[i][k] + 1) % 4;
                v[i].push_back(num);
            }
        }

    }

    dragon();

    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++) {
            if (MAP[i][j]) isSqr(i, j);
        }

    cout << cnt << endl;
}