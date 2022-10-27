#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
struct node {
	int x;
	int y;
};
int r, c, k;
int MAP[101][101];
int visited[101];
int M=3;
int N=3;
int ans = 0;
bool com(node a, node b) {
	if (a.y < b.y) {
		return true;
	}
	else if (a.y == b.y) {
		if (a.x < b.x)
			return true;
	}
	return false;
}

void solve() {
	if (MAP[r][c] == k){
		ans = 0;
		return;
	}
	int cnt = 0;
	while (true) {
		cnt++;
		if (cnt > 100){
			ans = -1;
			return;
		}
		if (N >= M) {
			for (int i = 0; i < N; i++) {
				memset(visited, 0, sizeof(visited));
				vector<node> v;
				int Maxnum = 0;
				for (int j = 0; j < M; j++) {
					if (MAP[i][j] == 0)
						continue;
					else {
						visited[MAP[i][j]]++;
						Maxnum = max(Maxnum, MAP[i][j]);
					}
					MAP[i][j] = 0;
				}
				for (int j = 1; j <= Maxnum; j++) {
					if (visited[j] == 0)
						continue;
					else
						v.push_back({ j,visited[j] });
				}
				sort(v.begin(), v.end(), com);
				int s = v.size();
				if (s > 49) {
					s = 49;
				}
				int nn = 0;
				for (int j = 0; j < s; j++) {
					MAP[i][nn++] = v.at(j).x;
					MAP[i][nn++] = v.at(j).y;
				}
				M = max(M, nn);
			}
		}
		else {
			for (int i = 0; i < M; i++) {
				memset(visited, 0, sizeof(visited));
				vector<node> v;
				int Maxnum = 0;
				for (int j = 0; j < N; j++) {
					if (MAP[j][i] == 0)
						continue;
					else {
						visited[MAP[j][i]]++;
						Maxnum = max(Maxnum, MAP[j][i]);
					}
					MAP[j][i] = 0;
				}
				for (int j = 1; j <= Maxnum; j++) {
					if (visited[j] == 0)
						continue;
					else
						v.push_back({ j,visited[j] });
				}
				sort(v.begin(), v.end(), com);
				int s = v.size();
				if (s > 49) {
					s = 49;
				}
				int nn = 0;
				for (int j = 0; j < s; j++) {
					MAP[nn++][i] = v.at(j).x;
					MAP[nn++][i] = v.at(j).y;
				}
				N= max(N, nn);
			}
		}
		if (MAP[r][c] == k) {
			ans = cnt;
			return;
		}
	}
}
int main() {
	cin >> r >> c >> k;
	r -= 1;
	c -= 1;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> MAP[i][j];
		}
	}
	solve();
	cout << ans << endl;
	
}