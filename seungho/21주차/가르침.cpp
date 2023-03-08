#include <iostream>
using namespace std;

int N, K;
int alphabets[50][26];
int teach[26];
int base[5] = { 0,2,8,13,19 };

int ans = 0;

void dfs(int level, int index) {
	if (level == K-5) {
		int cnt = 0;
		for (int i = 0; i < N; i++) {
			bool ok = true;
			for (int j = 0; j < 26; j++) {
				if (alphabets[i][j] == 1 && teach[j] == 0) {
					ok = false;
					break;
				}
			}
			if (ok) cnt++;
		}
		ans = max(ans, cnt);
		return;
	}
	for (int i = index; i < 26; i++) {
		bool is_base = false;
		for (int b = 0; b < 5; b++) {
			if (i == base[b]) {
				is_base = true;
				break;
			}
		}
		if (is_base) continue;

		teach[i] = 1;
		dfs(level + 1, i + 1);
		teach[i] = 0;
	}
}

int main()
{
	cin >> N >> K;
	
	// K가 기본 문자 5개보다 적은 경우
	if (K < 5) {
		cout << 0;
		return 0;
	}

	for (int i = 0; i < N; i++) {
		string word;
		cin >> word;
		for (int j = 4; j < word.length() - 4; j++) {
			alphabets[i][word[j] - 'a'] = 1;	// 사용된 알파벳 체크
		}
		for (int b = 0; b < 5; b++) {
			alphabets[i][base[b]] = 1;
		}
	}

	for (int b = 0; b < 5; b++) {
		teach[base[b]] = 1;
	}

	dfs(0, 0);

	cout << ans;

	return 0;
}
