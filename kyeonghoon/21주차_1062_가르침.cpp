#include<iostream>
using namespace std;

int n, k, alpha[26],ans;
string s[50];

int search_cnt() {
	int ret = 0;
	for (int i = 0; i < n; i++) {
		bool flag = false;
		for (int j = 0; j < s[i].size(); j++) {
			if (!alpha[s[i][j] - 'a'])flag = true;
		}
		if (!flag)ret += 1;
	}
	return ret;
}

void dfs(int cnt,int index) {
	if (cnt == k) {
		int ret = search_cnt();
		ans = max(ret, ans);
		return;
	}
	for (int i = index; i < 26; i++) {
		if (i == 0 || i == 2 || i == 8 || i == 13 || i == 19)continue;
		if (alpha[i])continue;
		alpha[i] = 1;
		dfs(cnt + 1,i);
		alpha[i] = 0;
	}
}

int main() {
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> s[i];
	}
	if (k < 5) {
		cout << 0;
		return 0;
	}
	alpha[0] = 1; alpha[2] = 1; alpha[8] = 1; alpha[13] = 1; alpha[19] = 1;
	dfs(5, 0);
	cout << ans;
}
