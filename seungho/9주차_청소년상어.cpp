#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int MAP[4][4];

struct Node {
	int num;
	int dir;
	int y;
	int x;
};

bool cmp(Node a, Node b) {
	if (a.num < b.num) return true;
	else if (a.num > b.num) return false;
	return false;
}

vector<Node> v;
vector<int> dead;
Node index[16];
Node shark;

int diry[8] = { -1,-1,0,1,1,1,0,-1 };
int dirx[8] = { 0,-1,-1,-1,0,1,1,1 };

int ans = 0;
int cnt = 0;

void dfs() {

	// 물고기 작은 번호부터 이동
	for (int i = 1; i <= 16; i++) {
		if (v[i].num <= 0) continue;

		Node now = v[i];
		// 방향 45도씩 돌려가며 이동할 수 있으면 이동
		for (int k = 0; k <= 8; k++) {
			int ndir = (now.dir + k) % 8;
			int ny = now.y + diry[ndir];
			int nx = now.x + dirx[ndir];
			if (ny < 0 || nx < 0 || ny >= 4 || nx >= 4) continue;
			if (MAP[ny][nx] == -1) continue;	// 상어가 있는 칸이면 continue

			// 바뀐 방향 저장
			v[i].dir = ndir;

			// 이동할 칸 물고기와 바꾸기
			// 물고기 위치 바꾸기

			v[i].y = ny;
			v[i].x = nx;
			v[MAP[ny][nx]].y = now.y;
			v[MAP[ny][nx]].x = now.x;

			// 맵 정보 바꾸기
			int temp = MAP[ny][nx];
			MAP[ny][nx] = now.num;
			MAP[now.y][now.x] = temp;
			break;
		}
	}

	// 물고기 정보 벡터 복사
	vector<Node> v2;
	for (int i = 0; i < 17; i++) {
		v2.push_back(v[i]);
	}
	// 맵 복사
	int MAP2[4][4] = { 0 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			MAP2[i][j] = MAP[i][j];
		}
	}
	int asdf = 1;
	// 상어 이동
	for (int i = 1; i < 4; i++) {
		int ny = v[0].y + i * diry[v[0].dir];
		int nx = v[0].x + i * dirx[v[0].dir];
		if (ny < 0 || nx < 0 || ny >= 4 || nx >= 4) continue;
		if (v[MAP[ny][nx]].num < 0) continue;

		// 물고기 먹고 위치로 이동
		int num = MAP[ny][nx];
		cnt += num;
		dead.push_back(num);

		MAP[v[0].y][v[0].x] = num;
		MAP[ny][nx] = -1;
		v[num] = { -2,v[num].dir,v[0].y,v[0].x };
		v[0] = { -1, v[num].dir,ny,nx };

		dfs();

		// 기존 상태로 복구
		cnt -= num;
		dead.pop_back();
		for (int k = 0; k < 17; k++) {
			v[k] = v2[k];
		}
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				MAP[y][x] = MAP2[y][x];
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

	v.push_back({ -1,0,0,0 });

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int n, d;
			cin >> n >> d;
			v.push_back({ n,d - 1,i,j });
			MAP[i][j] = n;
		}
	}

	sort(v.begin() + 1, v.end(), cmp);

	// 상어 (0,0) 먹기
	v[0].dir = v[MAP[0][0]].dir;
	cnt += MAP[0][0];
	dead.push_back(MAP[0][0]);
	v[MAP[0][0]] = { 0,v[0].dir,0,0 };
	MAP[0][0] = -1;

	dfs();

	cout << ans;

	return 0;
}
