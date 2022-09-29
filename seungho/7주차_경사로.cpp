#include <iostream>
using namespace std;

int MAP[100][100] = { 0 };
int MAP2[100][100] = { 0 };
int MAP3[100][100] = { 0 };

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	int N, L;
	cin >> N >> L;

	int ans = 0;
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
		}
	}
	
	// 가로로 길 만들기
	for (int i = 0; i < N; i++) {
		int flag = 1;
		for (int j = 0; j < N-1; j++) {
			// 다음 칸이 두 칸 이상 차이나는 경우 break
			if (abs(MAP[i][j] - MAP[i][j + 1]) > 1) {
				flag = 0;
				break;
			}

			// 다음 칸이 더 높은 경우
			if (MAP[i][j] < MAP[i][j + 1]) {
				// 경사로 길이만큼 뒤로 놓았을때 맵을 벗어나면 break
				if (j - (L - 1) < 0) {
					flag = 0;
					break;
				}
				for (int a = j - (L - 1); a <= j; a++) {
					// 경사로 놓을 칸의 높이가 다르면 break
					if (MAP[i][a] != MAP[i][j]) {
						flag = 0;
						break;
					}
					// 이미 경사로를 놓은 칸이면 break
					if (MAP2[i][a] > 0) {
						flag = 0; break;
					}
				}
				// 경사로를 놓을 수 있으면 MAP2에 표시
				for (int a = j - (L - 1); a <= j; a++) {
					MAP2[i][a] = 1;
				}
			}

			// 다음 칸이 더 낮은 경우
			else if (MAP[i][j] > MAP[i][j+1]) {
				// 경사로 길이만큼 앞으로 놓았을때 맵을 벗어나면 break
				if (j + L >= N) {
					flag = 0;
					break;
				}
				for (int a = j+1; a <= j+L; a++) {
					// 경사로 놓을 칸의 높이가 다르면 break
					if (MAP[i][a] != MAP[i][j+1]) {
						flag = 0;
						break;
					}
					// 이미 경사로를 놓은 칸이면 break
					if (MAP2[i][a] > 0) {
						flag = 0; 
						break;
					}
				}
				// 경사로를 놓을 수 있으면 MAP2에 표시
				for (int a = j + 1; a <= j + L; a++) {
					MAP2[i][a] = 1;
				}
			}
		}
		// 길이 만들어지면 ans++
		if (flag == 1) {
			ans++;
		}
	}

	// 세로로 길 만들기
	for (int j = 0; j < N; j++) {
		int flag = 1;
		for (int i = 0; i < N - 1; i++) {
			// 다음 칸이 두 칸 이상 차이나는 경우 break
			if (abs(MAP[i][j] - MAP[i+1][j]) > 1) {
				flag = 0;
				break;
			}

			// 다음 칸이 더 높은 경우
			if (MAP[i][j] < MAP[i+1][j]) {
				// 경사로 길이만큼 뒤로 놓았을때 맵을 벗어나면 break
				if (i - (L - 1) < 0) {
					flag = 0;
					break;
				}
				for (int a = i - (L - 1); a <= i; a++) {
					// 경사로 놓을 칸의 높이가 다르면 break
					if (MAP[a][j] != MAP[i][j]) {
						flag = 0;
						break;
					}
					// 이미 경사로를 놓은 칸이면 break
					if (MAP3[a][j] > 0) {
						flag = 0; 
						break;
					}
				}
				// 경사로를 놓을 수 있으면 MAP2에 표시
				for (int a = i - (L - 1); a <= i; a++) {
					MAP3[a][j] = 1;
				}
			}

			// 다음 칸이 더 낮은 경우
			else if (MAP[i][j] > MAP[i+1][j]) {
				// 경사로 길이만큼 앞으로 놓았을때 맵을 벗어나면 break
				if (i + L >= N) {
					flag = 0;
					break;
				}
				for (int a = i + 1; a <= i + L; a++) {
					// 경사로 놓을 칸의 높이가 다르면 break
					if (MAP[a][j] != MAP[i+1][j]) {
						flag = 0;
						break;
					}
					// 이미 경사로를 놓은 칸이면 break
					if (MAP3[a][j] > 0) {
						flag = 0; 
						break;
					}
				}
				// 경사로를 놓을 수 있으면 MAP2에 표시
				for (int a = i + 1; a <= i + L; a++) {
					MAP3[a][j] = 1;
				}
			}
		}

		// 길이 만들어지면 ans++
		if (flag == 1) {
			ans++;
		}
	}

	cout << ans;

	return 0;
}
