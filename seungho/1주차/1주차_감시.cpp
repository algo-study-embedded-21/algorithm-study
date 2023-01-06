#include <iostream>
#include <vector>
using namespace std;

int N, M;
int MAP[9][9] = { 0 };
string arr[9][9];
struct node {
	int y;
	int x;
};

vector<node> v;
int cnt = 0;
int maxa = 0;

void up(node now) {
	for (int u = now.y - 1; u >= 0; u--) {
		if (MAP[u][now.x] == 6) break;
		if (MAP[u][now.x] > 0) continue;
		if (arr[u][now.x][0] == '#') {
			arr[u][now.x] += "#";
			continue;
		}
		arr[u][now.x] = "#";
		cnt++;
	}
}
void down(node now) {
	for (int d = now.y + 1; d < N; d++) {
		if (MAP[d][now.x] == 6) break;
		if (MAP[d][now.x] > 0) continue;
		if (arr[d][now.x][0] == '#') {
			arr[d][now.x] += "#";
			continue;
		}
		arr[d][now.x] = "#";
		cnt++;
	}
}
void left(node now) {
	for (int l = now.x - 1; l >= 0; l--) {
		if (MAP[now.y][l] == 6) break;
		if (MAP[now.y][l] > 0) continue;
		if (arr[now.y][l][0] == '#') {
			arr[now.y][l] += "#";
			continue;
		}
		arr[now.y][l] = "#";
		cnt++;
	}
}
void right(node now) {
	for (int r = now.x + 1; r < M; r++) {
		if (MAP[now.y][r] == 6) break;
		if (MAP[now.y][r] > 0) continue;
		if (arr[now.y][r][0] == '#') {
			arr[now.y][r] += "#";
			continue;
		}
		arr[now.y][r] = "#";
		cnt++;
	}
}

void mup(node now) {
	for (int u = now.y - 1; u >= 0; u--) {
		if (MAP[u][now.x] == 6) break;
		if (arr[u][now.x] == "#") {
			arr[u][now.x] = "";
			cnt--;
		}
		else {
			arr[u][now.x] = arr[u][now.x].substr(0, arr[u][now.x].size() - 1);
		}
	}
}
void mdown(node now) {
	for (int d = now.y + 1; d < N; d++) {
		if (MAP[d][now.x] == 6) break;
		if (arr[d][now.x] == "#") {
			arr[d][now.x] = "";
			cnt--;
		}
		else {
			arr[d][now.x] = arr[d][now.x].substr(0, arr[d][now.x].size() - 1);
		}
	}
}
void mleft(node now) {
	for (int l = now.x - 1; l >= 0; l--) {
		if (MAP[now.y][l] == 6) break;
		if (arr[now.y][l] == "#") {
			arr[now.y][l] = "";
			cnt--;
		}
		else {
			arr[now.y][l] = arr[now.y][l].substr(0, arr[now.y][l].size() - 1);
		}
	}
}
void mright(node now) {
	for (int r = now.x + 1; r < M; r++) {
		if (MAP[now.y][r] == 6) break;
		if (arr[now.y][r] == "#") {
			arr[now.y][r] = "";
			cnt--;
		}
		else {
			arr[now.y][r] = arr[now.y][r].substr(0, arr[now.y][r].size() - 1);
		}
	}
}

void func(int a) {
	int h = 0;
	if (a == v.size()) {
		if (cnt > maxa) {
			maxa = cnt;
		}
		return;
	}
	node now = v[a];

	if (MAP[now.y][now.x] == 1) {
		for (int i = 0; i < 4; i++) {
			if (i == 0) up(now);
			else if (i == 1) right(now);
			else if (i == 2) down(now);
			else left(now);
			func(a + 1);
			if (i == 0) mup(now);
			else if (i == 1) mright(now);
			else if (i == 2) mdown(now);
			else mleft(now);
		}
	}
	if (MAP[now.y][now.x] == 2) {
		for (int i = 0; i < 2; i++) {
			if (i == 0) {
				left(now);
				right(now);
			}
			else {
				up(now);
				down(now);
			}
			func(a + 1);
			if (i == 0) {
				mleft(now);
				mright(now);
			}
			else {
				mup(now);
				mdown(now);
			}
		}
	}
	if (MAP[now.y][now.x] == 3) {
		for (int i = 0; i < 4; i++) {
			if (i == 0) {
				up(now);
				right(now);
			}
			else if (i == 1) {
				up(now);
				left(now);
			}
			else if (i == 2) {
				left(now);
				down(now);
			}
			else {
				right(now);
				down(now);
			}
			func(a + 1);
			if (i == 0) {
				mup(now);
				mright(now);
			}
			else if (i == 1) {
				mup(now);
				mleft(now);
			}
			else if (i == 2) {
				mleft(now);
				mdown(now);
			}
			else {
				mright(now);
				mdown(now);
			}
		}
	}
	if (MAP[now.y][now.x] == 4) {
		for (int i = 0; i < 4; i++) {
			if (i == 0) {
				up(now);
				right(now);
				left(now);
			}
			else if (i == 1) {
				up(now);
				down(now);
				left(now);
			}
			else if (i == 2) {
				left(now);
				down(now);
				right(now);
			}
			else {
				right(now);
				down(now);
				up(now);
			}
			func(a + 1);
			if (i == 0) {
				mup(now);
				mright(now);
				mleft(now);
			}
			else if (i == 1) {
				mup(now);
				mdown(now);
				mleft(now);
			}
			else if (i == 2) {
				mleft(now);
				mdown(now);
				mright(now);
			}
			else {
				mright(now);
				mdown(now);
				mup(now);
			}
		}
	}
	if (MAP[now.y][now.x] == 5) {
		up(now);
		down(now);
		right(now);
		left(now);
		func(a + 1);
		mup(now);
		mdown(now);
		mright(now);
		mleft(now);
	}

}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();
	int numz = 0;
	cin >> N >> M;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < M; i++) {
			int p;
			cin >> p;
			if (p != 0) {
				numz++;
			}
			MAP[j][i] = p;
			if (p > 0 && p < 6) v.push_back({ j,i });
		}
	}
	func(0);
	cout << N * M - maxa-numz;
	return 0;
}
