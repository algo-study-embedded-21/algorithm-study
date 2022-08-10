/*

1. cctv의 대수 구하기
2. 각 cctv의 방향 (0~3으로 설정) 조합 구하기
3. 조합 별 사각지대 구한 뒤, 최솟값 갱신

*/

#include <iostream>
#include <vector>
using namespace std;

struct Node {
	int x;
	int y;
	int id;
};

int n, m;
int arr[8][8];
vector<Node> cctv;
vector<int> direction;

// cctv가 바라볼 수 있는 방향의 좌표
int dArr[4][2] = {
	// up
	{-1, 0},
	// down
	{1, 0},
	// left
	{0, -1},
	// right
	{0, 1}
};

int minsize = 2134567890;

void getArea() {
	// 모든 cctv에 대해 감시 구역 확인
	int len = cctv.size();

	// map  복사
	int map[8][8] = { 0 };
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			map[i][j] = arr[i][j];
		}
	}

	// 정해진 조합의 방향으로 cctv 감시
	for (int i = 0; i < len; i++) {
		Node now = cctv[i];

		switch (now.id)
		{
		case 1: {
			// 1번 카메라는 한 방향만 
			int x = now.x;
			int y = now.y;

			// 정해진 방향으로 벽이 나타날 때까지 확인
			while (x < n && y < m && x >= 0 && y >= 0) {
				if (map[x][y] == 6) break;

				map[x][y] = -1;
				x += dArr[direction[i]][0];
				y += dArr[direction[i]][1];
			}

			break;
		}
		case 2: {
			// 상하 혹은 좌우만 살필 수 있도록 확인할 방향 지정
			int selectD[4][2] = {
				{0, 1},
				{0, 1},
				{2, 3},
				{2, 3}
			};

			for (int j : selectD[direction[i]]) {
				int x = now.x;
				int y = now.y;

				while (x < n && y < m && x >= 0 && y >= 0) {
					if (map[x][y] == 6) break;

					map[x][y] = -1;
					x += dArr[j][0];
					y += dArr[j][1];
				}
			}

			break;
		}
		case 3: {
			// 상좌, 상우, 하좌, 하우 방향 지정
			int selectD[4][2] = {
				{0, 2},
				{0, 3},
				{1, 2},
				{1, 3}
			};

			for (int j : selectD[direction[i]]) {
				int x = now.x;
				int y = now.y;

				while (x < n && y < m && x >= 0 && y >= 0) {
					if (map[x][y] == 6) break;

					map[x][y] = -1;
					x += dArr[j][0];
					y += dArr[j][1];
				}
			}

			break;
		}
		case 4: {
			// 한 방향 빼고 다 확인
			for (int j = 0; j < 4; j++) {
				if (j == direction[i]) continue;
				int x = now.x;
				int y = now.y;

				while (x < n && y < m && x >= 0 && y >= 0) {
					if (map[x][y] == 6) break;

					map[x][y] = -1;
					x += dArr[j][0];
					y += dArr[j][1];
				}
			}

			break;
		}
		case 5: {
			// 그냥 다 확인
			for (int j = 0; j < 4; j++) {
				int x = now.x;
				int y = now.y;

				while (x < n && y < m && x >= 0 && y >= 0) {
					if (map[x][y] == 6) break;

					map[x][y] = -1;
					x += dArr[j][0];
					y += dArr[j][1];
				}
			}
			break;

		}
		}
	}

	// 현재 조합의 사각지대 구하기
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 0) cnt++;
		}
	}

	// 더 적은 사각지대가 나오면 갱신
	minsize = min(cnt, minsize);
}

void dfs(int depth) {
	// cctv 대수 별 방향 정한 뒤
	if (depth == cctv.size()) {
		// 조합별 사각지대 구하기
		getArea();
		return;
	}

	// 2번 5번 cctv의 경우 중복을 좀 더 제거할 수 있지만
	// n의 크기가 8로 작으므로 그냥 다 계산
	for (int j = 0; j < 4; j++) {
		direction.push_back(j);
		dfs(depth + 1);
		direction.pop_back();
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
			// cctv의 위치, 종류 저장
			if (arr[i][j] == 1 || arr[i][j] == 2 || arr[i][j] == 3 || arr[i][j] == 4 || arr[i][j] == 5)
				cctv.push_back({ i, j, arr[i][j] });
		}
	}

	// cctv의 방향 조합 구하기
	// 순서 구분, 중복 가능
	dfs(0);

	cout << minsize;

	return 0;
}