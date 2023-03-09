#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

int n, k;
int visited[26];
string word[50];
int answer;

void input() {
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		s = s.substr(4, s.size()-8);
		word[i] = s;
	}
}

void dfs(int c, int len) {
	
	if (len == k - 5) {
		int sum = 0;
		for (int i = 0; i < n; i++) { 
			int flag = 1;
			for (int j = 0; j < word[i].size(); j++) {
				if (visited[word[i][j] - 'a'] == 0) {
					flag = 0;
					break;
				}
			}
			if (flag == 1) sum++;
		}
		answer = max(sum, answer);
	}

	for (int i = c; i < 26; i++) {
		if (visited[i] == 1) continue;
		visited[i] = 1;
		dfs(i, len+1);
		visited[i] = 0;
	}
}

void output() {
	// a, n, t, i, c를 알지 못할 때
	if (k < 5) cout << 0;
	// 모든 알파벳을 알 면 모든 단어 알 수 있음
	else if (k == 26) cout << n;
	else {
		visited['a' - 'a'] = 1;
		visited['n' - 'a'] = 1;
		visited['t' - 'a'] = 1;
		visited['i' - 'a'] = 1;
		visited['c' - 'a'] = 1;
		dfs(0, 0);
		cout << answer;
	}
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	input();
	output();

	return 0;
}