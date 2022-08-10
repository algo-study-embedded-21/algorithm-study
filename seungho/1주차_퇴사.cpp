#include <iostream>
#include <vector>
using namespace std;


struct node {
	int num;
	int t;
	int p;
};
int N;

vector<node> v;

int money = 0;
int maxmon = 0;

void func(int now) {
	if (now + v[now].t > N) {
		if (now + v[now].t == N + 1) {
			money += v[now].p;
			if (money > maxmon) {
				maxmon = money;
			}
			money -= v[now].p;
		}
		if (money > maxmon) {
			maxmon = money;
		}		
		return;
	}
	for (int i = now + 1; i <= N; i++) {
		if (i - now < v[now].t) continue;
		money += v[now].p;
		func(i);
		money -= v[now].p;
	}

}



int main()
{
	cin >> N;
	v.push_back({ 0,0,0 });
	for (int i = 1; i <= N; i++) {
		int t, p;
		cin >> t >> p;
		v.push_back({ i,t,p });
	}
	func(0);
	cout << maxmon;
	return 0;

}