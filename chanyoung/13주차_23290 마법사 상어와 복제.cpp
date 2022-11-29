#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <string.h>
using namespace std;

struct gps { int y, x; };

vector<int> map[4][4]; 
vector<int> cmap[4][4]; // 마법 복제 맵
vector<int> mvmap[4][4]; // 물고기 이동 맵
vector<gps> shpath; // 상어가 움직인 경로
vector<gps> path; // dfs 경로
int smell[4][4]; // 냄새맵
int visit[4][4]; // dfs visit
int outfish; // 격자에서 제외되는 물고기 양
int m, s;
gps sh; // 상어의 위치

int yy[8] = { 0,-1,-1,-1,0,1,1,1 }; // 상:2,하:6,좌0,우:4
int xx[8] = { -1,-1,0,1,1,1,0,-1 };

int shdir[4] = { 2, 0, 6, 4 }; // 상좌하우 사전순 상어 이동 배열 인덱스

void copy(int finish) // 상어 마법 finish = 0 일때 마법 시전 , 1일때 복제완료
{
    if (!finish)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                cmap[i][j].clear();
                for (int n = 0; n < map[i][j].size(); n++)
                {
                    cmap[i][j].push_back(map[i][j][n]);
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                for (int n = 0; n < cmap[i][j].size(); n++)
                {
                    map[i][j].push_back(cmap[i][j][n]);
                }
            }
        }
    }
}

void move() // 물고기 이동
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            vector<int> tmp;
            for (int n = 0; n < map[i][j].size(); n++)// 맵에 있는 물고기 수 만큼
            {
                int dd = map[i][j][n];
                int flag = 1;
                for (int d = 0; d < 8; d++) // 8방향
                {
                    int dr = (8 + dd - d) % 8; // 반시계방향
                    gps mv = { i + yy[dr],j + xx[dr] };
                    if (mv.y < 0 || mv.y>3 || mv.x < 0 || mv.x>3)continue;
                    if (smell[mv.y][mv.x]> 0)continue;
                    if (mv.y == sh.y && mv.x == sh.x)continue;
                    mvmap[mv.y][mv.x].push_back(dr);
                    flag = 0; // 물고기가 이동했을시
                    break;
                }
                if (flag)tmp.push_back(dd); // 이동하지 않았다면 다시 그자리에 넣어주기 위해 tmp에 담기
            }
            for (int n = 0; n < tmp.size(); n++) // 이동못한 물고기 원위치
            {
                mvmap[i][j].push_back(tmp[n]);
            }
        }
    }
    for (int i = 0; i < 4; i++) // 이동맵으로 본래 맵 덮어씌우기
    {
        for (int j = 0; j < 4; j++)
        {
            map[i][j] = mvmap[i][j];
            mvmap[i][j].clear();
        }
    }
}

void dfs(int level,gps mvsh,int cnt) // 상어 이동경로 찾기
{
    if (level == 3)
    {
        if (cnt > outfish) // 가장 많은 물고기를 제외시킬수 있는경우
        {
            outfish = cnt;
            shpath = path;
        }
        return;
    }
    for (int i = 0; i < 4; i ++)
    {
        int d = shdir[i]; // 상좌하우 인덱스
        gps next = { mvsh.y + yy[d],mvsh.x + xx[d] };
        if (next.y < 0 || next.y>3 || next.x < 0 || next.x>3)continue;
        if (visit[next.y][next.x] == 1) // 중복된 위치는 이동가능하지만 제외되는 물고기수 중복 방지
        {
            path.push_back(next);
            dfs(level + 1, next, cnt);
            path.pop_back();
        }
        else
        {
            cnt += map[next.y][next.x].size();
            path.push_back(next);
            visit[next.y][next.x] = 1;
            dfs(level + 1, next, cnt);
            path.pop_back();
            cnt -= map[next.y][next.x].size();
            visit[next.y][next.x] = 0;
        }
    }
}

void shmove() // 상어 이동
{
    for (int i = 0; i < shpath.size(); i++) // 찾은 경로로 움직이기
    {
        gps now = shpath[i];
        if (map[now.y][now.x].size() > 0)
        {
            smell[now.y][now.x] = 3; // 최초에 3으로 셋팅, 냄새는 가장 최근 냄새 1개로 판단가능
            map[now.y][now.x].clear();
        }
    }
    sh = shpath[2]; // 마지막 상어의 위치
    shpath.clear();
    for (int i = 0; i < 4; i++) // 이전에 남아있는 냄새 -1
    {
        for (int j = 0; j < 4; j++)
        {
            if(smell[i][j]>0)smell[i][j] -= 1;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> m >> s;
    for (int i = 0; i < m; i++)
    {
        int x, y, d;
        cin >> x >> y >> d;
        map[x-1][y-1].push_back(d-1);
    }
    int x, y;
    cin >> x >> y;
    sh = { x-1,y-1 };
    for (int i = 0; i < s; i++)
    {
        copy(0);
        move();
        outfish = -1;
        shpath.clear();
        dfs(0,sh,0);
        shmove();
        copy(1);
    }
    int ans = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ans += map[i][j].size();
        }
    }
    cout << ans;

    return 0;
}