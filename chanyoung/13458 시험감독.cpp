#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include<cstring>

using namespace std;

int main()
{

	vector<int> test;
	int n;
	cin >> n; // ������ ����
	long long cnt = 0; // ��������
	for (int i = 0; i < n; i++) //������ ����ŭ �ݺ�
	{
		int a;
		cin >> a;
		test.push_back(a);  // ������ ���� ���Ϳ� ����
		cnt++; // �����帶�� �Ѱ����� 1�� �ʼ�
	}
	int b, c;
	cin >> b >> c; // ������ ���� �Է�
	for (int i = 0; i < n; i++)
	{
		if (test[i] - b > 0)
		{
			int ex = test[i] - b; // ������ ������ ������ �Ѱ����� 1����� �����ڼ��� ��
			if ((ex % c) == 0)  // �� ������ �������� ������ �����ڼ��� ������ ������ ���
			{
				cnt = cnt + ex / c;
			}
			else  // ������ �������� �������
			{
				cnt = cnt + ex / c + 1;  // ���� �����ڼ� ������ +1
			}
		}
	}
	cout << cnt;
	return 0;
}