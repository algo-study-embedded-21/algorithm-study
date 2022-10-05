#include <iostream>
using namespace std;

int N, Q;
int MAP[100][100];

void turn(int L) {
	int bsize = pow(2, L);
	int msize = pow(2, N);

	// 맵 복사
	int MAP2[100][100] = { 0 };
	for (int i = 0; i < msize; i++) {
		for (int j = 0; j < msize; j++) {
			MAP2[i][j] = MAP[i][j];
		}
	}

	// 구역 별 회전
	for (int by = 0; by < msize/bsize; by++) {
		for (int bx = 0; bx < msize/bsize; bx++) {
			for (int i = 0; i < bsize; i++) {
				for (int j = 0; j < bsize; j++) {
					MAP[j+bx*bsize][bsize - i+by*bsize] = MAP2[i+by*bsize][j+bx*bsize];
				}
			}
		}
	}
}

int main() {
	cin >> N >> Q;
	for (int i = 0; i < pow(2, N); i++) {
		for (int j = 0; j < pow(2, N); j++) {
			cin >> MAP[i][j];
		}
	}

	for (int i = 0; i < Q; i++) {
		int L;
		cin >> L;

		turn(L);
	}


	return 0;
}
