#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>
using namespace std;

int R, C, M;

struct shark {
	int r;
	int c;
	int s;
	int d;
	int z;
};

bool cmp(shark a, shark b) {
	if (a.r < b.r) return true;
	if (a.r > b.r) return false;
	if (a.z > b.z) return true;
	if (a.z < b.z) return false;
	return false;
}

vector<shark> v;
queue<shark> q;
queue<shark> mq;

int MAP[101][101] ={0}; // 상어의 크기 저장
int MAP2[101][101]={0};

int diry[4] = { -1,0,1,0 };
int dirx[4] = { 0,1,0,-1 };




int main() {
	// 입력
	
	cin >> R >> C >> M;
	int r, c, s, d, z;
	for (int i = 0; i < M; i++) {
		cin >> r >> c >> s >> d >> z;
		MAP[r][c] = z;

		// 방향배열에 맞추어 바꿔서 입력
		if (d == 1) d = 0;
		else if (d == 2) d = 2;
		else if (d == 3) d = 1;
		else if (d == 4) d = 3;

		q.push({ r,c,s,d,z });
	}
	

	int ans = 0;

	for (int i = 1; i <= C; i++) {
		// 1초 동안 일어나는 일
		
		// 낚시왕 있는 열의 상어 중 가장 가까운 상어 잡는다
		int fish=0;
		for (int j = 1; j <= R; j++) {
			if (MAP[j][i] > 0) {
				fish = MAP[j][i];
				ans += MAP[j][i];
				MAP[j][i] = -1;
				break;
			}
		}
		// 상어 이동
		int qsize = q.size();
		for (int j = 0; j < qsize;j++) {
			shark now = q.front();
			q.pop();
			if (now.z == fish) continue;	// 잡힌 상어면 패스
			if (MAP[now.r][now.c] != now.z) continue;  // 같은 칸에 더 큰 상어가 있으면 패스
			MAP[now.r][now.c] = -1;	// 현재 칸 비운다
			int moves = now.s;
			while (moves > 0) {
				int ny = now.r + diry[now.d];
				int nx = now.c + dirx[now.d];

				// 벽에 부딪히면 반대 방향으로 전환
				if (ny <= 0 || nx <= 0 || ny > R || nx > C) {
					now.d += 2;
					now.d %= 4;
					continue;
				}
				now.r = ny;
				now.c = nx;
				moves--;
			}
			// 현재 칸에 더 큰 상어가 있다면 패스
			if (MAP2[now.r][now.c] > now.z) continue;
			MAP2[now.r][now.c] = now.z;
			q.push({ now.r,now.c, now.s, now.d,now.z });
			mq.push({ now.r,now.c, now.s, now.d,now.z });
		}
		while (!mq.empty()) {
			shark now = mq.front();
			mq.pop();
			MAP[now.r][now.c] = now.z;
			MAP2[now.r][now.c] = 0;
		}
	}

	cout << ans;
	return 0;
}
