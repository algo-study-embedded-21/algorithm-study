#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

struct damage { int one, two, three; };

int n;
int hp[61][61][61]; // scv1의 체력 , 2의 체력, 3의 체력 이 되기위한 최소 횟수 dp
int scv[3]; // 주어진 최초의 체력 , svc가 없는경우 0
int maxhp = -1; // 주어진 최초 체력중 가장 큰 값
damage attack[6] = { {9,3,1} ,{9,1,3},{3,9,1},{3,1,9},{1,9,3},{1,3,9} }; // 공격하는 경우의수


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> scv[i];
		maxhp = max(maxhp, scv[i]);
	}
	for (int i = 0; i <= maxhp; i++)
	{
		for (int j = 0; j <= maxhp; j++)
		{
			for (int k = 0; k <= maxhp; k++)
			{
				hp[i][j][k] = 213456789;
			}
		}
	}
	hp[scv[0]][scv[1]][scv[2]] = 0;
	for (int i = maxhp; i >= 0; i--)
	{
		for (int j = maxhp; j >= 0; j--)
		{
			for (int k = maxhp; k >= 0; k--)
			{
				if (hp[i][j][k] != 213456789)// 가능한 경우의 수
				{
					for (int d = 0; d < 6; d++)
					{// 지금 체력에서 횟수 +1 과 이미 가지고있던 값중 최솟값으로 저장 (체력은 0 밑으로 떨어지지 않도록)
						hp[max(0, i - attack[d].one)][max(0, j - attack[d].two)][max(0, k - attack[d].three)]
							= min(hp[i][j][k] + 1, hp[max(0, i - attack[d].one)][max(0, j - attack[d].two)][max(0, k - attack[d].three)]);
					}
				}
			}
		}
	}

	cout << hp[0][0][0];
	
	return 0;
}