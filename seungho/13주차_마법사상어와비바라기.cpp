#include <iostream>
#include <queue>
using namespace std;

int N, M;
int MAP[50][50];

struct Node {
	int d; int s;
};

Node moves[100];

queue<Node> cloud;
queue<Node> rain;

int diry[8] = {0,-1,-1,-1,0,1,1,1};
int dirx[8] = {-1,-1,0,1,1,1,0,-1};

int diry2[4] = { -1,-1,1,1 };
int dirx2[4] = { -1,1,1,-1 };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
		}
	}

	// 0. 비구름 생성
	cloud.push({ N - 1,0 });
	cloud.push({ N - 1,1 });
	cloud.push({ N - 2,0 });
	cloud.push({ N - 2,1 });

	for (int m = 0; m < M; m++) {
		int d, s;
		cin >> d >> s;

		int cloudMAP[50][50]={0};

		// 1. 모든 구름이 di 방향으로 si칸 이동
		// -> cloud에서 rain으로 이동
		while (!cloud.empty()) {
			Node now = cloud.front();
			int ny = now.d + s * diry[d-1];
			int nx = now.s + s * dirx[d-1];
			ny %= N;
			nx %= N;
			rain.push({ ny,nx });

			cloudMAP[ny][nx] = 1; // 이번 턴에 구름이 있었던 곳 체크

			// 2. 각 구름에서 비
			MAP[ny][nx]++;
			// 3. 구름이 모두 사라진다.
			cloud.pop();
		}
		// 4. 2에서 물이 증가한 칸에 물복사버그
		while(!rain.empty()){
			Node now = rain.front();
			rain.pop();
			int cnt = 0;

			// 대각선 방향에 물이 있는 바구니 수 count
			for (int r = 0; r < 4; r++) {
				int ny = now.d + diry2[r];
				int nx = now.s + dirx2[r];
				if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
				if (MAP[ny][nx] == 0) continue;
				cnt++;
			}
			MAP[now.d][now.s] += cnt;
		}

		// 5. 물의 양 2 이상인 모든 칸에 구름
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (cloudMAP[i][j]) continue;
				if (MAP[i][j] >= 2) {
					cloud.push({ i,j });
				}
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			ans += MAP[i][j];
		}
	}

	cout << ans;

	return 0;
}
