#include <iostream>
#include <vector>
using namespace std;

int n, m;
int a, b;
int parent, child;
int answer;
int visited[101];
int num;
vector<int> graph[101];

void input() {
	cin >> n >> a >> b >> m;

	for (int i = 0; i < m; i++) {
		cin >> parent >> child;
		graph[parent].push_back(child);
		graph[child].push_back(parent);
	}
}

void dfs(int now) {
	
	if (now == b) {
		answer = num;
		return;
	}

	for (int i = 0; i < graph[now].size(); i++) {
		if (visited[graph[now][i]] == 1) continue;
		num++;
		visited[graph[now][i]] = 1;
		dfs(graph[now][i]);
		num--;
		visited[graph[now][i]] = 0;
	}
}

void output() {
	if (answer == 0) cout << -1;
	else cout << answer; 
}

int main() {
	input(); 
	dfs(a);
	output();
}