/*

1. 모든 칸에 대해 좋아하는 학생, 빈 칸 조사 후 정렬
2. 1순위 자리에 배치
3. 만족도 조사

*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
int info[444][4];
int map[21][21];
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };

struct seat {
	int r;
	int c;
	int like;
	int empty;
};
bool cmp(seat a, seat b) {
	if (a.like > b.like) return true;
	if (a.like < b.like) return false;
	if (a.empty > b.empty) return true;
	if (a.empty < b.empty) return false;
	if (a.r < b.r) return true;
	if (a.r > b.r) return false;
	return a.c < b.c;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n * n; i++) {
		int index;
		cin >> index;
		for (int j = 0; j < 4; j++) {
			cin >> info[index][j];
		}
		
		vector<seat> s;
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				if (map[j][k]) continue;
				int likeCnt = 0;
				int emptyCnt = 0;
				for (int w = 0; w < 4; w++) {
					int nx = j + dx[w];
					int ny = k + dy[w];

					if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
					if (map[nx][ny] == 0) {
						emptyCnt++;
						continue;
					}
					for (int x = 0; x < 4; x++) {
						if (map[nx][ny] == info[index][x]) {
							likeCnt++;
							break;
						}
					}
				}
				s.push_back({ j, k, likeCnt, emptyCnt });
			}
		}
		sort(s.begin(), s.end(), cmp);
		map[s[0].r][s[0].c] = index;
	}


	int val = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {		
			int cnt = 0;
			for (int k = 0; k < 4; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];

				if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
				for (int x = 0; x < 4; x++) {
					if (map[nx][ny] == info[map[i][j]][x]) {
						cnt++;
						break;
					}
				}
			}

			switch (cnt) {
				case 1:
					val += 1;
					break;
				case 2:
					val += 10;
					break;
				case 3:
					val += 100;
					break;
				case 4:
					val += 1000;
					break;
				default:
					val += 0;
			}
		}
	}

	cout << val;

	return 0;
}