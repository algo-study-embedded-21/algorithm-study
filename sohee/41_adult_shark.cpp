#include <iostream>
#include <vector>
using namespace std;

int n, m, k;
pair<int, int> map[20][20];

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

struct shark {
	int num;
	int x, y;
	int d;
	int dir[4][4];
};

// 상어 정보를 번호 순으로 벡터에 관리
vector<shark> s;
int ans = -1;

int check() {
	for (int i = 2; i <= m; i++) {
		if (s[i].num != -1) return 0;
	}
	return 1;
}

void move(int time) {
	vector<int> nmap[20][20];

	// 상어 이동
	for (int i = 1; i <= m; i++) {
		if (s[i].num == -1) continue;

		int x = s[i].x;
		int y = s[i].y;
		int flag = 0;

		for (int j = 0; j < 4; j++) {
			int nx = x + dx[s[i].dir[s[i].d][j]];
			int ny = y + dy[s[i].dir[s[i].d][j]];

			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			if (map[nx][ny].second > time) continue;
			s[i].x = nx;
			s[i].y = ny;
			s[i].d = s[i].dir[s[i].d][j];
			nmap[nx][ny].push_back(i);
			flag = 1;
			break;
		}

		// 인접한 칸 중 냄새가 배지 않은 곳이 있으면 continue
		if (flag) continue;

		// 냄새 배지 않은 곳이 없으면 자기 냄새 찾기
		for (int j = 0; j < 4; j++) {
			int nx = x + dx[s[i].dir[s[i].d][j]];
			int ny = y + dy[s[i].dir[s[i].d][j]];

			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			if (map[nx][ny].first != i) continue;
			s[i].x = nx;
			s[i].y = ny;
			s[i].d = s[i].dir[s[i].d][j];
			nmap[nx][ny].push_back(i);
			break;
		}
	}

	// 이동 확정
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int len = nmap[i][j].size();
			if (len == 0) continue;
			// 번호 순으로 이동해서 0번이 젤 번호가 작은 상어
			map[i][j] = { nmap[i][j][0], time + k + 1 };
			// 나머진 쫓겨남
			if (len > 1) {
				for (int t = 1; t < len; t++) {
					s[nmap[i][j][t]].num = -1;
				}
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m >> k;

	// vector 사이즈 설정
	s.resize(m + 1);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int x;
			cin >> x;
			if (x == 0) continue;
			map[i][j] = { x, k };
			s[x].x = i; s[x].y = j;
		}
	}

	for (int i = 0; i < m; i++) {
		int x;
		cin >> x;
		s[i + 1].d = x - 1;
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < 4; j++) {
			for (int t = 0; t < 4; t++) {
				int x;
				cin >> x;
				s[i + 1].dir[j][t] = x - 1;
			}
		}
	}

	for (int i = 0; i <= 1000; i++) {
		if (check()) {
			ans = i;
			break;
		}

		move(i);
	}

	cout << ans;

	return 0;
}