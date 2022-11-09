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

int diryR[3] = { -1,0,1 };
int dirxR[3] = { 1, 1, 1 };

int mdiryR[3] = {-1,0, 1};
int mdirxR[3] = { 0,1, 0};

void bfs(int y, int x, int t) {
	int visited[21][21] = { 0 };

	queue<Node> q;
	// 오른쪽 방향 온풍기인 경우
	q.push({ y,x+1,t });
	visited[y][x+1] = 5;

	for (int a = 0; a < 3; a++) {
		Node now = q.front();
		q.pop();
		if (visited[now.y][now.x] == 1) break;	// 1도 올라간 칸부터는 더 퍼지지 않는다.
		int ny = now.y + diryR[3];
		int nx = now.x + dirxR[3];
		if (ny < 0 || nx < 0 || ny >= R || nx >= C) continue;
		if (MAP[ny][nx] > 0 && MAP[ny][nx] < 5) continue;	// 온풍기 있는 칸이면 continue

		// 벽이 있으면 continue
		int flag = 0;
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

		if (visited[ny][nx] > 0) continue;

		q.push({ ny,nx,t });
		visited[ny][nx] = visited[now.y][now.x] - 1;
	}
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
			if (MAP[i][j] == 5) {
				check.push_back({ i,j,5 });
			}
			else {
				v.push_back({ i,j,MAP[i][j] });
			}
		}
	}

	cin >> W;
	for (int i = 0; i < W; i++) {
		int x, y, t;
		cin >> x >> y >> t;
		wall[x][y][t] = 1;
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

		int dirdy[2] = { 0,1 };
		int dirdx[2] = { 1,0 };

		int temp2[21][21];
		// 온도 조절
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				temp2[i][j] = temp[i][j];
			}
		}
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				for (int d = 0; d < 2; d++) {
					int ny = i + dirdy[d];
					int nx = j + dirdx[d];
					if (ny >= R || nx >= C) continue;
					
					// 벽이 있으면 continue
					if (d == 0 && wall[i][j][1] == 1) continue;
					if (d == 1 && wall[i + 1][j][0] == 1) continue;
					
					int dif = abs(temp2[i][j] - temp2[ny][nx]);
					if (temp2[i][j] > temp2[ny][nx]) {
						temp[i][j] -= dif / 4;
						temp[ny][nx] += dif / 4;
					}
					else {
						temp[i][j] += dif / 4;
						temp[ny][nx] -= dif / 4;
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
			return;
		}
	}

	cout << chocolate;

	return 0;
}
