#include<iostream>

using namespace std;

int n;
int dp[100000];

int make(int num)
{
	if (dp[num] == 0)
	{
		//  n��° ���� ���°�� [ n-2������ ����Ǽ� * n-1��° ���� ä��� ����� ��(=3) ]
		//  n��° ���� ä��� ��� [ ����,������ (=2) * (n-1��° ����Ǽ� - n��°�� ä����ĭ�� �ݴ�Ǵ� ĭ�� ä���� ����� ��)]
		dp[num] = (3 * make(num - 2) + 2 * (make(num - 1) - make(num - 2))) % 9901; 
		return dp[num];
	}
	else return dp[num];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	dp[0] = 3;
	dp[1] = 7;

	cout << make(n - 1);

	return 0;
}