#include <iostream>
using namespace std;

int N, K;
struct Node {
	int r;
	int d;
};
Node arr[201];

int cnt = 0;

// 과정 1회
void turn()  {
	// 벨트 한칸 회전
	// 배열 index +=1
	arr[0] = arr[2 * N];
	for (int i = 2 * N - 1; i >= 0; i--) {
		arr[i + 1] = arr[i];
	}
	// n번 칸 로봇 하차
	arr[N].r = 0;

	// n-1 -> 1번 순서로 로봇 이동
	for (int i = N-1; i > 0; i--) {
		// 현재 칸에 로봇 없다면 패스
		if (arr[i].r == 0) continue;
		// 앞 칸에 로봇 있는지 확인
		if (arr[i + 1].r == 1) continue;
		// 앞 칸의 내구도 확인
		if (arr[i + 1].d <= 0) continue;
		
		// 조건 만족 시 로봇 이동
		arr[i + 1].r = 1;
		arr[i].r = 0;
		// 이동한 칸 내구도 -= 1;
		arr[i + 1].d -= 1;
		// 로봇 이동으로 해당 칸 내구도가 0이 되면 cnt++
		if (arr[i + 1].d == 0) cnt++;
	}
	arr[N].r = 0;

	// 올리는 위치 내구도 0 아니면 로봇 올림
	if (arr[1].d > 0) {
		arr[1].r = 1;
		// 올리면 내구도 -= 1
		arr[1].d -= 1;
		// 올려서 내구도 0 되면 cnt++
		if (arr[1].d == 0) cnt++;
	}
}


int main() {
	// 입력
	cin >> N >> K;
	for (int i = 1; i <= 2*N; i++) {
		cin >> arr[i].d;
		if (arr[i].d == 0) cnt++;
	}

	int ans = 0;

	// 과정 반복
	while (true) {
		ans++;
		turn();
		// cnt가 K 이상이면 종료
		if (cnt >= K) break;
	}

	cout << ans;
	return 0;
}
