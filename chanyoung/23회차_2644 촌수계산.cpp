#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

int n, m;
int one, two;
vector<int> node[101];
int visit[101];

int bfs()
{
    queue<int> q;
    q.push(one);
    visit[one] = 1;
    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        if (now == two) return visit[two] - 1;
        for (int i = 0; i < node[now].size(); i++)
        {
            int next = node[now][i];
            if (visit[next])continue;
            visit[next] = visit[now] + 1;
            q.push(next);
        }
    }
    return -1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> n >> one >> two >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        node[a].push_back(b);
        node[b].push_back(a);
    }
    cout << bfs();

    return 0;
}
