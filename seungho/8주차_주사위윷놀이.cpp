#include <iostream>
#include <vector>

using namespace std;

struct Node {
	int y;
	int x;
};

Node horse[4]; // 말 4개 각각의 위치
int moves[10]; // 주사위에서 나올 수
int finish[4]; // 도착 여부

int MAP[5][21] =
{
	{0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40},
	{0,0,0,0,0,0,0,0,0,0,0,0,10,13,16,19,25,30,35,40},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,20,22,24,25,30,35,40},
	{0,0,0,0,0,0,0,0,0,0,0,0,30,28,27,26,25,30,35,40},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,30,35,40}
};

int maxans = -1;

void dfs(int level, int ans) {
	if (level == 10) {
		maxans = max(maxans, ans);
		//cout << "level: " << level << " ans: " << ans << " maxans : " << maxans << "\n";
		return;
	}

	int m = moves[level];

	// 말의 위치 정보 저장
	Node temp[4] = { 0 };
	for (int h = 0; h < 4; h++) {
		temp[h] = { horse[h].y,horse[h].x };
	}

	// 점수 저장
	int tempans = ans;

	for (int i = 0; i < 4; i++) {
		// 이미 도착한 말이면 continue
		if (finish[i] == 1) continue;

		horse[i].x += m;	// m 칸 이동

		int nowfin = 0; // 이번 턴에 도착했는지 여부

		// 도착 칸을 지나는 경우
		if (horse[i].x > 20) {
			finish[i] = 1;
			nowfin = 1;
		}
		// 이동 후 현재 칸 숫자를 점수에 추가
		ans += MAP[horse[i].y][horse[i].x];

		// 10, 20, 30 에서 멈춘 경우 MAP의 해당 행으로 이동
		Node now = horse[i];
		if (MAP[now.y][now.x] == 10) {
			horse[i] = { 1,12 };
		}
		else if (MAP[now.y][now.x] == 20) {
			horse[i] = { 2,13 };
		}
		else if (now.y == 0 && MAP[now.y][now.x] == 30) {
			horse[i] = { 3,12 };
		}
		else if (MAP[now.y][now.x] == 40) {
			horse[i] = { 0,20 };
		}
		else if (now.y != 0 && now.x > 16 && now.x< 20) {
			horse[i].y = 1;
		}


		// 이동한 칸에 다른 말이 있는지 확인
		// 도착한 말이면 확인 x
		int flag = 0;
		if (finish[i] == 0) {
			for (int j = 0; j < 4; j++) {
				if (i == j) continue;	// 같은 말 번호면 continue

				// 도착한 칸이 다른 말의 위치와 같은 경우
				// 점수와 위치를 이전으로 되돌려 놓는다
				if (horse[i].y == horse[j].y && horse[i].x == horse[j].x) {
					flag = 1;
					ans = tempans;
					for (int t = 0; t < 4; t++) {
						horse[t] = temp[t];
					}
					break;
				}
			}
		}
		if (flag == 1) continue;
		dfs(level + 1, ans);

		// return시 이전 정보 복구
		ans = tempans;
		for (int t = 0; t < 4; t++) {
			horse[t] = temp[t];
		}
		if (nowfin == 1) finish[i] = 0;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	for (int i = 0; i < 10; i++) {
		cin >> moves[i];
	}

	dfs(0, 0);

	cout << maxans;
	return 0;
}
