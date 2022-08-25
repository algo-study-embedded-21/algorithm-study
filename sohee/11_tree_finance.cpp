/*

sort를 사용하지 않기 위해 deque 사용
구조체를 사용하지 않는 것도 시간을 줄이는 데 도움이 된다고 함

*/

#include <iostream>
#include <deque>
using namespace std;

int n, m, k;
int map[11][11];
int food[11][11];

int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

deque<int> trees[11][11];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			map[i][j] = 5;
			cin >> food[i][j];
		}
	}
	for (int i = 0; i < m; i++) {
		int x, y, age;
		cin >> x >> y >> age;
		trees[x][y].push_back(age);
	}

	int time = 0;
	while (time < k) {
		int newTree[11][11] = { 0 };

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				int len = trees[i][j].size();
				int index = len;
				for (int w = 0; w < len; w++) {
					if (trees[i][j][w] > map[i][j]) {
						index = w;
						break;
					}
					map[i][j] -= trees[i][j][w];
					trees[i][j][w]++;
					if (trees[i][j][w] % 5 == 0) newTree[i][j]++;
				}
				while (index < len) { 
					map[i][j] += trees[i][j].back() / 2;
					trees[i][j].pop_back();
					index++;
				}
			}
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				map[i][j] += food[i][j];

				if (newTree[i][j] == 0) continue;
				for (int x = 0; x < 8; x++) {
					int nx = i + dx[x];
					int ny = j + dy[x];

					if (nx < 1 || nx > n || ny < 1 || ny > n) continue;
					for(int y=0; y<newTree[i][j]; y++)
						trees[nx][ny].push_front(1);
				}
			}
		}

		time++;
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cnt += trees[i][j].size();
		}
	}

	cout << cnt;

	return 0;
}