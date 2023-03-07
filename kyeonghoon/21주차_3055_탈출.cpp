#include<iostream>
#include<queue>
#include<tuple>
using namespace std;

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };
int r, c,visited[50][50];
char map[50][50];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> r >> c;
	queue<pair<int, int>> q1, q2;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'S') {
				q1.push({ i,j });
				visited[i][j] = 1;
			}
			else if (map[i][j] == '*') {
				q2.push({ i,j });
			}
		}
	}
	while(1) {
		queue<pair<int, int>> t1, t2; //매초마다 맵 갱신을 위해 다음 큐를 따로 보관함 t1:고슴도치 t2:물
		//물이 앞으로 들이닥칠 곳은 고슴도치가 못 감 따라서 물부터 갱신
		while (!q2.empty()) {
			int x, y;
			tie(x, y) = q2.front(); q2.pop();
			for (int k = 0; k < 4; k++) {
				int nx = x + dx[k];
				int ny = y + dy[k];
				if (nx < 0 || nx >= r || ny < 0 || ny >= c)continue;
				if (map[nx][ny] == '*' || map[nx][ny] == 'D' || map[nx][ny] == 'X')continue;
				map[nx][ny] = '*';
				t2.push({ nx,ny });
			}
		}
		while (!q1.empty()) {
			int x, y;
			tie(x, y) = q1.front(); q1.pop();
			for (int k = 0; k < 4; k++) {
				int nx = x + dx[k];
				int ny = y + dy[k];
				if (nx < 0 || nx >= r || ny < 0 || ny >= c)continue;
				if (map[nx][ny] == '*'||map[nx][ny] == 'X'||visited[nx][ny])continue;
				if (map[nx][ny] == 'D') {//visited+1 안 하고 바로 답, 처음에 시작할 때 1초로 시작했으니
					cout << visited[x][y];
					return 0;
				}
				visited[nx][ny] = visited[x][y] + 1;
				t1.push({ nx,ny });
			}
		}
		if (t1.empty()) {
			cout << "KAKTUS";
			return 0;
		}
		while (!t1.empty()) {
			q1.push(t1.front());
			t1.pop();
		}
		while (!t2.empty()) {
			q2.push(t2.front());
			t2.pop();
		}
	}
}
