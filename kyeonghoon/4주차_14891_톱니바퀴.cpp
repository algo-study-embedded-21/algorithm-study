#include<iostream>
using namespace std;

string s[4];
int a[4][8];

void move(int num, int dir) {
	if (dir == 0)return;
	if (dir == 1) {
		int tmp = a[num][7];
		for (int i = 7; i >= 1; i--) {
			a[num][i] = a[num][i - 1];
		}
		a[num][0] = tmp;
	}
	else if (dir == -1) {
		int tmp = a[num][0];
		for (int i = 0; i < 7; i++) {
			a[num][i] = a[num][i + 1];
		}
		a[num][7] = tmp;
	}
}

int main() {
	for (int i = 0; i < 4; i++) {
		cin >> s[i];
		for (int j = 0; j < 8; j++) {
			a[i][j] = s[i][j] - '0';
		}
	}
	int n;
	cin >> n;
	while (n--) {
		//이번 턴에 돌아가는 바퀴
		int turn[4] = {0};
		int num, dir;
		cin >> num >> dir;
		num--;
		turn[num] = dir;
		//왼
		int tmp = dir;
		for (int i = num; i >= 1; i--) {
			if (a[i][6] != a[i - 1][2]) {
				tmp *= -1;
				turn[i - 1] = tmp;
			}
			else {
				break;
			}
		}
		//오
		tmp = dir;
		for (int i = num; i < 3; i++) {
			if (a[i][2] != a[i + 1][6]) {
				tmp *= -1;
				turn[i + 1] = tmp;
			}
			else {
				break;
			}
		}
		for (int i = 0; i < 4; i++) {
			move(i, turn[i]);
		}
	}
	int ans = 0;
	for (int i = 0; i < 4; i++) {
		if (a[i][0] == 1) {
			ans += (1 << i);
		}
	}
	cout << ans;
}
