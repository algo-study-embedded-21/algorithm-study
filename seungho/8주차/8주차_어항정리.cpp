#include <iostream>
#include <string.h>
using namespace std;

int N, K;
int MAP[100][100];
int MAP2[100][100];

// 가장 적은 어항 찾고, 한마리 넣기
void add() {
	int mincnt = 2134567890;
	for (int i = 0; i < N; i++) {
		mincnt = min(mincnt, MAP[0][i]);
	}
	for (int i = 0; i < 100; i++) {
		if (MAP[0][i] == mincnt) {
			MAP[0][i]++;
		}
	}
}

// 말기
void roll() {
	// 처음 맨 앞 한 칸 올리기
	MAP[1][1] = MAP[0][0];
	MAP[0][0] = 0;

	while (1) {
		// 몇번째 칸(n) 전까지 2층 이상 쌓여있는지 찾기
		int n = 1;
		int flag = 0;
		for (int j = 1; j < N; j++) {
			if (MAP[0][j] == 0) continue;
			if (MAP[1][j] == 0) {
				n = j;
				flag = 1;
				break;
			}
		}
		if (flag == 0) break;
		// 몇층까지 쌓여있는지 찾기
		int m = 0;
		for (int i = 0; i < N; i++) {
			if (MAP[i][n - 1] == 0) {
				m = i;
				break;
			}
		}
		if (n + m > N) break;

		// n-1번째 열부터 왼쪽으로 가며 회전시켜 n번 열 위에 쌓기
		for (int j = n - 1; j >= 0; j--) {
			if (MAP[0][j] == 0) break;	// 더 이상 왼쪽에 어항이 없으면 break
			for (int i = 0; i < N; i++) {
				if (MAP[i][j] == 0) break;	// 더 이상 위에 어항이 없으면 break

				MAP[n - j][n + i] = MAP[i][j];
				MAP[i][j] = 0;
			}
		}

	}
}

int diry[2] = { 0,1 };
int dirx[2] = { 1,0 };

// 물고기 수 조절
void popctrl() {
	// MAP 복사하기
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			MAP2[i][j] = MAP[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (MAP2[i][j] == 0) continue; // 현재 칸에 어항이 없으면 continue
			for (int k = 0; k < 2; k++) {
				int ny = i + diry[k];
				int nx = j + dirx[k];
				if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
				if (MAP2[ny][nx] == 0) continue;	// 옆 칸에 어항이 없으면 continue
				// d = 인접한 두 칸의 차이를 5로 나눈 몫
				int d = abs(MAP2[i][j] - MAP2[ny][nx]) / 5;
				if (d <= 0) continue;
				// 두 칸 중 더 큰 쪽에서 작은 쪽으로 한 마리 이동
				if (MAP2[i][j] > MAP2[ny][nx]) {
					MAP[i][j] -= d;
					MAP[ny][nx] += d;
				}
				else {
					MAP[i][j] += d;
					MAP[ny][nx] -= d;
				}
			}
		}
	}
}

// 바닥에 깔기
void spread() {
	// MAP 복사
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			MAP2[i][j] = MAP[i][j];
		}
	}
	// MAP 
	memset(MAP, 0, sizeof(MAP));
	// 왼쪽 열부터 바닥에 일렬로 놓기
	int f = 0;
	for (int j = 0; j < N; j++) {
		if (MAP2[0][j] == 0) continue;	// 바닥에 어항이 없는 열이면 continue
		for (int i = 0; i < 100; i++) {
			if (MAP2[i][j] == 0) break;
			MAP[0][f] = MAP2[i][j];
			f++;
		}
	}
}

// 반으로 두 번 접기
void fold() {
	for (int j = 0; j < N / 2; j++) {
		MAP[1][N - 1 - j] = MAP[0][j];
		MAP[0][j] = 0;
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < N / 4; j++) {
			MAP[3 - i][N - 1 - j] = MAP[i][j + N / 2];
			MAP[i][j + N / 2] = 0;
		}
	}
}

// 최대, 최소 찾기
int Kcheck() {
	int maxcnt = -1;
	int mincnt = 2134567890;
	for (int j = 0; j < N; j++) {
		maxcnt = max(maxcnt, MAP[0][j]);
		mincnt = min(mincnt, MAP[0][j]);
	}

	if (maxcnt - mincnt <= K) return 1;
	else return 0;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> N >> K;

	for (int i = 0; i < N; i++) {
		cin >> MAP[0][i];
	}

	int cnt = 0;
	while (1) {
		// 물고기 최대 수와 최소 수 차이가 K 이하면 break
		if (Kcheck() == 1) break;

		// 1. 가장 적은 어항에 한 마리 넣기
		add();

		// 2. 말기
		roll();

		// 3. 물고기 수 조절
		popctrl();

		// 4. 다시 바닥에 깔기
		spread();

		// 5. 반으로 접기
		fold();

		// 6. 다시 물고기 수 조절
		popctrl();

		// 7. 바닥에 깔기
		spread();

		cnt++;
	}

	cout << cnt;

	return 0;
}
