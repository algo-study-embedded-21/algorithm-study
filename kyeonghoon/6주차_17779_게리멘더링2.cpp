#include<iostream>
#include<queue>
using namespace std;

int n;
int map[21][21];
int max_val = 0, min_val = 40000, ans=40000;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	int total = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
			total += map[i][j];
		}
	}
	for (int d1 = 1; d1 < n; d1++) {
		for (int d2 = 1; d2 < n; d2++) {
			for (int x = 1; x + d1 + d2 <= n; x++) {
				for (int y = 1 + d1; y + d2 <= n; y++) {
					int visited[21][21] = { 0 };
					//경계선
					for (int i = 0; i <= d1; i++) {
						visited[x + i][y - i] = 1;
						visited[x + d2 + i][y + d2 - i] = 1;
					}
					for (int i = 0; i <= d2; i++) {
						visited[x + i][y + i] = 1;
						visited[x + d1 + i][y - d1 + i] = 1;
					}
					int tmp = total;
					//1번
					int sum = 0;
					for (int r = 1; r < x + d1; r++) {
						for (int c = 1; c <= y; c++) {
							if (visited[r][c])break;
							sum += map[r][c];
						}
					}
					tmp -= sum;
					min_val = min(sum, min_val);
					max_val = max(sum, max_val);
					sum = 0;
					//2번
					for (int r = 1; r <= x + d2; r++) {
						for (int c = n; c > y; c--) {
							if (visited[r][c])break;
							sum += map[r][c];
						}
					}
					tmp -= sum;
					min_val = min(sum, min_val);
					max_val = max(sum, max_val);
					sum = 0;
					//3번
					for (int r = x + d1; r <= n; r++) {
						for (int c = 1; c < y - d1 + d2; c++) {
							if (visited[r][c])break;
							sum += map[r][c];
						}
					}
					tmp -= sum;
					min_val = min(sum, min_val);
					max_val = max(sum, max_val);
					sum = 0;
					//4번
					for (int r = x + d2 + 1; r <= n; r++) {
						for (int c = n; c >= y - d1 + d2; c--) {
							if (visited[r][c])break;
							sum += map[r][c];
						}
					}
					tmp-= sum;
					min_val = min(sum, min_val);
					max_val = max(sum, max_val);
					sum = 0;
					//5번
					min_val = min(tmp, min_val);
					max_val = max(tmp, max_val);
					//결과
					int val = abs(max_val - min_val);
					max_val = 0, min_val = 40000;
					ans = min(ans, val);
				}
			}
		}
	}
	cout << ans;
}
