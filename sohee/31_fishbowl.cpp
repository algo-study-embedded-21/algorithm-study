#include <iostream>
#include <vector>
using namespace std;

int bowl[101];
int map[101][101];
int n, k;
vector<int> v;
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };

struct node {
	int x1;
	int y1;
	int x2;
	int y2;
	int d;
};

int check()
{
	// 최소값, 최대값 차이, 최소값 리스트 한 번에 처리
	int minval = 2134567890;
	int maxval = 0;
	v.clear();
	for (int i = 0; i < n; i++) {
		if (minval > bowl[i]) {
			minval = bowl[i];
			v.clear();
			v.push_back(i);
		}
		else if (minval == bowl[i]) v.push_back(i);
		maxval = maxval < bowl[i] ? bowl[i] : maxval;
	}

	return maxval - minval;
}

void stack_bowl()
{
	int idx = 0;
	// 옮길 부부을 마스킹
	int mask[2] = { 1, 1 };

	for (int i = 0; i < n; i++) {
		map[0][i] = bowl[i];
	}

	while (1) {
		if (idx + mask[0] + mask[1] > n) break;
		for (int i = 0; i < mask[0]; i++) {
			for (int j = 0; j < mask[1]; j++) {
				map[mask[1] - j][idx + mask[1] + i] = map[i][idx + j];
				map[i][idx + j] = -1;
			}
		}
		idx += mask[1];
		// (1, 1), (2, 1), (2, 2), (3, 2) ... 마스킹 하는 칸이 늘어나는 규칙
		if (mask[0] == mask[1]) mask[0]++;
		else mask[1]++;
	}
}

void stack_bowl2()
{
	int idx = 0;
	int mask[2] = { 1, n/2 };

	for (int i = 0; i < n; i++) {
		map[0][i] = bowl[i];
	}

	for (int t = 0; t < 2; t++) {
		for (int i = 0; i < mask[0]; i++) {
			for (int j = 0; j < mask[1]; j++) {
				map[mask[0] * 2 - i - 1][idx + mask[1] * 2 - j - 1] = map[i][idx + j];
				map[i][idx + j] = -1;
			}
		}
		idx += mask[1];
		mask[0] *= 2;
		mask[1] /= 2;
	}
}

void move_fish()
{
	vector<node> v;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] == -1) continue;
			for (int k = 0; k < 4; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];

				if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
				if (map[nx][ny] == -1) continue;
				if (abs(map[i][j] - map[nx][ny]) < 5) continue;
				// 반대의 경우는 다른 칸에서 처리
				if (map[i][j] > map[nx][ny]) {
					v.push_back({ i, j, nx, ny, (map[i][j] - map[nx][ny]) / 5 });
				}
			}
		}
	}

	for (auto move : v) {
		// 0 이하가 될 가능성은 없나,,
		map[move.x1][move.y1] -= move.d;
		map[move.x2][move.y2] += move.d;
	}
}

void sort()
{
	int idx = 0;
	// 순서에 맞게 빈 칸이 아닌 값을 정렬
	for (int j = 0; j < n; j++) {
		if (map[0][j] == -1) continue;
		if (idx >= n)break;
		for (int i = 0; i < n; i++) {
			if (map[i][j] == -1) break;
			bowl[idx++] = map[i][j];
			map[i][j] = -1;
		}
	}
}

void organize()
{
	// 1. 물고기 한 마리씩 넣기
	for (int i : v) bowl[i] ++;

	// 2. 어항 쌓기
	stack_bowl();

	// 3. 물고기 수 조절
	move_fish();

	// 4. 일렬로 정렬
	sort();

	// 5. 어항 쌓기2
	stack_bowl2();

	// 6. 물고기 수 조절
	move_fish();

	// 7. 일렬로 정렬
	sort();
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	// 초기화
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			map[i][j] = -1;
		}
	}
	for (int i = 0; i < n; i++) {
		cin >> bowl[i];
	}

	int answer = 0;
	while (1) {
		// k 확인
		if (check() <= k) break;

		// 정리
		organize();

		answer++;
	}

	cout << answer;

	return 0;
}