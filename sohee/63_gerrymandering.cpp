#include <iostream>
#include <queue>
using namespace std;

int n;
int arr[10]; // 인구수
int map[10][10]; // 연결된 지역 표시
int sep[10]; // 구역 나누기 ( 0 || 1 )
int ans = 2134567890; 
int parents[10]; 
int groupCnt[10];

int Find(int x) {
	if (parents[x] == x) return x;
	return Find(parents[x]);
}

void Union(int x, int y) {
	int px = Find(x);
	int py = Find(y);
	
	if (px == py) return;
	groupCnt[py] = 0;
	parents[py] = px;
}

void check() {
	int one = 0;
	int zero = 0;
	for (int i = 0; i < n; i++) {
		parents[i] = i;
		groupCnt[i] = 1;
	}
	for (int i = 0; i < n; i++) {
		if (sep[i]) {
			one += arr[i];
		}
		else {
			zero += arr[i];
		}
		// 연결된 같은 선거구는 Union-Find
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			if (!map[i][j]) continue;
			if (sep[i] == sep[j]) Union(i, j);
		}
	}

	// 선거구는 무조건 2개
	int cnt = 0;
	for (int i = 0; i < n; i++) cnt += groupCnt[i];
	if (cnt != 2) return;
	//if (one == 0 || zero == 0) return;
	ans = min(ans, abs(one - zero));
}


void dfs(int level) {
	if (level == n) {
		check();
		return;
	}

	sep[level] = 1;
	dfs(level + 1);
	sep[level] = 0;
	dfs(level + 1);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++) cin >> arr[i];
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		for (int j = 0; j < x; j++) {
			int y;
			cin >> y;
			map[i][y - 1] = 1;
		}
	}

	dfs(0);

	if (ans == 2134567890) ans = -1;
	cout << ans;

	return 0;
}