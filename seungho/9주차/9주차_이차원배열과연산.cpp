#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;

int MAP[100][100];
int rowcnt = 2;
int colcnt = 2;

struct Node {
	int n; int c;
};

bool cmp(Node a, Node b) {
	if (a.c < b.c) return true;
	else if (a.c > b.c) return false;
	else if (a.n < b.n) return true;
	else if (a.n > b.n) return false;
	return false;
}

void calR() {
	int maxrow = 0;
	int maxcol = 0;
	for (int i = 0; i <= rowcnt; i++) {
		// 행의 숫자마다 개수 카운트
		vector<Node> v;
		int DAT[101] = { 0 };
		for (int j = 0; j < 100; j++) {
			if (MAP[i][j] == 0) continue;
			DAT[MAP[i][j]]++;
			// 카운트한 칸은 0으로 초기화
			MAP[i][j] = 0;
		}
		// 벡터에 숫자,개수 넣고 sort
		for (int j = 1; j < 101; j++) {
			if (DAT[j] == 0) continue;
			v.push_back({ j,DAT[j] });
		}
		sort(v.begin(), v.end(), cmp);

		for(int j=0;j<v.size();j++){
			if (2 * j >= 100) break;
			MAP[i][2*j] = v[j].n;
			MAP[i][2 * j + 1] = v[j].c;
			maxrow = max(maxrow, i);
			maxcol = max(maxcol, 2 * j + 1);
		}
	}
	rowcnt = maxrow;
	colcnt = maxcol;
}

void calC() {
	int maxrow = 0;
	int maxcol = 0;
	for (int j = 0; j <= colcnt; j++) {
		// 행의 숫자마다 개수 카운트
		vector<Node> v;
		int DAT[101] = { 0 };
		for (int i = 0; i < 100; i++) {
			if (MAP[i][j] == 0) continue;
			DAT[MAP[i][j]]++;
			// 카운트한 칸은 0으로 초기화
			MAP[i][j] = 0;
		}
		// 벡터에 숫자,개수 넣고 sort
		for (int i = 1; i < 101; i++) {
			if (DAT[i] == 0) continue;
			v.push_back({ i,DAT[i] });
		}
		sort(v.begin(), v.end(), cmp);

		for (int i = 0; i < v.size(); i++) {
			if (2 * i >= 100) break;
			MAP[2 * i][j] = v[i].n;
			MAP[2 * i + 1][j] = v[i].c;
			maxrow = max(maxrow, 2*i+1);
			maxcol = max(maxcol, j);
		}
	}
	rowcnt = maxrow;
	colcnt = maxcol;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	int r, c, k;
	cin >> r >> c >> k;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> MAP[i][j];
		}
	}

	// A[r][c] == k 확인
	// 행의 개수, 열의 개수 카운트
	// R/C 연산
		// 행/열 돌면서 숫자마다 개수 카운트
		// temp 벡터에 {숫자, 개수} 넣고 sort
		// 행/열에 순서대로 push_back
	// 0 채우기
	// 행/열 크기 100 넘어가면 버리기
	// 1초 ++
	int t = 0;
	while (1) {
		if (MAP[r-1][c-1] == k) break;
		if (t == 100) {
			cout << -1;
			return 0;
		}
		if (rowcnt >= colcnt) {
			calR();
		}
		else calC();
		t++;		
	}

	cout << t;
	return 0;
}
