#include<iostream>
#include<queue>
using namespace std;

int dx[] = { 0,0,1,-1,1,-1,1,-1 };
int dy[] = { 1,-1,0,0,1,1,-1,-1 };
int n, num[151][151],best[151][151],spot;
char map[151][151];

struct node {
	int x, y, high, low;
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	queue<node> q;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			best[i][j] = 1e6;
			cin >> map[i][j];
			if (map[i][j] == 'P') {
				best[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> num[i][j];
			if (map[i][j] == 'P') {
				spot = num[i][j];
				q.push({ i,j,num[i][j],num[i][j] });
			}
		}
	}
	while (!q.empty()) {
		node now = q.front(); q.pop();
		for (int k = 0; k < 8; k++) {
			int nx = now.x + dx[k];
			int ny = now.y + dy[k];
			if (nx < 0 || nx >= n || ny < 0 || ny >= n)continue;
			if (best[now.x][now.y] >= best[nx][ny])continue;
			if (num[nx][ny] > now.high || num[nx][ny] < now.low) {
				if (num[nx][ny] > now.high) {
					int tmp = num[nx][ny] - now.low;
					if (tmp < best[nx][ny]) {
						best[nx][ny] = num[nx][ny] - now.low;
					}
					q.push({ nx,ny,num[nx][ny],now.low });
				}
				if (num[nx][ny] < now.low) {
					int tmp = now.high - num[nx][ny];
					if (tmp < best[nx][ny]) {
						best[nx][ny] = now.high - num[nx][ny];
					}
					q.push({ nx,ny,now.high,num[nx][ny] });
				}
			}
			else if(num[nx][ny]<=now.high && num[nx][ny]>=now.low) {
				int tmp = now.high - now.low;
				if (tmp < best[nx][ny]) {
					best[nx][ny] = now.high - now.low;
				}
				q.push({ nx,ny,now.high,now.low });
			}
		}
		/*cout << '\n';
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << best[i][j];
			}
			cout << '\n';
		}*/
	}
	/*cout << '\n';
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << best[i][j];
		}
		cout << '\n';
	}*/

	int ans1 = 1e6,ans2=0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] == 'K') {
				ans1 = min(best[i][j], ans1);
				ans2 = max(best[i][j],ans2);
			}
		}
	}
	cout << ans1+ans2;
}
