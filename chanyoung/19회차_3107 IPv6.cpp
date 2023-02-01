#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

string ipv6; // 입력받는 주소값
vector<char> ans; // 풀이한 주소값
int point = 0;
int skip; // ::이 시작되는 인덱스 번호 

void check(vector<char> s)
{
    if (s.size() == 0)return; // 입력시 시작부터 :로 시작한경우 리턴
    int len = s.size(); // 입력 자릿수
    while (len < 4) // 4자리를 채울때 까지
    {
        ans.push_back('0'); // 0으로 채우기
        len++;
    }
    for (int i = 0; i < s.size(); i++)
    {
        ans.push_back(s[i]); // 복원숫자 넣기
    }
}

void zero()
{
    int cnt = 0;
    int ncnt = 0;
    vector<char> tmp;
    for (int i = 0; i < skip; i++)tmp.push_back(ans[i]); // ::전까지 ans를 tmp에 옮기기
    if (tmp.size()) // ::이 맨앞이 아닌경우 :를 하나 추가하고 시작
    {
        tmp.push_back(':');
        cnt++;
    }
    while (cnt <= 39 - ans.size()) // 생략된 수만큼
    {
        if (ncnt == 4) // 0을 4개 채울때 마다 : 하나 채우기
        {
            tmp.push_back(':');
            cnt++;
            ncnt = 0;
        }
        else
        {
            tmp.push_back('0');
            cnt++;
            ncnt++;
        }
    }
    if (ans[ans.size() - 1] == ':')tmp.push_back('0'); // ::이 맨 뒤인경우 0으로 치환
    else for (int i = skip + 1; i < ans.size(); i++)tmp.push_back(ans[i]); // :: 이후 ans를 tmp에 옮기기
    ans = tmp; // ans 완성
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> ipv6;
    int len = ipv6.size();
    vector<char> sec;
    while (point < len) // 입력받은 주소를 훑으면서
    {
        if (ipv6[point] == ':')
        {
            if (ipv6[point + 1] == ':') // 두개 연속일때
            {
                check(sec); // 이전까지의 4자리 풀이하고
                sec.clear();
                skip = ans.size(); // ::의 시작 인덱스 갱신
                point += 2; // ::이니까 포인터 2개 옮김
                ans.push_back(':'); // ans에 그대로 옮기기
            }
            else // 하나만 있다면
            {
                check(sec); //4자리 해석
                point++;
                sec.clear();
            }
            ans.push_back(':'); // ans에 : 옮겨주기
        }
        else // :가 아닌 주소값이라면
        {
            sec.push_back(ipv6[point]); // 해석할 4자리 후보로 옮김
            point++;
        }
    }
    check(sec); // 마지막 4자리 해석
    if (ans.size() != 39) zero(); // ans가 39자리가 안된다 >>> ::이 포함되어있다 >> 복원하기
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i];
    }

    return 0;
}
