#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<cmath>
using namespace std;

// 1:18  예제 맞춤
// 1:32  정답!

struct gps {
    int y;
    int x;
};

int n,ans;
vector<int> map[20];
vector<int> path;

int yy[4] = { -1,1,0,0 }; // 위 아래 왼쪽 오른쪽 순서
int xx[4] = { 0,0,-1,1 };
vector<int> en; // 0 또는 n-1
int plusminus[2] = { 1,-1 }; //증가 감소 표현

void slide(int d) // 한쪽방향으로 몰기
{
    int dd = d % 2; // 위 또는 왼쪽방향일때 0  아래 또는 오른쪽 방향일때 1
    int ddd = (d + 1) % 2; // dd와 반대
    int i = en[dd]; // 윗방향일때 0 아래방향일때 n-1
    while (i != en[ddd] - plusminus[ddd]) // 윗방향일때 n-1-(-1) = n 아랫방향일때 0-1 = -1
    {
        int j = en[dd];
        while(j != en[ddd] - plusminus[ddd])
        {
            int yd = i, xd = j;
            while (yd + yy[d] >= 0 && yd + yy[d] <= n - 1 && xd + xx[d] <= n - 1 && xd + xx[d] >= 0 && map[yd + yy[d]][xd + xx[d]] == 0)
            {
                yd += yy[d];
                xd += xx[d];
            }
            int temp = map[i][j];
            map[i][j] = 0;
            map[yd][xd] = temp;
            j += plusminus[dd];
        }
        i += plusminus[dd]; // 윗방향일때 증가 아랫방향일때 감소
    }
}

void make(int d) // 같은 숫자 합치기
{
    int dd = d % 2;
    int ddd = (d + 1) % 2;
    int i = en[dd];
    while (i != en[ddd] - plusminus[ddd])
    {
        int j = en[dd];
        while (j != en[ddd] - plusminus[ddd])
        {
            if (i + yy[d] >= 0 && i + yy[d] <= n - 1 && j + xx[d] <= n - 1 && j + xx[d] >= 0 && map[i][j] == map[i + yy[d]][j + xx[d]])
            {
                map[i][j] = 0;
                map[i + yy[d]][j + xx[d]] *= 2; // 합쳐지는 방향쪽 블록X2
            }
            j += plusminus[dd];
        }
        i += plusminus[dd];
    }
}

int maxscore() // 가장큰 숫자 구하기
{
    int mmax = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            mmax = max(mmax, map[i][j]);
        }
    }
    return mmax;
}

void dfs(int level) // 5번 움직이는 모든 경우 dfs
{
    if (level == 5) // 5번 움직인뒤 가장큰 숫자 갱신
    {
        ans = max(ans, maxscore());
        return;
    }
    for (int i = 0; i < 4; i++)
    {
        vector<int> mapcopy[20]; // 맵 복사해두기
        for (int i = 0; i < n; i++)
        {
            mapcopy[i] = map[i];
        }
        slide(i); // 움직이고
        make(i); // 합치고
        slide(i); // 움직이고
        path.push_back(i);
        dfs(level + 1);
        path.pop_back();
        for (int i = 0; i < n; i++) // 맵 복원
        {
            map[i] = mapcopy[i];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();
    
    cin >> n;
    en.push_back(0);
    en.push_back(n-1); // en을 0 또는 n-1로 셋팅
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int a;
            cin >> a;
            map[i].push_back(a);
        }
    }
    dfs(0);
    cout << ans;
    return 0;
}