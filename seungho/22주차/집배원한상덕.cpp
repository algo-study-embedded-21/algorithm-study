#include <iostream>
#include <set>
#include <vector>
#include <queue>
using namespace std;

int N;
int altitude[50][50];
char MAP[50][50];
int sy, sx;
int K = 0;
int ans = 2134567890;

set<int> s;
vector<int> v;

int diry[8] = { -1,-1,-1,0,1,1,1,0 };
int dirx[8] = { -1,0,1,1,1,0,-1,-1 };

int bfs(int left, int right) {
	int cnt = 0;
	int visited[50][50] = {0};
	queue<pair<int, int>> q;
	if (altitude[sy][sx] >= left && altitude[sy][sx] <= right) {
		q.push({ sy,sx });
		visited[sy][sx] = 1;
	}
	while (!q.empty()) {
		int r = q.front().first;
		int c = q.front().second;
		q.pop();

		for (int d = 0; d < 8; d++) {
			int ny = r + diry[d];
			int nx = c + dirx[d];
			if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
			if (visited[ny][nx]) continue;
			if (altitude[ny][nx]<left || altitude[ny][nx] > right) continue;
			q.push({ ny,nx });
			visited[ny][nx] = 1;
			if (MAP[ny][nx] == 'K') cnt++;
		}
	}
	if (cnt == K) {
		ans = min(ans, right - left);
		return 1;
	}
	return 0;
}

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			char area;
			cin >> area;
			if (area == 'P') {
				sy = i;
				sx = j;
			}
			if (area == 'K') {
				MAP[i][j] = area;
				K++;
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> altitude[i][j];
			s.insert(altitude[i][j]);
		}
	}

	for (set<int>::iterator iter = s.begin(); iter != s.end(); iter++) v.push_back(*iter);

	int left = 0;
	int right = 0;

	while (left <= right) {
		if (left >= v.size() || right >= v.size()) break;
		if (bfs(v[left], v[right])) left++;
		else right++;
	}

	cout << ans;
	return 0;
}
