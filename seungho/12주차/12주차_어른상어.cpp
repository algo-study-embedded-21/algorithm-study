#include <iostream>
#include <vector>
using namespace std;

int N, M, k;

int MAP[20][20];

struct Node {
	int n; int t;
};

// 냄새
Node scent[20][20];

// 상어 방향
int shark[400];

//상어 방향 우선순위
int direction[400][4][4];

int diry[4] = { -1,1,0,0 };
int dirx[4] = { 0,0,-1,1 };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> N >> M >> k;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin>>MAP[i][j];
		}
	}

	for (int i = 0; i < M; i++) {
		cin >> shark[i];
	}

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				int d;
				cin >> d;
				direction[i][j][k] = d-1;
			}
		}
	}

	int time = 0;
	while (true) {

		if (time > 1000) {
			cout << -1;
			return 0;
		}
		int MAP2[20][20] = { 0 };
		// 자신의 위치에 냄새 뿌린다.
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (MAP[i][j]) {
					MAP2[i][j] = MAP[i][j];
					scent[i][j] = { MAP[i][j],k };
					MAP[i][j] = 0;
				}
			}
		}

		// 인접한 칸으로 상어 이동
		// 우선순위에 따라 방향 결정
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				int num = MAP2[i][j];
				int dir = shark[MAP2[i][j]];
				int flag = 0;
				if (num > 0) {
					// 아무 냄새 없는 칸으로 이동
					for (int d = 0; d < 4; d++) {
						int dnow = direction[num][dir][d];
						int ny = i + diry[dnow];
						int nx = j + dirx[dnow];
						if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
						if (scent[ny][nx].t > 0) continue;
						MAP[ny][nx] = num;
						shark[num] = dnow;
						flag = 1;
						break;
					}
					if (flag == 1) break;
					// 자신의 냄새 있는 칸으로 이동
					for (int d = 0; d < 4; d++) {
						int dnow = direction[num][dir][d];
						int ny = i + diry[dnow];
						int nx = j + dirx[dnow];
						if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
						if (scent[ny][nx].n == num) {
							MAP[ny][nx] = num;
							shark[num] = dnow;
							flag = 1;
							break;
						}
					}
				}
			}
		}
		
		// 이동할 칸에 이미 상어가 있는 경우 가장 작은 번호 가진 상어만 남는다.
		// 결정된 방향으로 이동
		
		// 이동한 칸에 냄새 뿌린다.

		// 모든 칸 냄새 남은 시간 -1
		time++;
	}

	cout << time;
	return 0;
}
