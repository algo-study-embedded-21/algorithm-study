#include <iostream>
#include <vector>
using namespace std;

int m, s;
vector<int> map[4][4];
int smell[4][4];
pair<int, int> shark;

int dx[] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int sx[] = { -1, 0, 1, 0 };
int sy[] = { 0, -1, 0, 1 };
int step[3];
int ans[3];
int fish_ans;

void dfs(int level, int fish, int x, int y) {
	if (level == 3) {
		if (fish > fish_ans) {
			for (int i = 0; i < 3; i++) ans[i] = step[i];
			fish_ans = fish;
		}
		return;
	}

	for (int i = 0; i < 4; i++) {
		int nx = x + sx[i];
		int ny = y + sy[i];

		if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4) continue;
		step[level] = i;
		// 물고기 정보 저장 및 복원 (visited 사용 x)
		vector<int> vfish(map[nx][ny]);
		map[nx][ny].clear();
		dfs(level + 1, fish + vfish.size(), nx, ny);
		map[nx][ny] = vfish;
	}
}

void magin(int time) {
	// 복제 시작
	vector<int> new_map[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			new_map[i][j] = map[i][j];
		}
	}

	// 물고기 이동
	vector<int> move_map[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int len = map[i][j].size();
			if (len == 0) continue;
			for (int k = 0; k < len; k++) {
				int flag = 1;
				for (int d = 0; d < 8; d++) {
					int nx = i + dx[(map[i][j][k] - d + 8) % 8];
					int ny = j + dy[(map[i][j][k] - d + 8) % 8];

					if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4) continue;
					if (nx == shark.first && ny == shark.second) continue;
					if (smell[nx][ny] >= time) continue;
					move_map[nx][ny].push_back((map[i][j][k] - d + 8) % 8);
					flag = 0;
					break;
				}
				if (flag) move_map[i][j].push_back(map[i][j][k]);
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			map[i][j] = move_map[i][j];
		}
	}

	// 상어 이동
	fish_ans = -1;
	ans[0] = 0, ans[1] = 0, ans[2] = 0;
	dfs(0, 0, shark.first, shark.second);

	for (int i = 0; i < 3; i++) {
		shark.first += sx[ans[i]];
		shark.second += sy[ans[i]];

		if (map[shark.first][shark.second].size() > 0) {
			smell[shark.first][shark.second] = time + 2;
		}
		map[shark.first][shark.second].clear();
	}

	// 복제 완료
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < new_map[i][j].size(); k++) {
				map[i][j].push_back(new_map[i][j][k]);
			}
		}
	}
}

int getScore() {
	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cnt += map[i][j].size();
		}
	}

	return cnt;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> m >> s;

	for (int i = 0; i < m; i++) {
		int x, y, d;
		cin >> x >> y >> d;
		map[x - 1][y - 1].push_back(d - 1);
	}

	cin >> shark.first >> shark.second;
	shark.first--; shark.second--;

	for (int i = 1; i <= s; i++) {
		magin(i);
	}

	cout << getScore();

	return 0;
}