/*

1. 그냥 구현 문제인 것 같다 -> 입력 사이즈 확인 -> 맞는 듯
2. 시간 or 회전 기준으로 반복문을 돌리면 될 것 같다
	-> 회전 기준으로 세면 뱀 몸통 처리나 마지막 회전 이후 시간 처리가 어려울 것 같다
	-> 시간 기준으로 반복문을 돌리자
3. 시간을 증가시키면서 뱀을 한 칸씩 이동시키는 시뮬레이션을 돌린다
	-> 다음 진행 방향에 벽 or 몸통 있으면 끝
	-> 사과 있는지 확인
		-> 없으면 꼬리 부분을 한 칸 삭제
	-> 방향 변환을 dat로 저장해 해당 시간에 변환을 하는지 안하는지 쉽게 확인
	-> 방향 배열을 이용, 추후에 꼬리 부분 삭제 이후 꼬리 인덱스도 이동시키기 위해 방향 배열 정보를 map에 저장해둠
	-> 시간 증가

*/

#include <iostream>
using namespace std;

int n, k, l;
int map[101][101];
char command[10001];

// 오른쪽 회전 : 방향 값 ++
// 왼쪽 회전 : 방향 값 --
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> k;
	for (int i = 0; i < k; i++) {
		int x, y;
		cin >> x >> y;
		// 사과
		map[x - 1][y - 1] = 1;
	}

	cin >> l;
	for (int i = 0; i < l; i++) {
		int x;
		char c;
		cin >> x >> c;
		command[x] = c;
	}

	// 뱀
	map[0][0] = -1;
	// 초기 위치 및 방향
	int sx = 0, sy = 0, ex = 0, ey = 0, dir = 0;

	int time = 1;
	while (1) {
		int nx = sx + dx[dir];
		int ny = sy + dy[dir];
		// 벽인 경우 끝
		if (nx < 0 || nx >= n || ny < 0 || ny >= n) break;
		// 몸통과 부딪혀도 끝
		if (map[nx][ny] < 0) break;

		sx = nx;
		sy = ny;
		// 사과가 없으면
		if (map[nx][ny] == 0) {
			// 지나간 루트를 따라 꼬리 한 칸 삭제
			int nex = ex + dx[map[ex][ey] * -1 - 1];
			int ney = ey + dy[map[ex][ey] * -1 - 1];

			map[ex][ey] = 0;
			ex = nex;
			ey = ney;
		}

		// 방향 변환
		if (command[time] == 'D') dir = (dir + 1) % 4;
		// + 4 잊고 안해서 틀림 ㅠ 
		// %로 배열 돌릴 땐 범위 체크 조심하기
		if (command[time] == 'L') dir = (dir + 4 - 1) % 4;

		// 꼬리도 같은 루트로 방향 변환 할 수 있게 기록 && 몸통이 있다는 표시
		map[nx][ny] = (dir + 1) * -1;

		time++;
	}

	cout << time;

	return 0;
}