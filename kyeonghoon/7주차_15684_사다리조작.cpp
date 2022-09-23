#include<iostream>
using namespace std;

int n, m, h, ans=-1;
int map[11][31];

bool check() {
	for (int i = 1; i <= m; i++) {
		int tmp = i;
		for (int j = 1; j <= h; j++) {
			//오른쪽으로 가는 가로선 있음
			if (map[j][tmp] == 1 && map[j][tmp + 1]) {
				tmp += 1;
			}
			//왼쪽으로 가는 가로선 있음
			else if (map[j][tmp] == 1 && map[j][tmp - 1]) {
				tmp -= 1;
			}
			else {
				continue;
			}
		}
		if (tmp != i) {
			return false;
		}
	}
	return true;
}

void dfs(int cnt) {
	if (cnt > 3) {
		return;
	}
	cout << cnt << '\n';
	if (check()) {
		if (ans == -1) {
			ans = cnt;
		}
		else {
			ans = min(ans, cnt);
		}
	}
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= m-1; j++) {
			if (map[i][j] != 1 && map[i][j + 1] != 1) {
				map[i][j] = 1;
				map[i][j + 1] = 1;
				dfs(cnt + 1);
				map[i][j + 1] = 0;
				map[i][j] = 0;
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> h;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		map[a][b] = 1; map[a][b + 1] = 1;
	}
	dfs(0);
	cout << ans;
}
