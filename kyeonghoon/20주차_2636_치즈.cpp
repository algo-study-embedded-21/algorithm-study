#include<iostream>
#include<queue>
#include<tuple>
using namespace std;

int n, m, map[100][100], cnt, ttime;
int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	queue<pair<int, int>> q;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
			if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
				map[i][j] = 3;
				q.push({ i,j });
			}
		}
	}
	bool flag = true;
	while (1) {
		flag = false;
		//공기와 접촉된 구멍 탐색
		while (!q.empty()) {
			int x, y;
			tie(x, y) = q.front(); q.pop();
			for (int k = 0; k < 4; k++) {
				int nx = x + dx[k];
				int ny = y + dy[k];
				if (nx < 0 || nx >= n || ny < 0 || ny >= m)continue;
				if (map[nx][ny] == 0) {
					map[nx][ny] = 3;
					q.push({ nx,ny });
				}
			}
		}
		//공기와 접촉된 치즈 탐색
		for (int x = 1; x < n - 1; x++) {
			for (int y = 1; y < m - 1; y++) {
				if (map[x][y] == 1) {
					cnt = 0;//앞으로 지워질 치즈가 있으니 cnt새로 갱신한다.
					flag = true;
					for (int k = 0; k < 4; k++) {
						int nx = x + dx[k];
						int ny = y + dy[k];
						if (map[nx][ny] == 3) {
							map[x][y] = 2; //곧 사라질 치즈 2로 표시
							break;
						}
					}
				}
			}
		}
		//소멸
		for (int x = 0; x < n; x++) {
			for (int y = 0; y < m; y++) {
				if (map[x][y] == 2) {
					cnt += 1;
					map[x][y] = 3;
					q.push({ x,y }); //새로 생긴 공기는 곧 치즈구멍을 공기로 바꿀 후보
				}
			}
		}
		if (!flag)break;
		ttime++;
	}
	cout << ttime << '\n' << cnt;
}
