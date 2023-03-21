#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

struct Node {
	int r, c, s, idx;
};

int n, m, k, a[51][51], ans = 1e9;
vector<Node> v;

bool cmp(Node a, Node b) { //struct형태의 벡터는 sort 나 next_permutation할 때 정렬 규칙을 정해줘야함
	return a.idx < b.idx; //55% 반례 -> 섞어도 겹치는 부분 있어서 idx추가해서 고유값으로 정렬
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}
	for (int i = 0; i < k; i++) {
		int r, c, s;
		cin >> r >> c >> s;
		v.push_back({ r-1,c-1,s,i });
	}
	sort(v.begin(), v.end(),cmp);
	do {
		int b[51][51] = { 0, };
		memcpy(b, a, sizeof(a));
		//k개의 연산 진행
		for (Node now : v) {
			int c[51][51] = { 0, };
			memcpy(c, b, sizeof(b));
			int sx = now.r - now.s;
			int sy = now.c - now.s;
			int len = 2 * now.s + 1;
			vector<vector<int>> tmp(len, vector<int>(len));
			for (int i = 0; i < len; i++) {
				for (int j = 0; j < len; j++) {
					tmp[i][j] = c[sx + i][sy + j];
				}
			}
			//이동
			for (int j = 0; j < now.s; j++) {
				int tt = tmp[j][len - 1 - j];
				for (int i = len - 1 - j; i >= 1 + j; i--) {
					tmp[j][i] = tmp[j][i - 1];
				}
				for (int i = j; i < len - 1 - j; i++) {
					tmp[i][j] = tmp[i + 1][j];
				}
				for (int i = j; i < len - 1 - j; i++) {
					tmp[len - 1 - j][i] = tmp[len - 1 - j][i + 1];
				}
				for (int i = len - 1 - j; i >= 2 + j; i--) {
					tmp[i][len - 1 - j] = tmp[i - 1][len - 1 - j];
				}
				tmp[1 + j][len - 1 - j] = tt;
			}
			for (int i = 0; i < len; i++) {
				for (int j = 0; j < len; j++) {
					c[sx + i][sy + j] = tmp[i][j];
				}
			}
			memcpy(b, c, sizeof(c));
		}
		for (int i = 0; i < n; i++) {
			int sum = 0;
			for (int j = 0; j < m; j++) {
				sum += b[i][j];
			}
			ans = min(ans, sum);
		}
	} while (next_permutation(v.begin(), v.end(),cmp));
	cout << ans;
}
