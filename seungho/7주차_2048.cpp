#include <iostream>
using namespace std;

struct Block {
	int num;
	int flag;
};

int N;

Block MAP[20][20]; 

// d 방향으로 1회 이동시키는 함수
// 이동하는 방향쪽부터 모든 블록을 벽이나 다른 블록을 만날 때까지 방향으로 붙인다
// 벽을 만나면 위치에 블록 정보 저장 후 continue
// 바로 앞 블록이 같은 숫자일때,
// 1)이미 합쳐진 블록이면 현재 위치에 블록 정보 저장 후 continue
// 2)합쳐진 블록이 아니면 현재 블록과 합치고 정보 저장
void move(int d) {
	// 상
	if (d == 0) {
		for (int j = 0; j < N; j++) {
			for (int i = 1; i < N; i++) {
				// 현재 칸이 비어있다면 continue
				if (MAP[i][j].num == 0) continue;

				Block now = MAP[i][j];
				MAP[i][j] = { 0,0 };
				int ni = i;
				while (ni >= 0) {
					ni--;
					// 벽에 닿은 경우
					// 현재 위치에 정보 저장
					if (ni < 0) {
						MAP[ni + 1][j] = { now.num,0 };
						break;
					}
					// 다음 칸이 비어있는 경우 continue
					if (MAP[ni][j].num == 0) continue;

					// 만난 블록이 현재 블록과 같고 합쳐지지 않은경우
					// 블록을 합쳐주고 정보 저장
					if (MAP[ni][j].num == now.num && MAP[ni][j].flag == 0) {
						MAP[ni][j] = { now.num * 2, 1 };
					}
					// 나머지 경우 현재 위치에 블록 정보 저장
					else {
						MAP[ni + 1][j] = { now.num, 0 };
					}
				}
			}
		}
	}
	// 하
	else if (d == 1) {
		for (int j = 0; j < N; j++) {
			for (int i = N - 2; i >= 0; i--) {
				// 현재 칸이 비어있다면 continue
				if (MAP[i][j].num == 0) continue;

				Block now = MAP[i][j];
				MAP[i][j] = { 0,0 };
				int ni = i;
				while (ni < N) {
					ni++;
					// 벽에 닿은 경우
					// 현재 위치에 정보 저장
					if (ni >= N) {
						MAP[ni - 1][j] = { now.num,0 };
						break;
					}
					// 다음 칸이 비어있는 경우 continue
					if (MAP[ni][j].num == 0) continue;

					// 만난 블록이 현재 블록과 같고 합쳐지지 않은경우
					// 블록을 합쳐주고 정보 저장
					if (MAP[ni][j].num == now.num && MAP[ni][j].flag == 0) {
						MAP[ni][j] = { now.num * 2, 1 };
					}
					// 나머지 경우 현재 위치에 블록 정보 저장
					else {
						MAP[ni - 1][j] = { now.num, 0 };
					}
				}
			}
		}
	}
	// 좌
	else if (d == 3) {
		for (int i = 0; i < N; i++) {
			for (int j = 1; j < N; j++) {
				// 현재 칸이 비어있다면 continue
				if (MAP[i][j].num == 0) continue;

				Block now = MAP[i][j];
				MAP[i][j] = { 0,0 };
				int nj = j;
				while (nj >= 0) {
					nj--;
					// 벽에 닿은 경우
					// 현재 위치에 정보 저장
					if (nj < 0) {
						MAP[i][nj + 1] = { now.num,0 };
						break;
					}
					// 다음 칸이 비어있는 경우 continue
					if (MAP[i][nj].num == 0) continue;

					// 만난 블록이 현재 블록과 같고 합쳐지지 않은경우
					// 블록을 합쳐주고 정보 저장
					if (MAP[i][nj].num == now.num && MAP[i][nj].flag == 0) {
						MAP[i][nj] = { now.num * 2, 1 };
					}
					// 나머지 경우 현재 위치에 블록 정보 저장
					else {
						MAP[i][nj + 1] = { now.num, 0 };
					}
				}
			}
		}
	}
	// 우
	else {
		for (int i = 0; i < N; i++) {
			for (int j = N - 2; j >= 0; j--) {
				// 현재 칸이 비어있다면 continue
				if (MAP[i][j].num == 0) continue;

				Block now = MAP[i][j];
				MAP[i][j] = { 0,0 };
				int nj = j;
				while (nj < N) {
					nj++;
					// 벽에 닿은 경우
					// 현재 위치에 정보 저장
					if (nj >= N) {
						MAP[i][nj - 1] = { now.num,0 };
						break;
					}
					// 다음 칸이 비어있는 경우 continue
					if (MAP[i][nj].num == 0) continue;

					// 만난 블록이 현재 블록과 같고 합쳐지지 않은경우
					// 블록을 합쳐주고 정보 저장
					if (MAP[i][nj].num == now.num && MAP[i][nj].flag == 0) {
						MAP[i][nj] = { now.num * 2, 1 };
					}
					// 나머지 경우 현재 위치에 블록 정보 저장
					else {
						MAP[i][nj - 1] = { now.num, 0 };
					}
				}
			}
		}
	}
}

int maxNum = -1;


// N회 이동 dfs로 블록 최대 값 구하기
void dfs(int level) {
	if (level == 5) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (MAP[i][j].num == 0) continue;
				maxNum = max(maxNum, MAP[i][j].num);
			}
		}
		return;
	}
	Block temp[20][20]={0};
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			temp[i][j] = MAP[i][j];
		}
	}
	for (int i = 0; i < 4; i++) {
		move(i);
		dfs(level + 1);
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				MAP[i][j] = temp[i][j];
			}
		}
	}

}


int main() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int num;
			cin >> num;
			MAP[i][j] = { num,0 };
		}
	}

	dfs(0);

	cout << maxNum;


	return 0;
}
