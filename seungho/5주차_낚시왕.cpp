#include <iostream>
#include <vector>
using namespace std;

struct shark {
	int r;
	int c;
	int s;
	int d;
	int z;
};

vector<shark> v;

int MAP[101][101]; // 상어의 인덱스 저장


int main() {
	// 입력
	int R, C, M;
	cin >> R >> C >> M;
	int r, c, s, d, z;
	for (int i = 0; i < M; i++) {
		cin >> r >> c >> s >> d >> z;
		v.push_back({ r,c,s,d,z });
	}

	int ans = 0;

	// 1초 동안 일어나는 일
	for (int i = 1; i <= C; i++) {
		// 낚시왕 한 칸 이동


		// 낚시왕 있는 열 상어 중 가장 가까운 상어 잡는다
		for (int j = 1; j <= R; j++) {
			if (MAP[i][j] >= 0) {
				v[MAP[i][j]].z = 0; // 잡은 상어는 크기 0으로 표시
				ans++;
				break;
			}
		}

		// 상어 이동
		for (int j = 0; j < v.size(); j++) {
			if (v[j].z == 0) continue;
			MAP[v[j].r][v[j].c] = -1;	// 현재 칸 비운다

		}
	}


	return 0;
}
