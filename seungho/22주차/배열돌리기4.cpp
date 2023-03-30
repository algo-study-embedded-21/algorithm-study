#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M, K;
int MAP[51][51];
int temp_MAP[51][51];
int ans = 2134567890;
struct Node {
	int r; int c; int s;
};
vector<Node> v;

void rotate(int ind) {
	int r = v[ind].r;
	int c = v[ind].c;
	int s = v[ind].s;
	int COPY[51][51];

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			COPY[i][j] = temp_MAP[i][j];
		}
	}

	for (int i = 1; i <= s; i++) {
		for (int x = c - i + 1; x <= c + i; x++) {
			temp_MAP[c - i][x] = COPY[c - i][x - 1];
		}
		for (int y = r - i+1; y <= r + i; y++) {
			temp_MAP[y][c + i] = COPY[y - 1][c + i];
		}
		for (int x = c - i; x <= c + i - 1; x++) {
			temp_MAP[c + i][x] = COPY[c + i][x + 1];
		}
		for (int y = r - i; y <= r + i - 1; y++) {
			temp_MAP[y][c - i] = COPY[y + 1][c - i];
		}
	}
}

void find_min() {
	for (int i = 1; i <= N; i++) {
		int cnt = 0;
		for (int j = 1; j <= M; j++) {
			cnt += temp_MAP[i][j];
		}
		ans = min(cnt, ans);
	}
}

int main()
{
	cin >> N >> M >> K;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> MAP[i][j];
		}
	}

	for (int k = 0; k < K; k++) {
		int r, c, s;
		cin >> r >> c >> s;
		v.push_back({ r,c,s });
	}

	vector<int> pv(K);
	for (int i = 0; i < K; i++) {
		pv[i] = i;
	}
	
	do {
		// temp_MAP 초기화
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				temp_MAP[i][j] = MAP[i][j];
			}
		}
		// 순서대로 회전
		for (int i = 0; i < K; i++) {
			rotate(pv[i]);
		}
		// 배열 최솟값 확인
		find_min();
	} while (next_permutation(pv.begin(), pv.end()));

	cout << ans;

	return 0;
}
