#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <string.h>
using namespace std;

struct gps { int y, x; };
struct smell { int snum, last; }; // 냄새의 주인번호 , 남은시간

int n, m, k;
int map[20][20];
smell smellmap[20][20]; //각 위치에 남은 냄새 표시
gps shark[400]; // 상어들의 현재 위치
int nowdir[400]; // 상어들이 보고있는 방향
int outshark[400]; // 퇴출된 상어 표시
vector<int> sdir[400][4]; // 상어들의 방향 우선순위

int yy[4] = { -1,1,0,0 };
int xx[4] = { 0,0,-1,1 };

void move()
{
    int tmp[20][20] = { 0 };
    for (int i = 1; i <= m; i++) // 1번 상어부터 이동
    {
        if (outshark[i])continue; // 퇴출된 상어 제외
        gps now = shark[i];
        int d = nowdir[i];
        gps check = { 30,30 }; // 이동할 위치 초기값(맵밖)
        int checkd; // 이동한 후 바라보는 방향
        for (int j = 0; j < 4; j++)
        {
            int dd = sdir[i][d][j]; // 우선순위에 따른 방향
            gps next = { now.y + yy[dd], now.x + xx[dd] };
            if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>n - 1)continue;
            if (check.y == 30 && smellmap[next.y][next.x].snum==i) 
            { // 자기냄새인 인접칸중 우선순위 방향에 따라 가장 첫번째 칸
                check = next;
                checkd = dd;
            }
            else if (smellmap[next.y][next.x].snum==0)
            { // 냄새가 없는 칸 존재시 이동칸으로 확정!
                check = next;
                checkd = dd;
                break;
            }
        }
        if (check.y == 30)continue; // 이동할수 있는 칸이 없는경우
        if (tmp[check.y][check.x] == 0 || tmp[check.y][check.x]>i)
        { // 그 칸으로의 이동이 내가 처음이거나 나보다 큰번호의 상어가 있는경우 자리차지
            outshark[tmp[check.y][check.x]] = 1;
            tmp[check.y][check.x] = i;
            map[check.y][check.x] = i;
            shark[i] = check;
            nowdir[i] = checkd;
        }
        else if(tmp[check.y][check.x] < i) outshark[i] = 1; // 나보다 작은 번호의 상어가 있는경우 내가 퇴출
    }
}

void makesmell() // 냄새 갱신
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++) // 모든 맵에 대해
        {
            if (smellmap[i][j].last > 0)
            {
                smellmap[i][j].last -= 1; // 냄새 줄이고
                if (smellmap[i][j].last == 0) smellmap[i][j].snum = 0; // 냄새가 다 빠지면 초기화
            }
        }
    }
    for (int i = 1; i <= m; i++) // 상어들 현재위치에 냄새 남기기
    {
        if (outshark[i])continue;
        gps now = shark[i];
        smellmap[now.y][now.x].snum = i;
        smellmap[now.y][now.x].last = k;
    }
}

int check() // 종료조건
{
    for (int i = 2; i <= m; i++) if (outshark[i] == 0)return 0;
    return 1;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
            if (map[i][j] > 0)shark[map[i][j]] = { i,j };
        }
    }
    for (int i = 1; i <= m; i++)
    {
        int d;
        cin >> d;
        nowdir[i] = d - 1;
    }
    for (int i = 1; i <= m; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int a = 0; a < 4; a++)
            {
                int d;
                cin >> d;
                sdir[i][j].push_back(d - 1);
            }
        }
    }
    makesmell(); // 최초에 냄새 남기고 시작
    for (int i = 1; i <= 1000; i++)
    {
        move();
        makesmell();
        if (check())
        {
            cout << i;
            return 0;
        }
    }
    cout << "-1";
    return 0;
}