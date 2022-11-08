#include <iostream>
#include <vector>
using namespace std;

int R, C, K, W;
int MAP[21][21];

struct Node {
	int y; int x; int t;
};

vector<Node> v;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> R >> C >> K;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> MAP[i][j];
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

		// 모드 온풍기에서 바람

		// 온도 조절

		// 온도 1 이상이 가장 바깥쪽 칸 온도 1씩 감소

		// 초콜릿
	}



	return 0;
}
