#include <iostream>

using namespace std;

int N, L;
int MAP[202][101];
int used[202][101];
int gap[201][101];
int brid[201][101];
int cnt;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();

	cin >> N >> L;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];

			MAP[N + j][i] = MAP[i][j];
		} 
	}

	for (int i = 0; i < 2 * N; i++) {
		for (int j = 0; j < N; j++) {
			if (j > 0 && MAP[i][j] == MAP[i][j - 1]) {
				used[i][j] = used[i][j - 1] + MAP[i][j];
			}
			else if (j == 0 || MAP[i][j] != MAP[i][j - 1]) {
				used[i][j] = MAP[i][j];
			}
		}
	}

	for (int i = 0; i < 2 * N; i++) {
		for (int j = 0; j < N - 1; j++) {
			gap[i][j] = MAP[i][j + 1] - MAP[i][j];
		}
		gap[i][N - 1] = MAP[i][N - 1];
	}

	for (int i = 0; i < 2 * N; i++) {
		int flag = 0;
		for (int j = 0; j < N - 1; j++) {
			if (gap[i][j] > 1 || gap[i][j] < -1) flag = 1;
			if (gap[i][j] == 1) {
                if(j - L < -1) flag = 1;
				if (used[i][j] >= MAP[i][j] * L) {
					for (int k = 0; k < L; k++) {
						if (brid[i][j - k])
							flag = 1;
						else
							brid[i][j - k] = 1;
					}
				}
				else flag = 1;
			}
			if (gap[i][j] == -1) {
				if (j + L >= N) flag = 1;
				if (used[i][j + L] >= MAP[i][j + L] * L) {
					for (int k = 1; k <= L; k++) {
						if (j+k != N-1 && gap[i][j + k] == 1)
							flag = 1;
						else {
			 				if (brid[i][j + k])
								flag = 1;
							else
								brid[i][j + k] = 1;
						}
					}
				}
				else flag = 1;
			}
		}
		if (!flag) {
			cnt++;
		}
	}

	cout << cnt << '\n';

}