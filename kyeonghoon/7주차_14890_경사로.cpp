#include<iostream>
using namespace std;

int n, l;

int map[200][100];

int  search() {
	int cnt = 0;
	for (int i = 0; i < 2*n; i++) {
		bool ok = true;
		int tmp = 1;
		for (int j = 0; j < n-1; j++) {
			if (map[i][j] != map[i][j + 1]) {
				//오르막길
				if (map[i][j]+1 == map[i][j + 1] && tmp >= l) {
					tmp = 1;
					//내리막길
				}
				else if (map[i][j]==map[i][j + 1]+1 && tmp >= 0) {
					tmp = 1 - l;
				}
				//못감
				else {
					ok = false;
					break;
				}
			}
			else {
				tmp += 1;
			}
		}
		if (tmp < 0)ok = false;
		if (ok) {
			cnt += 1;
		}
	}
	return cnt;
}

void input() {
	cin >> n >> l;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			map[i + n][j] = map[j][i];
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	input();
	cout<<search();
	return 0;
}
