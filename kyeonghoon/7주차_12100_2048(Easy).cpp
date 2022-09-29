#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int n, ans;
int map[20][20];

void gravity(int xx[20][20]) {
	int visited[20][20] = { 0 };
	for (int i = 0; i < n; i++) {
		for (int j = n - 2; j >= 0; j--) {
			if (xx[j][i] == 0)continue;
			for (int k = j; k < n - 1; k++) {
				//같은 숫자의 블록
				if (xx[k][i] == xx[k + 1][i]){
					//합쳐진 적 없음
					if (visited[k + 1][i] != 1) {
						visited[k + 1][i] = 1;
						xx[k + 1][i] *= 2;
						xx[k][i] = 0;
						break;
					}
					//합쳐진 적 있음
					else {
						break;
					}
				}
				//비어 있음
				else if (xx[k + 1][i] == 0) {
					xx[k + 1][i] = xx[k][i];
					xx[k][i] = 0;
				}
				//다른 숫자의 블록
				else {
					break;
				}
			}
		}
	}
}

void copy_map(int aa[20][20], int bb[20][20]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			bb[i][j] = aa[i][j];
		}
	}
}

void turn(int xx[20][20], int k) {
	int tmp[20][20];
	for (int p = 0; p < k; p++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				tmp[i][j] = xx[n - j - 1][i];
			}
		}
		copy_map(tmp, xx);
	}
}

int search(int xx[20][20]) {
	int sum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			sum = max(sum, xx[i][j]);
		}
	}
	return sum;
}

void dfs(int lev, int xx[20][20]) {
	if (lev == 5) {
		int tmp = search(xx);
		ans = max(ans, tmp);
		return;
	}
	int copy[20][20] = { 0 };
	for (int i = 0; i < 4; i++) {
		copy_map(xx, copy);
		turn(copy, i);
		gravity(copy);
		dfs(lev + 1, copy);
	}
}

void input() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	input();
	dfs(0, map);
	cout << ans;
}

