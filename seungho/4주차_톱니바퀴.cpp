#include <iostream>
using namespace std;

string MAP[5];
// 처음 각 톱니바퀴의 12시방향 index
int pointer[5] = {0};


void rotate(int num, int dir, int from) {	// from: 왼쪽-> -1, 오른쪽 -> 1

	// 현재 톱니의 왼쪽, 오른쪽 극
	int leftindex = (pointer[num] + 6) % 8;

	int rightindex = (pointer[num] + 2) % 8;


	char left = MAP[num][leftindex];
	char right = MAP[num][rightindex];

	// 현재 톱니 회전
	pointer[num] = pointer[num]-dir + 8;
	pointer[num] %= 8;

	// 1,2,3번은 오른쪽 확인
	if (num == 1 || num == 2 || num == 3) {
		// 오른쪽에서 출발했으면 다시 돌아가지 않는다
		if (from != 1) {

			// 왼쪽 톱니의 오른쪽과, 오른쪽 톱니의 왼쪽이 다르다면
			if (right != MAP[num + 1][(pointer[num+1] + 6) % 8]) {
				rotate(num + 1, -1 * dir, -1);
			}
		}
		
	}

	// 2,3,4번은 왼쪽 확인
	if (num == 2 || num == 3 || num == 4) {
		// 왼쪽에서 출발했으면 다시 돌아가지 않는다
		if (from != -1) {

			// 오른쪽 톱니의 왼쪽과, 왼쪽 톱니의 오른쪽이 다르다면
			if (left != MAP[num - 1][(pointer[num-1] + 2) % 8]) {
				rotate(num - 1, -1 * dir, 1);
			}
		}		
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	for (int i = 1; i <= 4; i++) {
		cin >> MAP[i];
	}
	int K;
	cin >> K;
	
	for (int i = 0; i < K; i++) {
		int num, dir;
		cin >> num >> dir;
		rotate(num, dir, 0);
	}
	int score = 0;
	if (MAP[1][pointer[1]] == '1') score += 1;
	if (MAP[2][pointer[2]] == '1') score += 2;
	if (MAP[3][pointer[3]] == '1') score += 4;
	if (MAP[4][pointer[4]] == '1') score += 8;

	cout << score;
	return 0;
}
