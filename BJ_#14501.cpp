#include<cstdio>
#include<iostream>
#include<queue>
#include <algorithm>

using namespace std;

int n;
int time[16], pay[16];
int dp[16];					//i��° �� ���� ������ �� ���� �ִ� �ݾ�

int method(int);
int main() {
	cin >> n;
	memset(dp, -1, sizeof(dp));
	for (int i = 1; i <= n; i++) cin >> time[i] >> pay[i];

	cout << method(1) << endl;
}

int method(int day) {		//day=���� ��¥
	if (day > n) return 0;
	if (dp[day] != -1) return dp[day];
	
	if ((day + time[day] - 1) <= n) 		//�̳� ���� �ص� ��� ���̶��
		dp[day] = max(pay[day] + method(day + time[day]), method(day + 1));		//�̳� ���ϱ� vs �̳� �� ���ϱ�
	else									//��� ������ ���� �������ٸ�
		dp[day] = method(day + 1);			

	return dp[day];
}