#include <iostream>
#include <vector>
#include <queue>
#include <deque>
using namespace std;

int N, M;
int MAP[1001][1001];
vector<int> v[1001];
int visited[1001];
int cnt_front[1001];

int main()
{
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int num, list[100];
		cin >> num;
		for (int j = 0; j < num; j++) {
			cin >> list[j];
		}

		for (int j = 0; j < num; j++) {
			for (int k = j + 1; k < num; k++) {
				MAP[list[j]][list[k]] = 1;
				v[list[j]].push_back(list[k]);
				cnt_front[list[k]]++;
			}
		}
	}

	queue<int> q;

	for (int i = 1; i <= N; i++) {
		if (cnt_front[i] == 0) q.push(i);
	}

	deque<int> answer;

	while (!q.empty()) {
		int now = q.front();
		visited[now] = 1;
		q.pop();
		answer.push_front(now);
		for (int i = 0; i < v[now].size(); i++) {
			cnt_front[v[now][i]]--;
			if (visited[v[now][i]]) continue;
			if (cnt_front[v[now][i]] == 0) q.push(v[now][i]);
		}
	}

	if (answer.size() != N) {
		cout << 0;
		return 0;
	}
	while (!answer.empty()) {
		cout << answer.back()<< "\n";
		answer.pop_back();
	}

	return 0;
}
