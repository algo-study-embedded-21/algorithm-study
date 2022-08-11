#include<iostream>
#include<vector>
using namespace std;

int ans;
int n;
int p[21], t[21];

void dfs(int day, int sum) {
	if (day == n+1) {
		ans = max(ans, sum);
		return;
	}
	if (day > n + 1)return;
	dfs(day + t[day], sum + p[day]);
	dfs(day+1 , sum);
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> t[i] >> p[i];
	}
	dfs(1, 0);
	cout << ans;
}
