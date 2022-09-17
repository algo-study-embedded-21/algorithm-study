#include<iostream>
#include<vector>
using namespace std;

struct edge {
	int w, s, d;
};

int dx[] = { -1,-1,0,1,1,1,0,-1 };
int dy[] = { 0,1,1,1,0,-1,-1,-1 };

vector<edge> fire[50][50], n_fire[50][50];
int n, m, k;

void move_fire() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (fire[i][j].size() == 0)continue;
			for (auto p : fire[i][j]) {
				int nx = (i + dx[p.d] * p.s) % n;
				int ny = (j + dy[p.d] * p.s) % n;
				if (nx < 0)nx += n;
				if (ny < 0)ny += n;
				n_fire[nx][ny].push_back({ p.w,p.s,p.d });
			}
			fire[i][j].clear();
		}
	}
}

void check_fire() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (n_fire[i][j].size() == 0)continue;
			if (n_fire[i][j].size() > 1) {
				int w_sum = 0;
				int s_sum = 0;
				bool ok = true;
				int flag = n_fire[i][j][0].d % 2;
				for (auto p : n_fire[i][j]) {
					w_sum += p.w;
					s_sum += p.s;
					if (p.d % 2 != flag) {
						ok = false;
					}
				}
				w_sum /= 5;
				s_sum /= n_fire[i][j].size();
				//질량이 영인 파이어볼은 애초에 잘라버림.
				if (w_sum == 0) {
					//시간 오래걸렸던 부분
					n_fire[i][j].clear();
					continue;
				}
				//파이어볼의 방향이 모두 홀수 or 짝수
				if (ok) {
					for (int k = 0; k < 8; k += 2) {
						fire[i][j].push_back({ w_sum,s_sum,k });
					}
				}
				else {
					for (int k = 1; k < 8; k += 2) {
						fire[i][j].push_back({ w_sum,s_sum,k });
					}
				}
				n_fire[i][j].clear();
			}
			else {
				fire[i][j].push_back({ n_fire[i][j][0].w,n_fire[i][j][0].s,n_fire[i][j][0].d });
				n_fire[i][j].clear();
			}
		}
	}
}

int left_fire() {
	int sum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (fire[i][j].size() == 0)continue;
			for (auto x : fire[i][j]) {
				sum += x.w;
			}
		}
	}
	return sum;
}

void input() {
	cin >> n >> m >> k;
	for (int i = 0; i < m; i++) {
		int r, c, w, s, d;
		cin >> r >> c >> w >> s >> d;
		r--; c--;
		fire[r][c].push_back({ w,s,d });
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	input();
	for (int i = 0; i < k; i++) {
		move_fire();
		check_fire();
	}
	cout << left_fire();
	return 0;
}
