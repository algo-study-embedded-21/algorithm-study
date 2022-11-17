#include <iostream>
#include <cmath>
using namespace std;

int N, R;
int MAP[300][300];
int MAP2[300][300];
int msize;
int bsize;

void one() {
	for (int i = 0; i < msize / bsize; i++) {
		for (int j = 0; j < msize / bsize; j++) {
			for (int bi = 0; bi < bsize; bi++) {
				for (int bj = 0; bj < bsize; bj++) {
					MAP[i * bsize + bi][j * bsize + bj] = MAP2[i * bsize + (bsize - 1 - bi)][j * bsize + bj];
				}
			}
		}
	}
}

void two() {
	for (int i = 0; i < msize / bsize; i++) {
		for (int j = 0; j < msize / bsize; j++) {
			for (int bi = 0; bi < bsize; bi++) {
				for (int bj = 0; bj < bsize; bj++) {
					MAP[i * bsize + bi][j * bsize + bj] = MAP2[i * bsize + bi][j * bsize + (bsize - 1 - bj)];
				}
			}
		}
	}
}
void three() {
	for (int i = 0; i < msize / bsize; i++) {
		for (int j = 0; j < msize / bsize; j++) {
			for (int bi = 0; bi < bsize; bi++) {
				for (int bj = 0; bj < bsize; bj++) {
					MAP[i * bsize + bj][j * bsize + (bsize - 1 - bi)] = MAP2[i * bsize + bi][j * bsize + bj];
				}
			}
		}
	}
}
void four() {
	for (int i = 0; i < msize / bsize; i++) {
		for (int j = 0; j < msize / bsize; j++) {
			for (int bi = 0; bi < bsize; bi++) {
				for (int bj = 0; bj < bsize; bj++) {
					MAP[i * bsize + (bsize - 1 - bj)][j * bsize + bi] = MAP2[i * bsize + bi][j * bsize + bj];
				}
			}
		}
	}
}

void five() {
	for (int i = 0; i < msize / bsize; i++) {
		for (int j = 0; j < msize / bsize; j++) {
			for (int bi = 0; bi < bsize; bi++) {
				for (int bj = 0; bj < bsize; bj++) {
					MAP[bsize * (msize / bsize - 1 - i) + bi][j * bsize + bj] = MAP2[i * bsize + bi][j * bsize + bj];
				}
			}
		}
	}
}
void six() {
	for (int i = 0; i < msize / bsize; i++) {
		for (int j = 0; j < msize / bsize; j++) {
			for (int bi = 0; bi < bsize; bi++) {
				for (int bj = 0; bj < bsize; bj++) {
					MAP[i * bsize + bi][bsize * (msize / bsize - 1 - j) + bj] = MAP2[i * bsize + bi][j * bsize + bj];
				}
			}
		}
	}
}
void seven() {
	for (int i = 0; i < msize / bsize; i++) {
		for (int j = 0; j < msize / bsize; j++) {
			for (int bi = 0; bi < bsize; bi++) {
				for (int bj = 0; bj < bsize; bj++) {
					MAP[j * bsize + bi][(msize / bsize - 1 - i) * bsize + bj] = MAP2[i * bsize + bi][j * bsize + bj];
				}
			}
		}
	}
}
void eight() {
	for (int i = 0; i < msize / bsize; i++) {
		for (int j = 0; j < msize / bsize; j++) {
			for (int bi = 0; bi < bsize; bi++) {
				for (int bj = 0; bj < bsize; bj++) {
					MAP[(msize / bsize - 1 - j) * bsize + bi][i * bsize + bj] = MAP2[i * bsize + bi][j * bsize + bj];
				}
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> N >> R;

	msize = pow(2, N);

	for (int i = 0; i < msize; i++) {
		for (int j = 0; j < msize; j++) {
			cin >> MAP[i][j];
		}
	}

	for (int r = 0; r < R; r++) {
		int k, l;
		cin >> k >> l;
		bsize = pow(2, l);

		// MAP 복사
		for (int i = 0; i < msize; i++) {
			for (int j = 0; j < msize; j++) {
				MAP2[i][j] = MAP[i][j];
			}
		}

		switch (k) {
		case(1):
			one();
			break;
		case(2):
			two();
			break;
		case(3):
			three();
			break;
		case(4):
			four();
			break;
		case(5):
			five();
			break;
		case(6):
			six();
			break;
		case(7):
			seven();
			break;
		case(8):
			eight();
			break;
		}
	}

	for (int i = 0; i < msize; i++) {
		for (int j = 0; j < msize; j++) {
			cout << MAP[i][j] << " ";
		}
		cout << "\n";
	}

	return 0;
}
