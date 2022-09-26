/*

1 : 30

1. 4^5가지 경우의 수 -> 걍 dfs로 다 돌려도 ㄱㅊ
2. 블럭끼리 합치는 부분 / 한 쪽으로 옮기는 부분으로 나눠서 구현
2-1. 블럭 합치기
	- 합칠 수 있는 수(0이 아닌 경우) 수와 인덱스를 기록
	- 합칠 수 있는 경우가 아니면 새로운 값으로 갱신

*/
#include <iostream>
using namespace std;

int original[21][21];
int map[21][21];
int n;

// 상, 하, 좌, 우
int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };
int nums[5];
int answer = 0;

// 같은 수끼리 합치기
void merge(int dir) {
	int x = 0;
	int y = 0;
	int idx = 0;
	// 상, 하로 움직이는 경우
	if (dir == 0 || dir == 1) {
		// 모든 열에 대해 
		for (int i = 0; i < n; i++) {
			// 상인 경우 맨 위부터, 하인 경우 맨 아래부터 확인
			x = dir == 1 ? n - 1 : 0;
			idx = dir == 1 ? n - 1 : 0;
			
			// 첫번째 칸의 값 저장
			int pre = map[idx][i];
			// 나머지 행에 대해 확인
			for (int j = 1; j < n; j++) {
				x += dx[dir];
				// 이전 값이 0일 경우 : 합쳐질 일 없음 -> 새로운 값으로 갱신
				if (pre == 0) {
					pre = map[x][i];
					idx = x;
				}
				else {
					// 이전에 확인한 칸과 현재 칸의 값이 같을 경우
					// 합친 후 pre에 0 저장 (한 번 합친 칸은 또 합칠 수 없기 때문)
					if (pre == map[x][i]) {
						map[idx][i] *= 2;
						map[x][i] = 0;
						pre = 0;
					}
					// 다를 경우 현재 값이 0이면 pass
					// 0이 아니면 새로운 값으로 갱신
					else {
						if (map[x][i] == 0) continue;
						pre = map[x][i];
						idx = x;
					}
				}
			}
		}
	}
	// 좌, 우로 움직이는 경우
	else if (dir == 2 || dir == 3) {
		// 모든 행에 대해 확인
		for (int i = 0; i < n; i++) {
			y = dir == 3 ? n - 1 : 0;
			idx = dir == 3 ? n - 1 : 0;

			int pre = map[i][idx];
			for (int j = 1; j < n; j++) {
				y += dy[dir];
				if (pre == 0) {
					pre = map[i][y];
					idx = y;
				}
				else {
					if (pre == map[i][y]) {
						map[i][idx] *= 2;
						map[i][y] = 0;
						pre = 0;
					}
					else {
						if (map[i][y] == 0) continue;
						pre = map[i][y];
						idx = y;
					}
				}
			}
		}
	}
}

// 한 쪽 방향으로 몰기
void sort(int dir) {
	int x = 0;
	// 상, 하로 움직인 경우
	if (dir == 0 || dir == 1) {
		// 모든 열에 대해 실행
		for (int i = 0; i < n; i++) {
			x = dir == 1 ? n - 1 : 0;
			int line[21] = { 0 };
			int idx = 0;
			// n개의 칸 확인
			for (int j = 0; j < n; j++) {
				if (map[x][i] != 0) line[idx++] = map[x][i];
				map[x][i] = 0;
				x += dx[dir];
			}
			x = dir == 1 ? n - 1 : 0;
			// 0이 아닌 숫자칸의 개수만큼
			for (int j = 0; j < idx; j++) {
				map[x][i] = line[j];
				x += dx[dir];
			}
		}
	}
	// 좌, 우로 움직인 경우
	else if (dir == 2 || dir == 3) {
		// 모든 행에 대해 실행
		for (int i = 0; i < n; i++) {
			x = dir == 3 ? n - 1 : 0;
			int line[21] = { 0 };
			int idx = 0;
			for (int j = 0; j < n; j++) {
				if (map[i][x] != 0) line[idx++] = map[i][x];
				map[i][x] = 0;
				x += dy[dir];
			}
			x = dir == 3 ? n - 1 : 0;
			for (int j = 0; j < idx; j++) {
				map[i][x] = line[j];
				x += dy[dir];
			}
		}
	}
}

void calc() {
	// 매 번 초기화해주기!!!!
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			map[i][j] = original[i][j];
		}
	}

	for (int i = 0; i < 5; i++) {
		merge(nums[i]);
		sort(nums[i]);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			answer = max(answer, map[i][j]);
		}
	}
}

// 최대 5번움직일 조합 찾기
void dfs(int depth) {
	if (depth == 5) {
		calc();
		return;
	}

	for (int i = 0; i < 4; i++) {
		nums[depth] = i;
		dfs(depth + 1);
		nums[depth] = 0;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> original[i][j];
		}
	}

	dfs(0);
	cout << answer;

	return 0;
}