#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int dx[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[] = { 0, -1, -1, -1, 0, 1, 1, 1 };

struct node {
	int num;
	int d;
};

int maxscore;

void dfs(vector<vector<node>> map, pair<int, int> shark, int score) {
	// 물고기 이동
	for (int i = 1; i <= 16; i++) {
		int x = -1;
		int y = -1;
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				if (map[j][k].num == i) {
					x = j;
					y = k;
				}
			}
		}
		// 먹힌 물고기면 pass
		if (x == -1 && y == -1) continue;
		int d = map[x][y].d;

		// 갈 수 있는 방향으로 이동
		for (int j = 0; j < 8; j++) {
			int nd = (d + j) % 8;
			int nx = x + dx[nd];
			int ny = y + dy[nd];

			if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4) continue;
			if (nx == shark.first && ny == shark.second) continue;
			int temp_n = map[x][y].num;
			// 움직인 방향으로 갱신
			int temp_d = nd;
			map[x][y].num = map[nx][ny].num;
			map[x][y].d = map[nx][ny].d;
			map[nx][ny].num = temp_n;
			map[nx][ny].d = temp_d;

			break;
		}
	}

	// 상어 이동
	int x = shark.first;
	int y = shark.second;
	int d = map[x][y].d;
	for (int i = 1; i < 4; i++) {
		int nx = x + dx[d] * i;
		int ny = y + dy[d] * i;

		// 상하좌우대각선 다 해도 많이 움직여 봐야 3칸
		if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4) {
			maxscore = max(maxscore, score);
			continue;
		}
		if (map[nx][ny].num == -1) continue;
		// 이동한 경우
		vector<vector<node>> n_map(4, vector<node>(4));
		copy(map.begin(), map.end(), n_map.begin());
		int n_score = score;
		n_score += n_map[nx][ny].num;
		n_map[nx][ny].num = -1;
		dfs(n_map, { nx, ny }, n_score);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();
	
	vector<vector<node>> map(4, vector<node>(4));
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int n, d;
			cin >> n >> d;
			map[i][j] = { n, d - 1 };
		}
	}

	int score = 0;
	score += map[0][0].num;
	map[0][0].num = -1;

	dfs(map, { 0, 0 }, score);
	
	cout << maxscore;

	return 0;
}