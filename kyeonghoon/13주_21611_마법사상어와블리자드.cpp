#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };
int ddx[] = { 0,1,0,-1 };
int ddy[] = { -1,0,1,0 };
int n, m;
int map[100][100];
vector<int> num;
int score;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}
	while (m--) {
		num.clear();
		int dir, s;
		cin >> dir >> s;
		dir--;
		int s_x = n / 2, s_y = n / 2;
		//제거
		for (int i = 1; i <= s; i++) {
			int nx = s_x + dx[dir] * i;
			int ny = s_y + dy[dir] * i;
			map[nx][ny] = 0;
		}
		//달팽이배열에 넣기
		int s_dir = 0;
		int cnt = 1;
		while (1) {
			bool ok = false;
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < cnt; j++) {
					s_x += ddx[s_dir];
					s_y += ddy[s_dir];
					if (map[s_x][s_y] != 0) {
						num.push_back(map[s_x][s_y]);
					}
					if (s_x == 0 && s_y == 0) {
						ok = true;
						break;
					}
				}
				s_dir = (s_dir + 1) % 4;
				if (ok)break;
			}
			cnt += 1;
			if (ok)break;
		}
		if (num.size() == 0)break;
		//explode
		vector<int> n_num;
		while (1) {
			bool ok = false;
			int cnt = 1;
			int val = num[0];
			int si = 0;
			for (int i = 1; i < num.size(); i++) {
				if (val == num[i]) {
					cnt += 1;
				}
				else if (val != num[i]) {
					if (cnt >= 4) {
						for (int k = si; k < i; k++) {
							ok = true;
							score += val;
						}
					}
					else {
						for (int k = si; k < i; k++) {
							n_num.push_back(num[k]);
						}
					}
					cnt = 1;
					val = num[i];
					si = i;
				}
			}
			if (cnt >= 4) {
				for (int k = si; k < si + cnt; k++) {
					ok = true;
					score += val;
				}
			}
			else {
				for (int k = si; k < si + cnt; k++) {
					n_num.push_back(num[k]);
				}
			}
			num = n_num;
			n_num.clear();
			if (!ok)break;
		}
		if (num.size() == 0)break;
		//change
		cnt = 1;
		int val = num[0];
		for (int i = 1; i < num.size(); i++) {
			if (num[i] == val) {
				cnt += 1;
			}
			else if (num[i] != val) {
				n_num.push_back(cnt);
				n_num.push_back(val);
				val = num[i];
				cnt = 1;
			}
		}
		n_num.push_back(cnt);
		n_num.push_back(val);
		num = n_num;
		//달팽이배열에담기
		s_x = n / 2, s_y = n / 2;
		s_dir = 0;
		cnt = 1;
		int ss = 0;
		memset(map, 0, sizeof(map));
		while (1) {
			bool ok = false;
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < cnt; j++) {
					s_x += ddx[s_dir];
					s_y += ddy[s_dir];
					map[s_x][s_y] = num[ss++];
					if (ss == num.size()) {
						ok = true;
						break;
					}
					if (s_x == 0 && s_y == 0) {
						ok = true;
						break;
					}
				}
				s_dir = (s_dir + 1) % 4;
				if (ok)break;
			}
			cnt += 1;
			if (ok)break;
		}
		
	}
	cout << score;
}
