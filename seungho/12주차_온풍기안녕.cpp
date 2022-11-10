#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int R, C, K, W;
int MAP[21][21];
int temp[21][21];
struct Node {
	int y; int x; int t;
};
int wall[21][21][2];

vector<Node> v;
vector<Node> check;

// 바람 퍼지는 방향배열
int diry[4][3] = {
	{-1,0,1},	// 우
	{-1,0,1},	// 좌
	{-1,-1,-1},	// 상
	{1,1,1}		// 하
};
int dirx[4][3] = {
	{1,1,1},
	{-1,-1,-1},
	{-1,0,1},
	{-1,0,1}
};

// 온풍기 바로 옆칸 구하는 방향배열
int hdiry[4] = { 0,0,-1,1 };
int hdirx[4] = { 1,-1,0,0 };

// 벽으로 바람이 막히는지 구하는 방향배열

int wdiry[4][3][2] = {
	{{-1,-1},{0,10},{1,1}},
	{{-1,-1},{0,10},{1,1}},
	{{0,-1},{-1,10},{0,1}},
	{{0,-1},{1,10},{0,1}}
};
int wdirx[4][3][2] = {
	{{0,1},{1,10},{0,1}},
	{{0,-1},{-1,10},{0,-1}},
	{{-1,-1},{0,10},{1,-1}},
	{{-1,1},{0,10},{1,1}}
};


void bfs(int y, int x, int t) {
	int visited[21][21] = { 0 };

	queue<Node> q;
	int fy = y + hdiry[t];
	int fx = x + hdirx[t];
	if (fy < 0 || fx < 0 || fy >= R || fx >= C) return;
	q.push({ fy, fx, t });
	visited[fy][fx] = 5;

	while (!q.empty()) {
		Node now = q.front();
		q.pop();
		if (visited[now.y][now.x] == 1) break;	// 1도 상승하는 칸부터는 더 퍼지지 않는다.

		for (int a = 0; a < 3; a++) {
			int ny = now.y + diry[t][a];
			int nx = now.x + dirx[t][a];
			if (ny < 0 || nx < 0 || ny >= R || nx >= C) continue;
			if (MAP[ny][nx] > 0 && MAP[ny][nx] < 5) continue;	// 온풍기 있는 칸이면 continue
			if (visited[ny][nx] > 0) continue;

			// 벽이 있으면 continue
			int flag = 0;
			for (int d = 0; d < 2; d++) {
				if (a == 1 && d == 1) continue;
				int wy = now.y + wdiry[t][a][d];
				int wx = now.x + wdirx[t][a][d];
				//if (ny < 0 || nx < 0 || ny >= R || nx >= C) continue;
			}
			if (t == 0) {
				switch (a) {
				case(0):
					if (wall[now.y][now.x][0] == 1) flag = 1;
					else if (wall[now.y - 1][now.x][1] == 1) flag = 1;
					break;
				case(1):
					if (wall[now.y][now.x][1] == 1) flag = 1;
					break;
				case(2):
					if (wall[now.y + 1][now.x][0] == 1) flag = 1;
					else if (wall[now.y + 1][now.x][1] == 1) flag = 1;
					break;
				}
			}
			else if (t == 1) {
				switch (a) {
				case(0):
					if (wall[now.y][now.x][0] == 1) flag = 1;
					else if (wall[now.y - 1][now.x - 1][1] == 1) flag = 1;
					break;
				case(1):
					if (wall[now.y][now.x - 1][1] == 1) flag = 1;
					break;
				case(2):
					if (wall[now.y + 1][now.x][0] == 1) flag = 1;
					else if (wall[now.y + 1][now.x - 1][1] == 1) flag = 1;
					break;
				}
			}
			else if (t == 2) {
				switch (a) {
				case(0):
					if (wall[now.y][now.x - 1][1] == 1) flag = 1;
					else if (wall[now.y][now.x - 1][0] == 1) flag = 1;
					break;
				case(1):
					if (wall[now.y][now.x][0] == 1) flag = 1;
					break;
				case(2):
					if (wall[now.y][now.x][1] == 1) flag = 1;
					else if (wall[now.y][now.x + 1][0] == 1) flag = 1;
					break;
				}
			}
			else {
				switch (a) {
				case(0):
					if (wall[now.y][now.x - 1][1] == 1) flag = 1;
					else if (wall[now.y + 1][now.x - 1][0] == 1) flag = 1;
					break;
				case(1):
					if (wall[now.y + 1][now.x][0] == 1) flag = 1;
					break;
				case(2):
					if (wall[now.y][now.x][1] == 1) flag = 1;
					else if (wall[now.y + 1][now.x + 1][0] == 1) flag = 1;
					break;
				}
			}

			if (flag == 1) continue;

			q.push({ ny,nx,t });
			visited[ny][nx] = visited[now.y][now.x] - 1;
			cout << "\n\nvisited: " << visited[ny][nx] << "\n\n";
			cout << "\n---------------temp---------------\n";
			for (int i = 0; i < R; i++) {
				for (int j = 0; j < C; j++) {
					cout << temp[i][j] << " ";
				}
				cout << "\n";
			}

			cout << "\n----------------------------------\n";

			cout << "\n---------------visited---------------\n";
			for (int i = 0; i < R; i++) {
				for (int j = 0; j < C; j++) {
					cout << visited[i][j] << " ";
				}
				cout << "\n";
			}

			cout << "\n----------------------------------\n";

			int aaa = 1;
		}
	}

	cout << "\n---------------visited 최종---------------\n";
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cout << visited[i][j] << " ";
		}
		cout << "\n";
	}

	cout << "\n----------------------------------\n";

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cout << temp[i][j]<<","<<visited[i][j] << " ";
			if (visited[i][j] > 0)	temp[i][j] = temp[i][j] + visited[i][j];
		}
	}
	cout << "\n";
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> R >> C >> K;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 0) continue;
			else if (MAP[i][j] == 5) {
				check.push_back({ i,j,5 });
			}
			else {
				v.push_back({ i,j,MAP[i][j] - 1 });
			}
		}
	}

	cin >> W;
	for (int i = 0; i < W; i++) {
		int x, y, t;
		cin >> x >> y >> t;
		wall[x - 1][y - 1][t] = 1;
	}

	int chocolate = 0;

	while (1) {
		// 조사 칸 검사
		int flag = 0;
		for (int c = 0; c < check.size(); c++) {
			int i = check[c].y;
			int j = check[c].x;
			if (temp[i][j] < K) {
				flag = 1;
				break;
			}
		}

		if (flag == 0) break;

		// 모든 온풍기에서 바람
		for (int m = 0; m < v.size(); m++) {
			bfs(v[m].y, v[m].x, v[m].t);
		}

		int dirdy[2] = { -1,0 };
		int dirdx[2] = { 0,1 };

		// 온도 조절
		int temp2[21][21];	// temp 복사
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				temp2[i][j] = temp[i][j];
			}
		}
		for (int i = R - 1; i >= 0; i--) {
			for (int j = 0; j < C; j++) {
				for (int d = 0; d < 2; d++) {
					int ny = i + dirdy[d];
					int nx = j + dirdx[d];
					if (ny >= R || nx >= C) continue;

					// 벽이 있으면 continue
					if (wall[i][j][d] == 1) continue;
					int dif = temp2[i][j] - temp2[ny][nx];
					if (dif > 0) {
						temp[i][j] -= abs(dif) / 4;
						temp[ny][nx] += abs(dif) / 4;
					}
					else {
						temp[i][j] += abs(dif) / 4;
						temp[ny][nx] -= abs(dif) / 4;
					}
				}
			}
		}

		// 온도 1 이상인 가장 바깥쪽 칸 온도 1씩 감소
		for (int j = 0; j < C; j++) {
			if (MAP[0][j] > 0) MAP[0][j]--;
			if (MAP[R - 1][j] > 0) MAP[R - 1][j]--;
		}
		for (int i = 1; i < R - 1; i++) {
			if (MAP[i][0] > 0) MAP[i][0]--;
			if (MAP[i][C - 1] > 0) MAP[i][C - 1]--;
		}

		// 초콜릿
		chocolate++;
		if (chocolate > 100) {
			cout << 101;
			return 0;
		}
	}

	cout << chocolate;

	return 0;
}
