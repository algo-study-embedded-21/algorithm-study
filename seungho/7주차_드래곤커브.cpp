#include <iostream>
#include <vector>
using namespace std;

int N;
int MAP[101][101] = { 0 };
int diry[4] = { 0,-1,0,1 };
int dirx[4] = { 1,0,-1,0 };

void makeCurve(int x, int y, int d, int g) {
	MAP[y][x] = 1;
	vector<int> dir;
	dir.push_back(d);
	y += diry[d];
	x += dirx[d];
	MAP[y][x] = 1;

	for (int i = 1; i <= g; i++) {
		int size = dir.size();
		for (int v = size - 1; v >= 0; v--) {
			int nd = dir[v] + 1;
			if (nd > 3) nd = 0;
			y += diry[nd];
			x += dirx[nd];
			MAP[y][x] = 1;
			dir.push_back(nd);
		}
	}
}

// r / u / l u / l d l u / l d r d l d l u
// 0 / 1 / 2 1 / 2 3 2 1 / 2 3 0 3 2 3 2 1


// u -> l
// l -> d
// d -> r
// r -> u


int main() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		int x, y, d, g;
		cin >> x >> y >> d >> g;
		makeCurve(x, y, d, g);
	}

	int ans = 0;

	// 정사각형 중 네 꼭짓점이 모두 커브의 일부인 것 count
	for (int i = 0; i < 100; i++) {
		for(int j=0;j<100;j++){
			if (MAP[i][j] * MAP[i][j + 1] * MAP[i + 1][j] * MAP[i + 1][j + 1] != 0) {
				ans++;
			}
		}
	}
	
	cout << ans;

	return 0;
}
