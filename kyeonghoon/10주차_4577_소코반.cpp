#include<iostream>
#include<vector>
using namespace std;

int r, c, sx, sy;
char map[15][15];
char dir[4] = { 'U','D','L','R' };
int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	for (int tc = 1;; tc++) {
		cin >> r >> c;
		if (r == 0 && c == 0)break;
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				cin >> map[i][j];
				if (map[i][j] == 'w'||map[i][j]=='W') {
					sx = i, sy = j;
				}
			}
		}
		string move;
		cin >> move;
		bool ok2 = false;
		for (int i = 0; i < move.size(); i++) {
			int nx, ny, d;
			for (int k = 0; k < 4; k++) {
				if (dir[k] == move[i]) {
					d = k;
					nx = sx + dx[d];
					ny = sy + dy[d];
				}
			}
			int nx2 = nx + dx[d];
			int ny2 = ny + dy[d];
			//벽인 경우
			if (map[nx][ny] == '#') {
				continue;
			}
			else if (map[nx][ny] == 'b') {
				if (map[nx2][ny2] == '#' || map[nx2][ny2] == 'B' || map[nx2][ny2] == 'b') {
					continue;
				}
				else if (map[nx2][ny2] == '.') {
					map[nx2][ny2] = 'b';
					map[nx][ny] = 'w';
					if (map[sx][sy] == 'w') {
						map[sx][sy] = '.';
					}
					else {
						map[sx][sy] = '+';
					}
					sx = nx, sy = ny;
				}
				else if (map[nx2][ny2] == '+') {
					map[nx2][ny2] = 'B';
					map[nx][ny] = 'w';
					if (map[sx][sy] == 'w') {
						map[sx][sy] = '.';
					}
					else {
						map[sx][sy] = '+';
					}
					sx = nx, sy = ny;
				}
			}
			else if (map[nx][ny] == 'B') {
				if (map[nx2][ny2] == '#' || map[nx2][ny2] == 'B' || map[nx2][ny2] == 'b') {
					continue;
				}
				else if (map[nx2][ny2] == '.') {
					map[nx2][ny2] = 'b';
					map[nx][ny] = 'W';
					if (map[sx][sy] == 'w') {
						map[sx][sy] = '.';
					}
					else {
						map[sx][sy] = '+';
					}
					sx = nx, sy = ny;
				}
				else if (map[nx2][ny2] == '+') {
					map[nx2][ny2] = 'B';
					map[nx][ny] = 'W';
					if (map[sx][sy] == 'w') {
						map[sx][sy] = '.';
					}
					else {
						map[sx][sy] = '+';
					}
					sx = nx, sy = ny;
				}
			}
			else if (map[nx][ny] == '+') {
				map[nx][ny] = 'W';
				if (map[sx][sy] == 'w') {
					map[sx][sy] = '.';
				}
				else {
					map[sx][sy] = '+';
				}
				sx = nx, sy = ny;
			}
			else {
				map[nx][ny] = 'w';
				if (map[sx][sy] == 'w') {
					map[sx][sy] = '.';
				}
				else {
					map[sx][sy] = '+';
				}
				sx = nx, sy = ny;
			}
			bool ok = false;
			for (int i = 0; i < r; i++) {
				for (int j = 0; j < c; j++) {
					if (map[i][j] == 'b') {
						ok = true;
						break;
					}
				}
				if (ok)break;
			}
			if (!ok) {
				ok2 = true;
				break;
			}
		}
		
		if (!ok2) {
			cout << "Game " << tc << ": " << "incomplete\n";
			for (int i = 0; i < r; i++) {
				for (int j = 0; j < c; j++) {
					cout << map[i][j];
				}
				cout << '\n';
			}
		}
		else {
			cout << "Game " << tc << ": " << "complete\n";
			for (int i = 0; i < r; i++) {
				for (int j = 0; j < c; j++) {
					cout << map[i][j];
				}
				cout << '\n';
			}
		}
	}

}
