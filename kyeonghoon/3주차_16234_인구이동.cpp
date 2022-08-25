#include<iostream>
#include<queue>
#include<tuple>
#include<cstring>
using namespace std;

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

int n,l, r, ttime;
int a[50][50];
int visited[50][50];
int lock[50][50];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> l >> r;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> a[i][j];
		}
	}
	
	while (true) {
		bool ok = false;
		memset(visited, 0, sizeof(visited));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (visited[i][j]==1)continue;
				queue<pair<int, int>> q,q2;
				int size = 1;
				int sum = a[i][j];
				visited[i][j] = 1;
				q.push({ i,j });
				q2.push({ i,j });
				while (!q.empty()) {
					int x, y;
					tie(x, y) = q.front(); q.pop();
					for (int k = 0; k < 4; k++) {
						int nx = x + dx[k];
						int ny = y + dy[k];
						if (nx < 0 || nx >= n || ny < 0 || ny >= n)continue;
						if (visited[nx][ny]==1)continue;
						if (l <= abs(a[x][y] - a[nx][ny]) && abs(a[x][y] - a[nx][ny]) <= r) {
							ok = true;
							visited[nx][ny] = 1;
							sum += a[nx][ny];
							size += 1;
							q.push({ nx,ny });
							q2.push({ nx,ny });
						}
					}
				}
				sum /= size;
				while (!q2.empty()) {
					int x, y;
					tie(x, y) = q2.front();
					a[x][y] = sum;
					q2.pop();
				}
			}
		}
		if (!ok) {
			break;
		}
		ttime += 1;
	}
	cout << ttime;
}
