#include <iostream>
#include <vector>
using namespace std;

int n, m;
int map[22][22];
int visited[22][22];

// ���� ũ�Ⱑ ū �׷��� ���� ��� ��ǥ �� ũ��, ������ ��� ���� ����
int x, y, maxSize, maxRainbow;
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };
int score;

pair<int, int> dfs(int r, int c, int num) {
	pair<int, int> p;
	int cnt = 0;
	// ������ ����� ��� + 1
	int rb = map[r][c] == 0;
	visited[r][c] = 1;

	for (int i = 0; i < 4; i++) {
		int nx = r + dx[i];
		int ny = c + dy[i];

		if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
		if (visited[nx][ny]) continue;
		if (map[nx][ny] != 0 && map[nx][ny] != num) continue;
		p = dfs(nx, ny, num);
		cnt += p.first;
		rb += p.second;
	}
	return { cnt + 1, rb };
}

void findBlock() {
	// ������ ����� ���� ���ŵǸ� �ٽ� ���ؾ� ��
	vector<pair<int, int>> rainbow;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visited[i][j] = 0;
			if (map[i][j] == 0) rainbow.push_back({ i, j });
		}
	}

	maxSize = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			// �Ϲ� ����� ��쿡�� dfs
			if (map[i][j] <= 0) continue;
			if (visited[i][j]) continue;

			pair<int, int> p = dfs(i, j, map[i][j]);
			int val = p.first;
			int rb = p.second;

			// ������ ����� �湮 ó���� �ʱ�ȭ����
			// �Ʒ� continue�� �ؿ� ����� Ʋ�� 
			for (auto r : rainbow) {
				visited[r.first][r.second] = 0;
			}

			if (val < 2) continue;
			if (val < maxSize) continue;
			if (val == maxSize) {
				if (maxRainbow > rb) continue;
				if (maxRainbow == rb) {
					if (x > i) continue;
					if (x == i) {
						if (y > j) continue;
					}
				}
			}
			maxSize = val;
			maxRainbow = rb;
			x = i;
			y = j;
		}
	}
}

void removeBlock(int r, int c, int num) {
	map[r][c] = -5;
	for (int i = 0; i < 4; i++) {
		int nx = r + dx[i];
		int ny = c + dy[i];

		if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
		if (map[nx][ny] == -5) continue;
		if (map[nx][ny] != 0 && map[nx][ny] != num) continue;
		removeBlock(nx, ny, num);
	}
}

void gravity() {
	for (int j = 0; j < n; j++) {
		vector<pair<int, int>> v;
		// �� ĭ�� ������ ����� ���ڿ� ���� ��ġ�� ���
		for (int i = n - 1; i >= 0; i--) {
			if (map[i][j] == -5) continue;
			v.push_back({ map[i][j], i });
			map[i][j] = -5;
		}
		int index = n - 1;
		for (auto i : v) {
			// -1�� ��� ��ġ ����
			if (i.first == -1) {
				index = i.second;
				map[i.second][j] = -1;
			}
			// �Ϲ� ����� ������� �ױ�
			else {
				map[index][j] = i.first;
			}
			index--;
		}
	}
}

void turnLeft() {
	int nmap[22][22] = { 0 };
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			nmap[n - 1 - j][i] = map[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			map[i][j] = nmap[i][j];
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}

	while (1) {
		findBlock();
		if (maxSize == 0) break;

		score += (maxSize * maxSize);
		removeBlock(x, y, map[x][y]);
		gravity();
		turnLeft();
		gravity();
	}

	cout << score;

	return 0;
}