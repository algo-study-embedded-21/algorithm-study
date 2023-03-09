#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

int n, k;
vector<string> line;
int alpha[150]; // alpha['c'] = c를 배웠다면 1 안배웠다면 0
string basic = "antatica"; // 남극 단어 기본
int ans;
vector<char> v;

int cnt() // 배운것으로 몇개나 읽을수 있는가
{
    int CNT = 0;
    for (int i = 0; i < n; i++)
    {
        int is = 1;
        for (int j = 0; j < line[i].size(); j++)
        {
            if (alpha[line[i][j]] == 0) // 배운적 없는 알파벳이 있다면
            {
                is = 0;
                break;
            }
        }
        if (is)CNT++;
    }
    return CNT;
}

void dfs(int level,char c)
{
    if (level == k-5) // 남극 기본 알파벳 5개 제외한 나머지 다 골랐을때
    {
        int CNT = cnt();
        ans = max(ans, CNT);
        return;
    }
    // k - 5 > level(고른갯수) + ('z' - c )(남은 알파벳) 
    //if (c + (k - 5 - level) > 'z')return; // 남은걸 다 골라도 k개가 안되는경우
    for (char i = c; i <= 'z'; i++)
    {
        if (alpha[i])continue;
        alpha[i] = 1;
        v.push_back(i);
        dfs(level + 1, i + 1); // 조합으로 조사하기 
        v.pop_back();
        alpha[i] = 0;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();
    
    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        string a;
        cin >> a;
        a = a.substr(3, a.size()-7); // 기본 형식 잘라내고 저장하기
        line.push_back(a);
    }
    if (k < 5) // 기본 단어도 충족하지 못하는 경우
    {
        cout << '0';
        return 0;
    }
    for (int i = 0; i < basic.size(); i++) // 기본 단어 미리 표시하기
    {
        char c = basic[i];
        alpha[c] = 1;
    }
    dfs(0, 'b'); // a는 기본단어 포함이므로 b부터 시작하기
    cout << ans;
   
    return 0;
}
