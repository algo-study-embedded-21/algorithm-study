#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

int N, K;
vector<string> v;
string base = "antic";
int maxval = -2134567890;
bool alpha[27];
bool used[51];

void setA() {
	for (int i = 0; i < base.length(); i++) {
		alpha[base[i] - 97] = true;
	}

	for (int i = 0; i < v.size(); i++) {
		sort(v[i].begin(), v[i].end());
		v[i].erase(unique(v[i].begin(), v[i].end()), v[i].end());
	}

}

void input() {
	cin >> N >> K;

	for (int i = 0; i < N; i++) {
		string s;
		cin >> s;

		v.push_back(s.substr(4,s.length()-8));
	}
}

void check(int lvl, int cnt) {
	if (cnt == K - 5) {
		return;
	}

	for (int i = lvl; i < 26; i++) {
		if (alpha[i]) continue;

		alpha[i] = true;
		check(i, cnt + 1);
		alpha[i] = false;
	}

}

int main() {
	input();
	if (K < 5) {
		cout << 0;
		return 0;
	}
	setA();
	check();
	cout << maxval;
}
