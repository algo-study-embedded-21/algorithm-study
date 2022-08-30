/*

dfs�� �κ�û�ұⰡ ���� ������ ������ ��ǥ ǥ��
4������ ��� Ȯ���ߴٴ� ���� ǥ���� ���� �߰�

*/

#include <iostream>
using namespace std;

int n, m;
int map[55][55];
int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };

void dfs(int x, int y, int dir, int start) {
	int nx = x + dx[(dir + 3) % 4];
	int ny = y + dy[(dir + 3) % 4];

	if (map[nx][ny] == 0) {
		map[nx][ny] = -1;
		dfs(nx, ny, (dir + 3) % 4, -1);
	}
	else {
		if (start == dir) {
			nx = x + dx[(dir + 2) % 4];
			ny = y + dy[(dir + 2) % 4];

			if (map[nx][ny] == 1) return;
			dfs(nx, ny, dir, -1);
		}
		else {
			if (start == -1) dfs(x, y, (dir + 3) % 4, dir);
			else dfs(x, y, (dir + 3) % 4, start);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m;
	int x, y, dir;
	cin >> x >> y >> dir;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}

	map[x][y] = -1;
	dfs(x, y, dir, -1);

	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == -1) cnt++;
		}
	}

	cout << cnt;

	return 0;
}