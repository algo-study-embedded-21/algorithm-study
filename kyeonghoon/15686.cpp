#include<iostream>
#include<queue>
using namespace std;

int n, m, ans=1e9;
int a[50][50],b[50][50];
vector<pair<int, int>> chi;
#define X first
#define Y second

int check(int p[][50]) {
	int ans1 = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (p[i][j] == 1) {
				int sum = 100;
				for (auto x : chi) {
					int tmp = (abs(i - x.X) + abs(j - x.Y));
					sum = min(tmp, sum);
				}
				ans1 += sum;
			}
		}
	}
	return ans1;
}

void dfs(int num,int sx,int sy) {
	if (num == m) {
		int tmp = check(b);
		ans = min(tmp, ans);
		return;
	}
	for (int i = sx; i < n; i++) {
		for (int j = sy; j < n; j++) {
			if (a[i][j] == 2 && b[i][j]==0) {
				chi.push_back({ i,j });
				b[i][j] = 2;
				dfs(num + 1,i,j);
				b[i][j] = 0;
				chi.pop_back();
			}
		}
		sy = 0;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> a[i][j];
			if (a[i][j] != 2) {
				b[i][j] = a[i][j];
			}
		}
	}
	dfs(0,0,0);
	cout << ans;
}
