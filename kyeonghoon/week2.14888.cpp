#include<iostream>
using namespace std;

int n, min_val = 1e9, max_val = -min_val;
int a[11], op[4];

void dfs(int num, int sum) {
	if (num == n) {
		min_val = min(min_val, sum);
		max_val = max(max_val, sum);
		return;
	}
	if (op[0] > 0) {
		op[0] -= 1;
		dfs(num + 1, sum + a[num]);
		op[0] += 1;
	}
	if (op[1] > 0) {
		op[1] -= 1;
		dfs(num + 1, sum - a[num]);
		op[1] += 1;
	}
	if (op[2] > 0) {
		op[2] -= 1;
		dfs(num + 1, sum * a[num]);
		op[2] += 1;
	}
	if (op[3] > 0) {
		op[3] -= 1;
		dfs(num + 1, sum / a[num]);
		op[3] += 1;
	}
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < 4; i++) {
		cin >> op[i];
	}
	dfs(1, a[0]);
	cout << max_val << '\n';
	cout << min_val;
}
