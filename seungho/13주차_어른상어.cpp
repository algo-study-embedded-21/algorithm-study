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
				cin >> direction[i][j][k];
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
				}
			}
		}

		// 인접한 칸으로 상어 이동
		

		// 우선순위에 따라 방향 결정
		// 이동할 칸에 이미 상어가 있는 경우 가장 작은 번호 가진 상어만 남는다.
		// 결정된 방향으로 이동
		
		// 이동한 칸에 냄새 뿌린다.

		// 모든 칸 냄새 남은 시간 -1
		time++;
	}

	cout << time;
	return 0;
}
