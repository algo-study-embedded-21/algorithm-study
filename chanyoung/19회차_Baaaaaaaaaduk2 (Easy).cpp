#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct gps { int y, x; };

int n, m;
int map[20][20];
vector<gps> space; //빈칸
vector<gps> enemy; //상대돌칸
int ans = -1;
int kill;

int yy[4] = { 0,0,1,-1 };
int xx[4] = { 1,-1,0,0 };

void check()
{
    kill = 0; // 잡은 돌의 갯수
    int visit[20][20] = { 0 };
    for (int d = 0; d < enemy.size(); d++) // 모든 상대돌을 탐색
    {
        int cnt = 1; // 현재 그룹화중인 상대돌의 갯수
        int stop = 0; // 현재 그룹이 잡을수 있으면 0 없으면 1
        gps st = enemy[d];
        if (visit[st.y][st.x])continue; // 다른그룹에 속해있다면 무시
        queue<gps> q;
        q.push(st);
        visit[st.y][st.x] = 1;
        while (!q.empty())
        {
            gps now = q.front();
            q.pop();
            for (int i = 0; i < 4; i++)
            {
                gps next = { now.y + yy[i],now.x + xx[i] };
                if (next.y > n - 1 || next.y<0 || next.x>m - 1 || next.x < 0)continue;
                if (visit[next.y][next.x])continue;
                if (map[next.y][next.x] == 0)stop = 1; // 상대돌 인근에 빈칸이있다면 잡을수 없다고 표시
                if (map[next.y][next.x] == 2) // 인근 돌이 상대돌인경우 그룹화 진행
                {
                    cnt++;
                    q.push(next);
                    visit[next.y][next.x] = 1;
                }
            }
        }
        if (stop == 0)kill += cnt; // 이 그룹을 잡을수 있는경우 잡은 돌의 갯수 갱신
    }
}

void dfs(int level,int num) // 내 돌 2개 놓기
{
    if (level == 2)
    {
        check();
        ans = max(kill, ans); // 가장 많은 돌을 잡는경우 갱신
        return;
    }
    for (int i = num; i < space.size(); i++) // 중복 경우의수 제거
    {
        gps now = space[i];
        map[now.y][now.x] = 1; // 돌 놓기
        dfs(level + 1, i + 1);
        map[now.y][now.x] = 0; // 돌 빼기
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> map[i][j];
            if (map[i][j] == 0)space.push_back({ i,j });
            else if (map[i][j] == 2)enemy.push_back({ i,j });
        }
    }
    dfs(0,0);

    cout << ans;

    return 0;
}
