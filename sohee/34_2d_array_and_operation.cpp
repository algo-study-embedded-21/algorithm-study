#include <iostream>
using namespace std;

int arr[100][100];
// 각 행, 열 사이즈
int row[100];
int col[100];
// 가장 긴 행, 열 사이즈
int max_row = 0;
int max_col = 0;
int r, c, k;
int ans = -1;

void sort_row(int row_num) {
	// dat 이용해 각 수의 개수 파악
	int n_arr[101] = {0};
	for (int i = 0; i < row[row_num]; i++) {
		n_arr[arr[row_num][i]]++;
	}
	// 0은 취급 안함
	n_arr[0] = 0;

	int idx = 0;
	while (idx < 100) {
		int i = 0;
		int val = 2134567890;
		// 범위 체크 실수
		for (int j = 0; j <= 100; j++) {
			// 제일 개수가 적은 수, 크기가 작은 수부터
			if (n_arr[j] != 0 && n_arr[j] < val) {
				i = j;
				val = n_arr[j];
			}
		}
		// 모든 수가 0이면 반복문 탈출
		if (val == 2134567890) {
			break;
		}

		// 숫자, 개수 저장
		arr[row_num][idx] = i;
		idx++;
		arr[row_num][idx] = val;
		idx++;
		n_arr[i] = 0;
	}

	// 변화된 행의 길이 저장
	if (row[row_num] > idx) {
		for (int j = idx; j < row[row_num]; j++) arr[row_num][j] = 0;
	}
	row[row_num] = idx;
}

void sort_col(int col_num) {
	int n_arr[101] = {0};
	for (int i = 0; i < col[col_num]; i++) {
		n_arr[arr[i][col_num]]++;
	}
	n_arr[0] = 0;

	int idx = 0;
	while (idx < 100) {
		int i = 0;
		int val = 2134567890;
		for (int j = 0; j <= 100; j++) {
			if (n_arr[j] != 0 && n_arr[j] < val) {
				i = j;
				val = n_arr[j];
			}
		}
		if (val == 2134567890) {
			break;
		}

		arr[idx][col_num] = i;
		idx++;
		arr[idx][col_num] = val;
		idx++;
		n_arr[i] = 0;
	}
	if (col[col_num] > idx) {
		for (int j = idx; j < col[col_num]; j++) arr[j][col_num] = 0;
	}
	col[col_num] = idx;
}

// R연산
void operation_R() {
	int range = max_row;
	for (int i = 0; i < range; i++) {
		// 한 줄 정렬
		sort_row(i);
	}
	// 가장 긴 열 찾기
	int cnt = 0;
	for (int i = 0; i < 100; i++) {
		cnt = max(cnt, row[i]);
	}
	max_col = cnt;

	// 변한 열, 행 정보 갱신
	int val = 0;
	for (int i = 0; i < 100; i++) {
		int idx = 0;
		for (int j = 0; j < 100; j++) {
			if (arr[j][i] != 0) idx = j + 1;
		}
		col[i] = idx;
		val = max(val, idx);
	}
	max_row = val;
}

// C연산
void operation_C() {
	int range = max_col;
	for (int i = 0; i < range; i++) {
		sort_col(i);
	}
	int cnt = 0;
	for (int i = 0; i < 100; i++) {
		cnt = max(cnt, col[i]);
	}
	max_row = cnt;

	int val = 0;
	for (int i = 0; i < 100; i++) {
		int idx = 0;
		for (int j = 0; j < 100; j++) {
			if (arr[i][j] != 0) idx = j + 1;
		}
		row[i] = idx;
		val = max(val, idx);
	}
	max_col = val;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	// 초기화
	cin >> r >> c >> k;
	r--; c--;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> arr[i][j];
		}
		row[i] = 3;
		col[i] = 3;
	}

	max_row = 3;
	max_col = 3;

	for (int i = 0; i <= 100; i++) {
		if (arr[r][c] == k) {
			ans = i;
			break;
		}

		if (max_row >= max_col) {
			operation_R();
		}
		else if (max_row < max_col) {
			operation_C();
		}
	}

	cout << ans;

	return 0;
}