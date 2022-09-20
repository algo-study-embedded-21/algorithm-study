#include<iostream>
using namespace std;

int n,blue[6][4], green[6][4], score;

int blocks(int xx[][4]) {
	int sum = 0;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			if (xx[i][j] == 1)sum += 1;
		}
	}
	return sum;
}

void block(int y, int type, int xx[][4]) {
	int cur;//블록이 최대한 내려갈 수 있는 줄
	if (type != 2) {
		for (int i = 1; i < 6; i++) {
			cur = i;
			if (xx[i][y] == 1) {
				cur -= 1;
				break;
			}
		}
	}
	else {
		for (int i = 1; i < 6; i++) {
			cur = i;
			if (xx[i][y] == 1 || xx[i][y + 1] == 1) {
				cur -= 1;
				break;
			}
		}
	}
	xx[cur][y] = 1;
	if (type == 2)xx[cur][y + 1] = 1;
	if (type == 3)xx[cur - 1][y] = 1;
	/*cout << "green\n";
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			cout << green[i][j];
		}
		cout << '\n';
	}
	cout << "blue\n";
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			cout << blue[i][j];
		}
		cout << '\n';
	}*/
	//완성줄 탐색 터질 때 최대 두 줄 그리고 공간을 두고 터질확률 x
	int start = -1; //터지기 시작한 가장 밑줄
	int val = 0;//몇 줄이 터졌나?
	for (int i = 5; i >= 0; i--) {
		bool ok = true;
		for (int j = 0; j < 4; j++) {
			if (xx[i][j] == 0) {
				ok = false; break;
			}
		}
		if (ok) {
			for (int j = 0; j < 4; j++) {
				xx[i][j] = 0;
				if (start == -1) {
					start = i;
				}
			}
			val++;
		}
	}
	/*cout << "한줄터진후\n";
	cout << "green\n";
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			cout << green[i][j];
		}
		cout << '\n';
	}
	cout << "blue\n";
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			cout << blue[i][j];
		}
		cout << '\n';
	}*/
	//중력
	if (start != -1) {
		score += val;
		for (int i = start; i >= 2; i--) {
			for (int j = 0; j < 4; j++) {
				xx[i][j] = xx[i - val][j];
				xx[i - val][j] = 0;
			}
		}
	}
	/*cout << "중력후\n";
	cout << "green\n";
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			cout << green[i][j];
		}
		cout << '\n';
	}
	cout << "blue\n";
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			cout << blue[i][j];
		}
		cout << '\n';
	}*/
	//연한부분에 대한 처리
	int cnt = 0;
	for (int i = 0; i < 2; i++) {
		bool ok = false;
		for (int j = 0; j < 4; j++) {
			if (xx[i][j] == 1) {
				ok = true;
				break;
			}
		}
		if (ok)cnt += 1;
	}
	cout << cnt << '\n';
	if (cnt) {
		for (int i = 5; i >= 2; i--) {
			for (int j = 0; j < 4; j++) {
				xx[i][j] = xx[i - cnt][j];
				xx[i - cnt][j] = 0;
			}
		}
	}
	/*cout << "연한후\n";
	cout << "green\n";
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			cout << green[i][j];
		}
		cout << '\n';
	}
	cout << "blue\n";
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			cout << blue[i][j];
		}
		cout << '\n';
	}*/
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	int cnt = 1;
	while(n--) {
		cout << "--------" << cnt++ << '\n';
		int t, x, y;
		cin >> t >> x >> y;
		if (t == 1) {
			block(y, 1, green);
			block(3-x, 1, blue);
		}
		else if (t == 2) {
			block(y, 2, green);
			block(3-x, 3, blue);
		}
		else if (t == 3) {
			block(y, 3, green);
			block(3-x, 2, blue);
		}
	/*	cout << "green\n";
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 4; j++) {
				cout << green[i][j];
			}
			cout << '\n';
		}
		cout << "blue\n";
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 4; j++) {
				cout << blue[i][j];
			}
			cout << '\n';
		}*/
	}
	cout << score<<'\n';
	cout << blocks(blue) + blocks(green);
}
