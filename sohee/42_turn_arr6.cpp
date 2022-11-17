#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int n, r, k, l, range, len;
int arr[128][128];
vector<vector<int>> narr(128, vector<int>(128));

void copyArr() {
	for (int i = 0; i < range; i++) {
		for (int j = 0; j < range; j++) {
			arr[i][j] = narr[i][j];
		}
	}
}

void op1() {
	for (int i = 0; i < range; i += len) {
		for (int j = 0; j < range; j += len) {
			for (int x = 0; x < len / 2; x++) {
				for (int y = 0; y < len; y++) {
					int temp = arr[i + x][j + y];
					arr[i + x][j + y] = arr[i + len - x - 1][j + y];
					arr[i + len - x - 1][j + y] = temp;
				}
			}
		}
	}
}

void op2() {
	for (int i = 0; i < range; i += len) {
		for (int j = 0; j < range; j += len) {
			for (int x = 0; x < len / 2; x++) {
				for (int y = 0; y < len; y++) {
					int temp = arr[i + y][j + x];
					arr[i + y][j + x] = arr[i + y][j + (len - x - 1)];
					arr[i + y][j + (len - x - 1)] = temp;
				}
			}
		}
	}
}

void op3() {
	for (int i = 0; i < range; i += len) {
		for (int j = 0; j < range; j += len) {
			for (int x = 0; x < len; x++) {
				for (int y = 0; y < len; y++) {
					narr[i + y][j + len - x - 1] = arr[i + x][j + y];
				}
			}
		}
	}
	copyArr();
}

void op4() {
	for (int i = 0; i < range; i += len) {
		for (int j = 0; j < range; j += len) {
			for (int x = 0; x < len; x++) {
				for (int y = 0; y < len; y++) {
					narr[i + len - y - 1][j + x] = arr[i + x][j + y];
				}
			}
		}
	}
	copyArr();
}

void op5() {
	int N = range / len;
	for (int i = 0; i < N / 2; i++) {
		for (int x = 0; x < len; x++) {
			for (int y = 0; y < range; y++) {
				int temp = arr[i * len + x][y];
				arr[i * len + x][y] = arr[(N - i - 1) * len + x][y];
				arr[(N - i - 1) * len + x][y] = temp;
			}
		}
	}
}

void op6() {
	int N = range / len;
	for (int i = 0; i < N / 2; i++) {
		for (int x = 0; x < range; x++) {
			for (int y = 0; y < len; y++) {
				int temp = arr[x][i * len + y];
				arr[x][i * len + y] = arr[x][(N - i - 1) * len + y];
				arr[x][(N - i - 1) * len + y] = temp;
			}
		}
	}
}

void op7() {
	int N = range / len;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int x = 0; x < len; x++) {
				for (int y = 0; y < len; y++) {
					narr[j * len + x][(N - i - 1) * len + y] = arr[i * len + x][j * len + y];
				}
			}
		}
	}
	copyArr();
}

void op8() {
	int N = range / len;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int x = 0; x < len; x++) {
				for (int y = 0; y < len; y++) {
					narr[(N - j - 1) * len + x][i * len + y] = arr[i * len + x][j * len + y];
				}
			}
		}
	}
	copyArr();
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	// 함수 포인터 배열에 등록해 사용
	void(*fp[8]) ();
	fp[0] = op1; fp[1] = op2; fp[2] = op3; fp[3] = op4; fp[4] = op5; fp[5] = op6; fp[6] = op7; fp[7] = op8;

	cin >> n >> r;
	range = pow(2, n);

	for (int i = 0; i < range; i++) {
		for (int j = 0; j < range; j++) {
			cin >> arr[i][j];
		}
	}

	for (int i = 0; i < r; i++) {
		cin >> k >> l;
		len = pow(2, l);
		// if나 switch 대신 함수 포인터 배열로 함수 호출
		fp[k - 1]();
	}

	for (int i = 0; i < range; i++) {
		for (int j = 0; j < range; j++) {
			cout << arr[i][j] << ' ';
		}
		cout << '\n';
	}

	return 0;
}