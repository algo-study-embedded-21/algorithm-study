#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <string.h>
using namespace std;

struct gps { int y,x; };
int n, m;
vector<int> dir; // 이동 방향
vector<int> dis; // 이동 거리
vector<gps> cloud; // 생성된 (이동전) 구름
vector<gps> rain; // 이동한 구름 (비 내릴곳)

int map[51][51];

int yy[8] = { 0,-1,-1,-1,0,1,1,1 };
int xx[8] = { -1,-1,0,1,1,1,0,-1 };

int side[4] = { 1,3,5,7 }; // 대각방향 인덱스

void move(int t) // 구름 이동
{
    rain.clear();
    int dd = dir[t] - 1;
    int ss = dis[t] % n; // 맵 내에서만 이동하도록
    for (int i = 0; i < cloud.size(); i++)
    {
        gps now = cloud[i];
        gps next = { now.y + yy[dd]*ss, now.x + xx[dd]*ss };
        if (next.y > n) next.y = next.y - n;
        if (next.y < 1)next.y = n + next.y;
        if (next.x > n)next.x = next.x - n;
        if (next.x < 1)next.x = n + next.x;
        rain.push_back(next);
    }
    cloud.clear();
}

void rainy()
{
    for (int i = 0; i < rain.size(); i++)
    {
        gps now = rain[i];
        map[now.y][now.x] += 1; // 비내리기
    }
    int rmap[51][51] = { 0 };
    for (int i = 0; i < rain.size(); i++)
    {
        gps now = rain[i];
        int cnt = 1; // 대각에 물있는 바구니 갯수 (비내린 자리 판별위해 1로 셋팅)
        for (int d = 0; d < 4; d++)
        {
            int dd = side[d];
            gps next = { now.y + yy[dd], now.x + xx[dd] };
            if (next.y > n || next.y<1 || next.x>n || next.x < 1)continue;
            if (map[next.y][next.x] == 0)continue;
            cnt++;
        }
        rmap[now.y][now.x] = cnt;
    }
    for (int i = 0; i < rain.size(); i++)
    {
        gps now = rain[i];
        map[now.y][now.x] += rmap[now.y][now.x]-1; // 셋팅된 1빼고 더해주기
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++) // 새로운 구름 생성
        {
            if (rmap[i][j] > 0)continue; // 구름이 사라진 자리 판별
            if (map[i][j] < 2)continue; 
            map[i][j] -= 2;
            cloud.push_back({ i,j });
        }
    }
}

int go()
{
    for (int i = 0; i < m; i++) // m번이동
    {
        move(i);
        rainy();
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++) // 남은 물의양 카운트
    {
        for (int j = 1; j <= n; j++)
        {
            cnt += map[i][j];
        }
    }
    return cnt;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> map[i][j];
        }
    }
    for (int i = 0; i < m; i++)
    {
        int d, s;
        cin >> d >> s;
        dir.push_back(d);
        dis.push_back(s);
    } 
    // 최초 구름 셋팅
    cloud.push_back({ n,1 });
    cloud.push_back({ n,2 });
    cloud.push_back({ n-1,1 });
    cloud.push_back({ n-1,2 });
    cout << go();

    return 0;
}
