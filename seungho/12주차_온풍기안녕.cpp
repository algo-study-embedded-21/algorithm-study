#include <iostream>
#include <vector>
using namespace std;

int R, C, K, W;
int MAP[21][21];
int temp[21][21];

struct Node {
	int y; int x; int t;
};

vector<Node> v;
vector<Node> check;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> R >> C >> K;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 0) continue;
			if (MAP[i][j] == 5) {
				check.push_back({ i,j,5 });
			}
			else {
				v.push_back({ i,j,MAP[i][j] });
			}	
		}
	}

	cin >> W;
	for (int i = 0; i < W; i++) {
		int x, y, t;
		cin >> x >> y >> t;
		v.push_back({ x,y,t });
	}

	while (1) {
		// 조사 칸 검사
		int flag = 0;
		for (int c = 0; c < check.size(); c++) {
			int i = check[c].y;
			int j = check[c].x;
			if (temp[i][j] < K) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) break;

		// 모든 온풍기에서 바람
		for (int m = 0; m < v.size(); m++) {
			bfs(v[m].y, v[m].x, v[m].t);
		}

		// 온도 조절
		

		// 온도 1 이상이 가장 바깥쪽 칸 온도 1씩 감소
		for (int j = 0; j < C; j++) {
			if (MAP[0][j] > 0) MAP[0][j]--;
			if (MAP[R - 1][j] > 0) MAP[R - 1][j]--;
		}
		for (int i = 1; i < R - 1; i++) {
			if (MAP[i][0] > 0) MAP[i][0]--;
			if (MAP[i][C - 1] > 0) MAP[i][C - 1]--;
		}

		// 초콜릿
	}



	return 0;
}
