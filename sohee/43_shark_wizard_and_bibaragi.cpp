#include <iostream>
#include <vector>
using namespace std;

int n, m, d, s;
int map[50][50];
int dx[] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
vector<pair<int, int>> v;
int ans;

void getAns() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ans += map[i][j];
		}
	}
}

void move() {
	// ���� ���� ��ġ ����
	int cloud[50][50] = { 0 };

	// d�������� sĭ �̵� + �� �� ����
	int len = v.size();
	for (int i = 0; i < len; i++) {
		int x = v[i].first;
		int y = v[i].second;
		// s ���� ����
		x = (x + dx[d] * (s % n) + n) % n;
		y = (y + dy[d] * (s % n) + n) % n;

		v[i] = { x, y };
		map[x][y]++;
		cloud[x][y] = 1;
	}

	// ������
	for (int i = 0; i < len; i++) {
		int x = v[i].first;
		int y = v[i].second;
		int cnt = 0;

		for (int j = 0; j < 8; j++) {
			if (j % 2 == 0) continue;
			int nx = x + dx[j];
			int ny = y + dy[j];
			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			if (map[nx][ny] == 0) continue;
			cnt++;
		}
		map[x][y] += cnt;
	}

	// ���� ���� ����
	v.erase(v.begin(), v.end());

	// �� ���� ����
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (cloud[i][j]) continue;
			if (map[i][j] < 2) continue;
			v.push_back({ i, j });
			map[i][j] -= 2;
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

	v.push_back({ n - 1, 0 }); v.push_back({ n - 1, 1 }); v.push_back({ n - 2, 0 }); v.push_back({ n - 2, 1 });

	for (int i = 0; i < m; i++) {
		cin >> d >> s;
		d--;
		move();
	}

	getAns();

	cout << ans;

	return 0;
}