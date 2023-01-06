#include <iostream>
#include <vector>
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
void move(int d, int level) {
	// 상
	if (d == 0) {
		for (int j = 0; j < N; j++) {
			for (int i = 1; i < N; i++) {
				// 현재 칸이 비어있다면 continue
				if (MAP[i][j].num == 0) continue;

				Block now = MAP[i][j];
				MAP[i][j] = { 0,0 };
				int ni = i - 1;
				while (ni >= 0) {
					// 블록을 만난 경우
					if (MAP[ni][j].num > 0) {
						// 같은 숫자이고 합쳐지지 않은 블록인 경우
						if (MAP[ni][j].num == now.num && MAP[ni][j].flag != level) {
							// 블록을 합치고 맵에 정보 저장
							MAP[ni][j] = { now.num * 2, level };
						}
						// 합쳐지지 않고 이전 칸에 정보 저장
						else {
							MAP[ni + 1][j] = { now.num, 0 };
						}
						break;
					}

					// 블록을 만나지 않고 끝까지 이동한 경우
					if (ni == 0) {
						MAP[ni][j] = { now.num,0 };
					}
					ni--;
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
				int ni = i + 1;
				while (ni < N) {
					// 블록을 만난 경우
					if (MAP[ni][j].num > 0) {
						// 같은 숫자이고 합쳐지지 않은 블록인 경우
						if (MAP[ni][j].num == now.num && MAP[ni][j].flag != level) {
							// 블록을 합치고 맵에 정보 저장
							MAP[ni][j] = { now.num * 2, level };
						}
						// 합쳐지지 않고 이전 칸에 정보 저장
						else {
							MAP[ni - 1][j] = { now.num, 0 };
						}
						break;
					}

					// 블록을 만나지 않고 끝까지 이동한 경우
					if (ni == N - 1) {
						MAP[ni][j] = { now.num,0 };
					}
					ni++;
				}
			}
		}
	}
	// 좌
	else if (d == 2) {
		for (int i = 0; i < N; i++) {
			for (int j = 1; j < N; j++) {
				// 현재 칸이 비어있다면 continue
				if (MAP[i][j].num == 0) continue;

				Block now = MAP[i][j];
				MAP[i][j] = { 0,0 };
				int nj = j - 1;
				while (nj >= 0) {
					// 블록을 만난 경우
					if (MAP[i][nj].num > 0) {
						// 같은 숫자이고 합쳐지지 않은 블록인 경우
						if (MAP[i][nj].num == now.num && MAP[i][nj].flag != level) {
							// 블록을 합치고 맵에 정보 저장
							MAP[i][nj] = { now.num * 2, level };
						}
						// 합쳐지지 않고 이전 칸에 정보 저장
						else {
							MAP[i][nj + 1] = { now.num, 0 };
						}
						break;
					}

					// 블록을 만나지 않고 끝까지 이동한 경우
					if (nj == 0) {
						MAP[i][nj] = { now.num,0 };
					}
					nj--;
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
				int nj = j + 1;
				while (nj < N) {
					// 블록을 만난 경우
					if (MAP[i][nj].num > 0) {
						// 같은 숫자이고 합쳐지지 않은 블록인 경우
						if (MAP[i][nj].num == now.num && MAP[i][nj].flag != level) {
							// 블록을 합치고 맵에 정보 저장
							MAP[i][nj] = { now.num * 2, level };
						}
						// 합쳐지지 않고 이전 칸에 정보 저장
						else {
							MAP[i][nj - 1] = { now.num, 0 };
						}
						break;
					}

					// 블록을 만나지 않고 끝까지 이동한 경우
					if (nj == N - 1) {
						MAP[i][nj] = { now.num,0 };
					}
					nj++;
				}
			}
		}
	}
}

int maxNum = -1;

vector<int> path;

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
	Block temp[20][20] = { 0 };
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			temp[i][j] = MAP[i][j];
		}
	}
	for (int i = 0; i < 4; i++) {
		move(i, level + 1);
		path.push_back(i);
		dfs(level + 1);
		path.pop_back();
		// 이전 맵으로 복구
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
