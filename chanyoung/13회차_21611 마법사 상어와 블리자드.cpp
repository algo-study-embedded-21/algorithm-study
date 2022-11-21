#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <string.h>
using namespace std;

struct gps { int y, x; };
struct mapnum { int num, cnt; }; // 칸의 순서 , 칸에 있는 구슬 번호

int n, m;
mapnum map[50][50];
vector<int> magic; // 블리자드 마법 거리
vector<int> magicDir; // 블리자드 마법 방향
int one, two, three;
vector<int> line; // 달팽이 배열을 한줄로
vector<int> out; // 파괴된 위치 표시
gps shark; // 상어의 위치(정중앙)

int yy[4] = { -1,1,0,0 };
int xx[4] = { 0,0,-1,1 };

int turn[4] = { 2,1,3,0 }; // 달팽이 배열 진행방향

void refill() // 파괴된 구슬 제거
{
    vector<int> tmp;
    vector<int> outtmp;
    for (int i = 0; i < line.size(); i++)
    {
        if (out[i])continue; // 파괴된 구슬 빼고
        tmp.push_back(line[i]);
        outtmp.push_back(0);
    }
    line = tmp;
    out = outtmp;
}

void makeline() // 달팽이 배열 한줄로 만들기
{
    gps next = shark;
    int go = 1;
    int dir = 0;
    int num = 0;
    while (go <= n)
    {
        for (int t = 0; t < 2; t++) //같은 길이로 2번 반복(방향만 변경)
        {
            int d = turn[dir];
            for (int i = 0; i < go; i++)
            {
                next = { next.y + yy[d],next.x + xx[d] };
                if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>n - 1)continue;
                int cnt = map[next.y][next.x].cnt;
                map[next.y][next.x].num = num;
                num++;
                if (cnt == 0)continue;; // 구슬이 없으면 번호만 표시하고 추가하지 않기
                line.push_back(cnt);
                out.push_back(0);
            }
            dir += 1;
            dir %= 4;
        }
        go++; // 길이 늘림
    }
}

void breaking(int d, int s) // 마법으로 구슬 파괴
{
    if (line.size() == 0)return;
    gps next = shark;
    for (int i = 0; i < s; i++)
    {
        next = { next.y + yy[d],next.x + xx[d] };
        if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>n - 1)break;
        int num = map[next.y][next.x].num;
        if (num >= line.size())break;
        out[num] = 1; // 파괴될 구슬 표시
    }
    refill();
}

void fourblock() // 4개이상 폭발
{
    int bf = -1;
    int cnt = 0;
    int flag = 1;
    while (flag) // 폭발이 없을때까지 반복
    {
        if (line.size() < 4)return;
        flag = 0;
        vector<int> erase; // 폭발할 그룹
        for (int i = 0; i < line.size(); i++)
        {
            int now = line[i];
            if (now == bf)
            {
                erase.push_back(i); // 연속된 구슬 그룹에 담기
                if (i == line.size() - 1) // 마지막 구슬이 그룹에 포함될경우
                {
                    if (erase.size() >= 4)
                    {
                        flag = 1;
                        for (int j = 0; j < erase.size(); j++)
                        {
                            out[erase[j]] = 1;
                            if (bf == 1)one++;
                            else if (bf == 2)two++;
                            else if (bf == 3)three++;
                        }
                    }
                }
            }
            else
            {
                if (erase.size() >= 4) // 그룹크기가 4이상이면 폭발
                {
                    flag = 1;
                    for (int j = 0; j < erase.size(); j++)
                    {
                        out[erase[j]] = 1;
                        if (bf == 1)one++;
                        else if (bf == 2)two++;
                        else if (bf == 3)three++;
                    }
                }
                erase.clear(); // 폭발후 그룹 초기화
                erase.push_back(i);
            }
            bf = now;
        }
        if (flag) refill(); // 폭발한 구슬이 없다면 실행하지 않는다
    }
}

void change() // 구슬 변화
{
    if (line.size() == 0)return;
    int bf = line[0]; // 현재 그룹의 구슬 번호
    int cnt = 1;
    vector<int> tmp; // 변화한 구슬 저장
    vector<int> outtmp;
    for (int i = 1; i < line.size(); i++)
    {
        int now = line[i];
        if (bf == now)cnt++;
        else
        {
            tmp.push_back(cnt);
            tmp.push_back(bf);
            outtmp.push_back(0);
            outtmp.push_back(0);
            cnt = 1;
            bf = now;
        }
        if (i == line.size() - 1) // 마지막구슬일 경우 인위적으로 저장
        {
            tmp.push_back(cnt);
            tmp.push_back(bf);
            outtmp.push_back(0);
            outtmp.push_back(0);
        }
        if (tmp.size() + 1 >= n * n)break; // 구슬이 맵의 크기를 벗어날경우 중단
    }
    while (tmp.size() + 1 > n * n) // 맵을 벗어난 구슬 제거 
    {
        tmp.pop_back();
        outtmp.pop_back();
    }
    line = tmp;
    out = outtmp;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j].cnt;
        }
    }
    for (int i = 0; i < m; i++)
    {
        int d, s;
        cin >> d >> s;
        magicDir.push_back(d - 1);
        magic.push_back(s);
    }
    shark = { n / 2,n / 2 };
    makeline();
    for (int i = 0; i < m; i++)
    {
        int d = magicDir[i];
        int s = magic[i];
        breaking(d, s);
        fourblock();
        change();
    }
    int ans = 1 * one + 2 * two + 3 * three;
    cout << ans;

    return 0;
}