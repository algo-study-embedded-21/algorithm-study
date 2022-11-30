#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int n, m;
int map[50][50];
int line[2500];
int d, s;
// 달팽이 배열 도는 방향
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };
// 마법 시전 방향
int sx[] = { 0, -1, 1, 0, 0 };
int sy[] = { 0, 0, 0, -1, 1 };
int balls[4];
int r, c;

void destroy() {
	int nx = r;
	int ny = c;
	for (int i = 0; i < s; i++) {
		nx += sx[d];
		ny += sy[d];

		if (nx < 0 || nx >= n || ny < 0 || ny >= n) break;
		map[nx][ny] = 0;
	}
}

void serialize() {
	int nx = r;
	int ny = c;
	int idx = 0;
	int cnt = 1;
	int dir = 0;
	int flag = 0;

	memset(line, 0, sizeof(line));

	while (1) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < cnt; k++) {
				nx += dx[dir % 4];
				ny += dy[dir % 4];

				if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
					flag = 1;
					break;
				}
				if (map[nx][ny] == 0) continue;
				line[idx++] = map[nx][ny];
			}
			dir++;
		}
		cnt++;
		if (flag) break;
	}
}

void move() {
	int idx = 0;
	vector<int> v(n * n, 0);

	for (int i = 0; i < n * n; i++) {
		if (line[i] == 0) continue;
		v[idx++] = line[i];
	}

	for (int i = 0; i < n * n; i++) line[i] = v[i];
}

int bomb() {
	int prev = -1;
	int cnt = 0;
	int flag = 1;
	for (int i = 0; i < n * n; i++) {
		// 끝나는 지점에서 한 번 더 확인
		if (line[i] == 0) {
			if (cnt >= 4) {
				flag = 0;
				for (int j = i - cnt; j < i; j++) {
					line[j] = 0;
				}
				balls[prev] += cnt;
			}
			break;
		}
		if (prev == line[i]) {
			cnt++;
		}
		else {
			if (cnt >= 4) {
				flag = 0;
				for (int j = i - cnt; j < i; j++) {
					line[j] = 0;
				}
				balls[prev] += cnt;
			}
			prev = line[i];
			cnt = 1;
		}
	}

	return flag;
}

void change() {
	vector<int> v(n * n, 0);
	int prev = line[0];
	int cnt = 1;
	int idx = 0;

	// line이 비어있는 경우 따로 처리
	if (prev == 0) {
		memset(line, 0, sizeof(line));
		return;
	}
	for (int i = 1; i < n * n; i++) {
		if (idx == (n * n) - 1) break;
		// 끝나는 지점에서 한 번 더 확인
		if (line[i] == 0) {
			v[idx++] = cnt;
			v[idx++] = prev;
			break;
		}
		if (prev == line[i]) {
			cnt++;
		}
		else {
			v[idx++] = cnt;
			v[idx++] = prev;
			prev = line[i];
			cnt = 1;
		}
	}

	for (int i = 0; i < n * n; i++) line[i] = v[i];
}

void tomap() {
	int nx = r;
	int ny = c;
	int idx = 0;
	int cnt = 1;
	int dir = 0;
	int flag = 0;

	while (1) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < cnt; k++) {
				nx += dx[dir % 4];
				ny += dy[dir % 4];

				if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
					flag = 1;
					break;
				}
				map[nx][ny] = line[idx++];
			}
			dir++;
		}
		cnt++;
		if (flag) break;
	}
}

void blizzard() {
	// 구슬 파괴
	destroy();

	// 구슬 이동
	serialize();

	// 구슬 폭발 및 이동
	while (1) {
		if (bomb()) break;
		move();
	}

	// 구슬 변화
	change();

	// map에 다시 세팅
	tomap();
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}

	r = n / 2; c = n / 2;

	for (int i = 0; i < m; i++) {
		cin >> d >> s;
		blizzard();
	}

	cout << balls[1] + 2 * balls[2] + 3 * balls[3];

	return 0;
}