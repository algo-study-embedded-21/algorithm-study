#include <iostream>
#include <vector>
using namespace std;

int N;
int arr[21][21];
vector<int> start;
vector<int> link;

int visited[21] = { 0, };
int startsum = 0;
int mindif = 2134567890;

void dfs(int level) {
	// start 팀 인원을 모두 뽑았을 경우 리턴
	if (level == N/2) {
		int linksum = 0;
		for (int i = 0; i < N; i++) {
			if (visited[i] == 1) continue;
			for (int j = 0; j < N; j++) {
				if (visited[j] == 1) continue;
				linksum += arr[i][j];
			}
		}
		if (abs(startsum - linksum) < mindif) {
			mindif = abs(startsum - linksum);
		}
		return;
	}

	for (int i = 0; i < N; i++) {
		if (visited[i] == 1) continue;
		start.push_back(i);
		visited[i] = 1;
		int nowstat = 0; // 현재 팀원이 start 팀에 들어가면 더해지는 능력치

		// start 팀원들과 현재 팀원이 같은 팀일때 능력치 추가
		for (int j = 0; j < start.size(); j++) {
			nowstat += arr[i][start[j]];
			nowstat += arr[start[j]][i];
		}
		startsum += nowstat;
		dfs(level + 1);
		start.pop_back();
		visited[i] = 0;
		startsum -= nowstat;
	}
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> N;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			cin >> arr[j][i];
		}
	}

	dfs(0);
	cout << mindif;

}
