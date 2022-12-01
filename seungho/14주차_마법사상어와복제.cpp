#include <iostream>
#include <vector>
#include <string.h>
using namespace std;


int M, S;
int smell[5][5];
int sy, sx;

vector<int> MAP[5][5];	// 이동 방향을 담는 벡터맵

int diry[8] = { 0,-1,-1,-1,0,1,1,1 };
int dirx[8] = { -1,-1,0,1,1,1,0,-1 };

int orderindex[8] = { 2,0,1,0,4,0,3,0 };

int maxcnt = -1;
int minorder = 2134567890;

struct Node {
	int y; int x;
};

vector<Node> v;	// 최종 상어 루트
vector<Node> temp;
int visited[5][5];

void dfs(int level, int cnt, int order) {
	if (level == 0) {
		if (cnt > maxcnt) {
			maxcnt = cnt;
			minorder = order;
			v.clear();
			v = temp;
		}
		else if (cnt == maxcnt) {
			if (order < minorder) {
				minorder = order;
				v.clear();
				v = temp;
			}
		}
		return;
	}

	for (int d = 0; d < 4; d++) {
		int dir = 2 * d;
		int ny = sy + diry[dir];
		int nx = sx + dirx[dir];
		if (ny <= 0 || nx <= 0 || ny > 4 || nx > 4) continue;
		sy = ny;
		sx = nx;
		temp.push_back({ ny,nx });
		int flag = 0;
		if (visited[ny][nx] == 0) {
			flag = 1;
			cnt += MAP[ny][nx].size();
		}
		visited[ny][nx]++;
		dfs(level / 10, cnt, order + level * orderindex[dir]);
		temp.pop_back();
		visited[ny][nx]--;
		if (flag == 1) cnt -= MAP[ny][nx].size();
		sy -= diry[dir];
		sx -= dirx[dir];
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> M >> S;

	for (int i = 0; i < M; i++) {
		int fy, fx, d;
		cin >> fy >> fx >> d;
		MAP[fy][fx].push_back(d - 1);
	}

	cin >> sy >> sx;

	for (int s = 0; s < S; s++) {
		// 0. 처음 위치와 방향의 물고기 복제
		vector<int> COPY[5][5];
		for (int i = 1; i < 5; i++) {
			for (int j = 1; j < 5; j++) {
				COPY[i][j] = MAP[i][j];
				MAP[i][j].clear();
			}
		}

		// 1. 모든 물고기 1칸 이동
		for (int i = 1; i < 5; i++) {
			for (int j = 1; j < 5; j++) {
				for (int k = 0; k < COPY[i][j].size(); k++) {
					// 이동할 방향 찾기
					int dir = COPY[i][j][k];
					// 1-1. 이동할 수 있는 칸 향할 때까지 방향 반시계 회전
					int moveflag = 0;
					for (int d = 8; d > 0; d--) {
						int nd = dir + d;
						nd %= 8;
						int ny = i + diry[nd];
						int nx = j + dirx[nd];
						if (ny <= 0 || nx <= 0 || ny > 4 || nx > 4) continue;
						if (ny == sy && nx == sx) continue;
						if (smell[ny][nx] > 0) continue;
						// 1-2. 이동
						MAP[ny][nx].push_back(nd);
						moveflag = 1;
						break;
					}
					if (moveflag == 0) MAP[i][j].push_back(dir);
				}
			}
		}

		// 2. 상어 3칸 연속 이동(제외되는 물고기 가장 많은 방법으로 이동)
		// 2-1. 이동 중 물고기 있으면 모두 제외
		// 2-2. 제외되는 물고기는 냄새를 남긴다.
		v.clear();
		temp.clear();
		memset(visited, 0, sizeof(visited));
		maxcnt = -1;
		minorder = 2134567890;

		dfs(100, 0, 0);

		sy = v[v.size() - 1].y;
		sx = v[v.size() - 1].x;

		// 3. 두 번 전 연습에서 생긴 냄새 제거
		for (int i = 1; i < 5; i++) {
			for (int j = 1; j < 5; j++) {
				if (smell[i][j] > 0) smell[i][j]--;
			}
		}

		for (int i = 0; i < v.size(); i++) {
			Node now = v[i];
			if (MAP[now.y][now.x].size() > 0) {
				smell[now.y][now.x] = 2;
				MAP[now.y][now.x].clear();
			}
		}

		// 4. 0에서 복제해둔 물고기 생성
		for (int i = 1; i < 5; i++) {
			for (int j = 1; j < 5; j++) {
				for (int k = 0; k < COPY[i][j].size(); k++) {
					MAP[i][j].push_back(COPY[i][j][k]);
				}
				COPY[i][j].clear();
			}
		}
	}

	int ans = 0;
	for (int i = 1; i < 5; i++) {
		for (int j = 1; j < 5; j++) {
			ans += MAP[i][j].size();
		}
	}

	cout << ans;

	return 0;
}
