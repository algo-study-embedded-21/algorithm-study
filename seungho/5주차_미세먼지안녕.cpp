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
				MAP[v[i].y][v[i].x] -= scatter;
			}
		}
	}
	// 확산 이후 결과 계산
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (MAP2[i][j] == 0) continue;
			MAP[i][j] += MAP2[i][j];
			MAP2[i][j] = 0;
		}
	}

	// 반시계 방향 바람
	int s1y = filter[0].y;
	int s1x = filter[0].x;
	int w1 = 0;
	while (true) {
		int ny = s1y + windy[w1];
		int nx = s1x + windx[w1];
		if (ny<1 || nx<1 || ny>R || nx>C) {
			w1++;
			continue;
		}
		if (MAP[ny][nx] == -1) break;
		MAP[s1y][s1x] = MAP[ny][nx];
		s1y = ny;
		s1x = nx;
	}
	// 시계 방향 바람
	int s2y = filter[1].y;
	int s2x = filter[1].x;
	int w2 = 2;
	while (true) {
		int ny = s2y + windy[w2];
		int nx = s2x + windx[w2];
		if (ny<1 || nx<1 || ny>R || nx>C) {
			w2--;
			if (w2 < 0) w2 += 4;
			continue;
		}
		if (MAP[ny][nx] == -1) break;
		MAP[s2y][s2x] = MAP[ny][nx];
		s2y = ny;
		s2x = nx;
	}
}


int main() {
	// 입력
	cin >> R >> C >> T;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] > 0) v.push_back({ i,j,MAP[i][j] });
			else if (MAP[i][j] == -1) filter.push_back({ i,j,-1 });
		}
	}

	// T초 반복
	for (int i = 0; i < T; i++) {
		dust();
	}
	int ans = 0;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (MAP[i][j] == -1) continue;
			ans += MAP[i][j];
		}
	}
	cout << ans;
	return 0;
}
