#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct gps { int y, x; };

int r, c;
char map[250][250];
int visit[250][250];
int wcnt, scnt; // 살아남은 늑대수, 양의 수

int yy[4] = { 0,0,-1,1 };
int xx[4] = { 1,-1,0,0 };

void bfs(gps st)
{
    queue<gps> q;
    q.push(st);
    visit[st.y][st.x] = 1;
    int wwcnt = 0, sscnt = 0; // 이 그룹내의 늑대수,양의수
    if (map[st.y][st.x] == 'v') wwcnt++; // 늑대라면 그룹 늑대수 갱신
    if (map[st.y][st.x] == 'o')sscnt++; // 양이라면 그룹 양의 수 갱신
    while (!q.empty())
    {
        gps now = q.front();
        q.pop();
        for (int d = 0; d < 4; d++)
        {
            gps next = { now.y + yy[d],now.x + xx[d] };
            if (next.y<0 || next.y>r - 1 || next.x<0 || next.x>c - 1)continue;
            if (visit[next.y][next.x])continue;
            if (map[next.y][next.x] == '#')continue; // 울타리면 무시
            if (map[next.y][next.x] == 'v') wwcnt++; // 그룹내 늑대수 갱신
            if (map[next.y][next.x] == 'o')sscnt++; // 그룹내 양의수 갱신
            visit[next.y][next.x] = 1;
            q.push(next);
        }
    }
    if (wwcnt >= sscnt)wcnt += wwcnt; // 늑대수 양의수와 같거나 더 크면 늑대가 살고
    else scnt += sscnt; // 양이 늑대보다 많다면 양만 산다
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> r >> c;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> map[i][j];
        }
    }
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (visit[i][j] || map[i][j] == '#' || map[i][j] == '.')continue; // 조사하지않은 양 또는 늑대위치에서 조사
            bfs({ i,j });
        }
    }
    cout << scnt << " " << wcnt;

    return 0;
}
