#include<iostream>
#include<queue>
using namespace std;

int n,kk,sum, p[11], road[11][11], score[3], ans = 1e9, group[11];

bool check() {
	for (int j = 1; j <= n; j++) {
		bool ok = false;
		for (int i = 1; i <= n; i++) {
			if (i == j)continue;
			if (group[i] == group[j] && road[j][i]) {//같은 그룹이고 연결된 곳이 있다.
				ok = true;
			}
		}
		//같은 그룹 중 하나도 연결 안 된 무언가가 있다.
		if (!ok)return true;
	}
	return false;
}

bool check2(int p) {
	for (int i = 1; i <= n; i++) {
		if (group[i] == group[p] && road[i][p])return true;
	}
	return false; //그룹같은데 연결된 곳 없음.
}

void func(int num) {
	if (num > n) {
		/*for (int i = 1; i <= n; i++) {
			cout << group[i] << " ";
		}
		cout << '\n';*/
		if (check())return;
		score[1] = 0, score[2] = 0;
		int use[11] = { 0, };
		for (int i = 1; i <= n; i++) {
			if (use[i] == 1)continue;
			use[i] = 1;
			if (check2(i)) {
				score[group[i]] += p[i];
			}
			for (int j = 1; j <= n; j++) {
				if (!road[i][j])continue;
				if (i == j)continue;
				if (group[i] == group[j] && !use[j]) {
					score[group[j]] += p[j];
					use[j] = 1;
				}
			}
		}
		//cout << score[1] << " " << score[2] << '\n';
		if (score[1] + score[2] == sum) {
			ans = min(ans, abs(score[1] - score[2]));
		}
		return;
	}
	for (int i = 1; i <= 2; i++) {
		group[num] = i;
		func(num + 1);
	}
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> p[i];
		sum += p[i];
	}
	
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		for (int j = 0; j < x; j++) {
			int y;
			cin >> y;
			road[i][y] = 1;
			road[y][i] = 1;
		}
	}
	if (n == 2) {
		cout << abs(p[1] - p[2]);
		return 0;
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		bool ok = false;
		for (int j = 1; j <= n; j++) {
			if (road[i][j])ok = true;
		}
		if (!ok) {
			kk = i;
			cnt += 1;
		}
	}
	if (cnt > 1) {//외딴 섬 두 개 이상이면
		cout << -1;
		return 0;
	}
	if (cnt == 1) {//외딴 섬 하나가 한 팀인 경우
		cout << sum - p[kk];
		return 0;
	}
	func(1);
	if (ans == 1e9) {
		cout << -1;
	}
	else {
		cout << ans;
	}
	
}
