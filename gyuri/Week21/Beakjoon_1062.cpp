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
		s = s.substr(4, s.size());
		s = s.substr(0, s.size() - 4);
		cout << s << endl;
		word[i] = s;
	}
}

void dfs(char c, int len) {
	
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
	// a, n, t, i, c�� ���� ���� ��
	if (k < 5) cout << 0;
	// ��� ���ĺ��� �� �� ��� �ܾ� �� �� ����
	else if (k == 26) cout << n;
	else {
		visited['a' - 'a'] = 0;
		visited['n' - 'a'] = 0;
		visited['t' - 'a'] = 0;
		visited['i' - 'a'] = 0;
		visited['c' - 'a'] = 0;
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