#include<iostream>
#include<queue>
using namespace std;

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

int a[500][500];
int visited[500][500];
int n, m, ans;

int tdx[4][3][2] = {
	{{0,-1},{-1,0},{0,1}},
	{{0,-1},{-1,0},{1,0}},
	{{1,0},{-1,0},{0,1}},
	{{0,-1},{1,0},{0,1}}
};

void dfs(int x, int y, int sum,int cnt) {
	if (cnt == 4) {
		ans = max(ans, sum);
		return;
	}
	for (int k = 0; k < 4; k++) {
		int nx = x + dx[k];
		int ny = y + dy[k];
		if (nx < 0 || nx >= n || ny < 0 || ny >= m)continue;
		if (visited[nx][ny])continue;
		visited[nx][ny] = 1;
		dfs(nx, ny, sum + a[nx][ny], cnt + 1);
		visited[nx][ny] = 0;
	}
}

int t_shape(int x, int y) {
	int answer = 0;
	for (int i = 0; i < 4; i++) {
		int sum = a[x][y];
		for (int j = 0; j < 3; j++) {
			int nx = x + tdx[i][j][0];
			int ny = y + tdx[i][j][1];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m)break;
			sum += a[nx][ny];
		}
		answer = max(answer, sum);
	}
	return answer;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			visited[i][j] = 1;
			dfs(i, j, a[i][j],1);
			visited[i][j] = 0;
			ans = max(ans, t_shape(i, j));
		}
	}
	cout << ans;
}
