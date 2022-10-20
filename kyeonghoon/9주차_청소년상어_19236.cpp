#include<iostream>
using namespace std;

int dx[] = { -1,-1,0,1,1,1,0,-1 };
int dy[] = { 0,-1,-1,-1,0,1,1,1 };
int fish[4][4];
int dir[4][4];
int ans;

void copy_map(int a[4][4],int b[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			b[i][j] = a[i][j];
		}
	}
}

void move_fish(int sx,int sy) {
	for (int num = 1; num <= 16; num++) {
		int x = -1, y = -1;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (fish[i][j] == num) {
					x = i, y = j;
					break;
				}
			}
		}
		if (x == -1 && y == -1)continue;
		int ndir = dir[x][y];
		for (int k = 0; k < 8; k++) {
			ndir = (ndir + k) % 8;
			int nx = x + dx[ndir];
			int ny = y + dy[ndir];
			if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4)continue;
			if (nx == sx && ny == sy)continue;
			if (fish[nx][ny] == 0) {
				fish[nx][ny] = num;
				dir[nx][ny] = ndir;
				fish[x][y] = 0;
				break;
			}
			else {
				fish[x][y] = fish[nx][ny];
				dir[x][y] = dir[nx][ny];
				fish[nx][ny] = num;
				dir[nx][ny] = ndir;
				break;
			}
		}
	}
}

void dfs(int x,int y,int sdir,int sum) {
	ans = max(ans, sum);
	int tmp[4][4] = { 0 };
	int tmp2[4][4] = { 0 };
	copy_map(fish, tmp);
	copy_map(dir, tmp2);
	move_fish(x,y);
	
	for (int i = 1; i <= 3; i++) {
		int nx = x + dx[sdir] * i;
		int ny = y + dy[sdir] * i;
		if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4)break;
		if (fish[nx][ny] == 0)continue;
		int num = fish[nx][ny];
		fish[nx][ny] = 0;
		dfs(nx, ny, dir[nx][ny], sum + num);
		fish[nx][ny] = num;
	}
	copy_map(tmp, fish);
	copy_map(tmp2, dir);
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cin >> fish[i][j] >> dir[i][j];
			dir[i][j] -= 1;
		}
	}
	int tmp = fish[0][0];
	fish[0][0] = 0;
	dfs(0,0,dir[0][0],tmp);
	cout << ans;
}
