#include <iostream>
using namespace std;

int main() {
	int N, M, H;
	cin >> N >> M >> H;

	int MAP[31][11]={0};

	int ans = 0;

	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		MAP[a][b] = 1;
	}

	for (int j = 1; j < N; j++) {
		int cnt = 0;
		for (int i = 1; i <= H; i++) {
			if (MAP[i][j] == 1) cnt++;
			if (i>1 && i<H && MAP[i][j] == 1 && MAP[i - 1][j + 1] == 1 && MAP[i + 1][j + 1] == 1) {
				cout << -1;
				return 0;
			}
			if (j>1 && i > 1 && i < H && MAP[i][j] == 1 && MAP[i - 1][j - 1] == 1 && MAP[i + 1][j - 1] == 1) {
				cout << -1;
				return 0;
			}
		}
		if (cnt % 2 == 1) {	
			ans++;
		}
	}

	cout << ans;

	return 0;
}
