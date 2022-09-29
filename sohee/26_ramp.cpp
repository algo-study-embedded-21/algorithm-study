#include <iostream>
using namespace std;

int n, l;
pair<int, int> map[101][101];
int answer;

void find_row(int r) {
	int pre = map[r][0].first;

	for (int i = 1; i < n; i++) {
		if (pre == map[r][i].first) continue;

		if (abs(pre - map[r][i].first) > 1) return;
		if (pre > map[r][i].first) {
			for (int j = i; j < i + l; j++) {
				if (j == n) return;
				if (map[r][j].first != map[r][i].first) return;
				map[r][j].second = 1;
			}
		}
		else {
			for (int j = i - 1; j >= i - l; j--) {
				if (j < 0) return;
				if (map[r][j].second == 1) return;
				if (map[r][j].first != map[r][i - 1].first) return;
				map[r][j].second = 1;
			}
		}
		pre = map[r][i].first;
	}

	answer++;
}

void find_column(int c) {
	int pre = map[0][c].first;

	for (int i = 1; i < n; i++) {
		if (pre == map[i][c].first) continue;

		if (abs(pre - map[i][c].first) > 1) return;
		if (pre > map[i][c].first) {
			for (int j = i; j < i + l; j++) {
				if (j == n) return;
				if (map[j][c].first != map[i][c].first) return;
				map[j][c].second = 1;
			}
		}
		else {
			for (int j = i - 1; j >= i - l; j--) {
				if (j < 0) return;
				if (map[j][c].second == 1) return;
				if (map[j][c].first != map[i - 1][c].first) return;
				map[j][c].second = 1;
			}
		}
		pre = map[i][c].first;
	}

	answer++;
}

void check() {
	// 행 확인
	for (int i = 0; i < n; i++) {
		find_row(i);
	}

	// 초기화
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			map[i][j].second = 0;
		}
	}

	// 열 확인
	for (int i = 0; i < n; i++) {
		find_column(i);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> l;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int x;
			cin >> x;
			// 높이, 경사로 설치 유무
			map[i][j] = { x, 0 };
		}
	}

	check();

	cout << answer;

	return 0;
}