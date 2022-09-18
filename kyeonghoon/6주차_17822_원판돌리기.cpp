#include<iostream>
using namespace std;

int n, m, t;
int a[52][52];
int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

void move(int num, int dir, int k) {
	while (k--) {
		if (dir == 1) {
			int temp = a[num][1];
			for (int i = 1; i < m; i++) {
				a[num][i] = a[num][i + 1];
			}
			a[num][m] = temp;
		}
		else if (dir == 0) {
			int temp = a[num][m];
			for (int i = m; i > 1; i--) {
				a[num][i] = a[num][i - 1];
			}
			a[num][1] = temp;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> t;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
		}
	}
	while (t--) {
		int x, d, k;
		cin >> x >> d >> k;
		for (int i = x; i <= n; i += x) {
			move(i, d, k);
		}
		
		for (int i = 1; i <= n; i++) {
			a[i][0] = a[i][m];
			a[i][m + 1] = a[i][1];
		}
		bool flag = false;
		double sum = 0;
		double cnt = 0;
		int visited[52][52] = {0};
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (a[i][j] == 0)continue;
				cnt += 1;
				sum += a[i][j];
                if(visited[i][j])continue;
				for (int k = 0; k < 4; k++) {
					int nx = i + dx[k];
					int ny = j + dy[k];
					if (a[nx][ny] == a[i][j]) {
						flag = true;
						visited[nx][ny] = 1;
						visited[i][j] = 1;
					}
				}
			}
		}
		if (!flag) {
			double val = sum / cnt;
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= m; j++) {
					if (a[i][j] == 0)continue;
					if (a[i][j] == val)continue;
					if (a[i][j] > val)a[i][j] -= 1;
					else a[i][j] += 1;
				}
			}
		}else{
            for (int i = 1; i <= n; i++) {
			    for (int j = 1; j <= m; j++) {
				    if (visited[i][j])a[i][j] = 0;
			    }
		    }
        }
		
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			ans += a[i][j];
		}
	}
	cout << ans << '\n';
	return 0;
}
