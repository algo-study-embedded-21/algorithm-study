/*

가능한 모양을 모두 마스크로 만든 후 계산

*/
#include <iostream>
using namespace std;

int n, m;

int blockSize[19][2] = {
	{2, 2},
	{1, 4},
	{4, 1},
	{3, 2},
	{2, 3},
	{2, 3},
	{3, 2},
	{2, 3},
	{3, 2},
	{3, 2},
	{2, 3},
	{3, 2},
	{2, 3},
	{3, 2},
	{3, 2},
	{3, 2},
	{2, 3},
	{2, 3},
	{2, 3}
};

int block[19][4][4] = {
	{
		{1, 1}, {1, 1}
},
	{
		{1, 1, 1, 1}
},
	{
		{1}, {1}, {1}, {1}
},
	{
		{1, 0}, {1, 1}, {0, 1}
},
	{
		{0, 1, 1}, {1, 1, 0}
},
	{
		{1, 1, 1}, {0, 1, 0}
},
	{
		{0, 1}, {1, 1}, {0, 1}
},
	{
		{0, 1, 0}, {1, 1, 1}
},
	{
		{1, 0}, {1, 1}, {1, 0}
},
	{
		{1, 0}, {1, 0} ,{1, 1}
},
	{
		{1, 1, 1}, {1, 0, 0}
},
	{
		{1, 1}, {0, 1}, {0, 1}
},
	{
		{0, 0, 1}, {1, 1, 1}
},
	{
		{0, 1}, {0, 1}, {1, 1}
},
	{
		{1, 1}, {1, 0}, {1, 0}
},
	{
		{0, 1}, {1, 1}, {1, 0}
}, 
	{
		{1, 1, 0}, {0, 1, 1}
},
	{
		{1, 1, 1}, {0, 0, 1}
},
	{
		{1, 0, 0}, {1, 1, 1}
}
};

int map[501][501];
int maxval;

void getValue(int x, int y) {
	for (int i = 0; i < 19; i++) {
		int val = 0;
		for (int j = 0; j < blockSize[i][0]; j++) {
			for (int k = 0; k < blockSize[i][1]; k++) {
				if (x + j >= n || y + k >= m) {
					val = -1;
					break;
				}
				if (block[i][j][k]) val += map[x + j][y + k];
			}
		}
		maxval = max(maxval, val);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			getValue(i, j);
		}
	}

	cout << maxval;

	return 0;
}