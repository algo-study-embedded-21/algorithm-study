#include <iostream>
using namespace std;

int n;
int map[100][100];
long long path[100][100];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}

	path[0][0] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] == 0) break;
			if (i + map[i][j] < n) {
				path[i + map[i][j]][j] += path[i][j];
			}
			if (j + map[i][j] < n) {
				path[i][j + map[i][j]] += path[i][j];
			}
		}
	}

	cout << path[n - 1][n - 1];

	return 0;
}