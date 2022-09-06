#include <iostream>
#include <vector>
using namespace std;

int R, C, T;
int MAP[1001][1001]={0};
int MAP2[1001][1001] = { 0 };

struct Node {
	int y;
	int x;
	int d;
};

vector<Node> v;
vector<Node> filter;

int diry[4] = { 0,0,1,-1 };
int dirx[4] = { 1,-1,0,0 };

int windy[4] = { -1,0,1,0 };
int windx[4] = { 0,1,0,-1 };

void dust() {
	// 미세먼지 칸마다 확산
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (MAP[i][j] == 0 || MAP[i][j] == -1) continue;
			int scatter = MAP[i][j] / 5;
			for (int a = 0; a < 4; a++) {
				int ny = i + diry[a];
				int nx = j + dirx[a];
				if (ny<1 || nx<1 || ny>R || nx>C) continue;
				if (MAP[ny][nx] == -1) continue;
				MAP2[ny][nx] += scatter;
				MAP[i][j] -= scatter;
			}
		}
	}
	// 확산 이후 결과 계산
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			/*if (MAP2[i][j] == 0) continue;*/
			MAP[i][j] += MAP2[i][j];
			MAP2[i][j] = 0;

		}

	}

	// 반시계 방향 바람
	int sy1 = filter[0].y-1;
	int sx1 = filter[0].x;
	int y1 = sy1;
	int x1 = sx1;
	int w1 = 0;
	while (true) {
		int ny = y1 + windy[w1];
		int nx = x1 + windx[w1];
		if (ny<1 || nx<1 || ny > (sy1+1) || nx>C) {
			w1++;	

			continue;
		}
		if (MAP[ny][nx] == -1) break;

		MAP[y1][x1] = MAP[ny][nx];
		y1 = ny;
		x1 = nx;
	}
	MAP[y1][x1] = 0; // 시작부분

	// 시계 방향 바람
	int sy2 = filter[1].y+1;
	int sx2 = filter[1].x;
	int y2 = sy2;
	int x2 = sx2;
	int w2 = 2;
	while (true) {
		int ny = y2 + windy[w2];
		int nx = x2 + windx[w2];
		if (ny<(sy2-1) || nx<1 || ny>R || nx>C) {
			w2--;
			if (w2 < 0) w2 += 4;
			continue;
		}
		if (MAP[ny][nx] == -1) break;
		MAP[y2][x2] = MAP[ny][nx];
		y2 = ny;
		x2 = nx;
	}
	MAP[y2][x2] = 0;  // 시작부분
}


int main() {
	// 입력
	cin >> R >> C >> T;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == -1) filter.push_back({ i,j,-1 });
		}
	}

	// T초 반복
	for (int i = 0; i < T; i++) {
		dust();
	}
	int ans = 0;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {

			if (MAP[i][j] == -1 || MAP[i][j]==0) continue;
			ans += MAP[i][j];
		}

	}
	cout << ans;
	return 0;
}
