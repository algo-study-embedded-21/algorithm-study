#include <iostream>
#include <vector>
using namespace std;

int MAP[4][4];

struct Node {
	int num;
	int dir;
	int y;
	int x;
};

vector<Node> v;

Node index[16];
Node shark;

int diry[8] = { 1,1,0,1,1,1,0,1 };
int dirx[8] = { 0,-1,-1,-1,0,1,1,1 };

int ans = 0;
int cnt = 0;

void dfs() {
	// 물고기 정보 벡터 복사
	vector<Node> v2 = v;
	// 맵 복사
	int MAP2[4][4] = { 0 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			MAP2[i][j] = MAP[i][j];
		}
	}
	// 물고기 작은 번호부터 이동
	for (int i = 0; i < 16; i++) {
		Node now = v[i];
		for (int k = 0; k < 8; k++) {
			now.dir += k;
			now.dir %= 8;
			int ny = now.y + diry[now.dir];
			int nx = now.x + dirx[now.dir];
			if (ny < 0 || nx < 0 || ny >= 4 || nx >= 4) continue;
			if (MAP[ny][nx] == -1) continue;	// 상어가 있는 칸이면 continue

			// 이동할 칸 물고기와 바꾸기
			// 물고기 정보 바꾸기
			v[i] = v[MAP[ny][nx]];
			v[MAP[ny][nx]] = now;
			v[i].y = ny;
			v[i].x = nx;
			v[MAP[ny][nx]].y = now.y;
			v[MAP[ny][nx]].x = now.x;

			// 맵 정보 바꾸기
			int temp = MAP[ny][nx];
			MAP[ny][nx] = now.num;
			v[i] = { now.num, now.dir, ny,nx };
			MAP[now.y][now.x] = temp;
			break;
		}
	}

	// 상어 이동
	for (int i = 0; i < 3; i++) {
		int ny = shark.y + i * diry[shark.dir];
		int nx = shark.x + i * dirx[shark.dir];
		if (ny < 0 || nx < 0 || ny >= 4 || nx >= 4) continue;

		// 물고기 먹고 위치로 이동
		int num = MAP[ny][nx];
		if(num > 0)	cnt += num;

		shark = { -1, v[MAP[ny][nx]].dir,ny,nx };
		v[MAP[ny][nx]] = { -2,0,ny,nx };
		MAP[shark.y][shark.x] = -2;
		MAP[ny][nx] = -1;

		dfs();

		// 기존 상태로 복구
		cnt -= num;
		v = v2;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				MAP[i][j] = MAP2[i][j];
			}
		}
	}


	ans = max(ans, cnt);
	return;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int n, d;
			cin >> n >> d;
			v.push_back({ n,d,i,j });
			MAP[i][j] = n;
		}
	}

	// 상어 (0,0) 먹기
	shark = { -1,v[MAP[0][0]].dir,0,0 };
	cnt += MAP[0][0];
	v[MAP[0][0]] = { -2,-1,0,0 };
	MAP[0][0] = -1;

	dfs();

	cout << ans;

	return 0;
}
