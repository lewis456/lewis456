#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n;
long long dp[101];			//n�� ������ �� �ִ�

long long method(int);		

int main() {
	cin >> n;
	memset(dp, -1, sizeof(dp));
	dp[0] = 0;

	cout << method(n) << endl;

	return 0;
}

long long method(int cnt) {
	if (dp[cnt] != -1) return dp[cnt];
	dp[cnt] = method(cnt - 1) + 1;			//A�ϳ� ���
	
	//���ۿ� �ѹ� ������ ������ ��� �ٿ��ֱ� ����
	//��ü����+���� -> 2�� �� �ٿ��ֱ� i��
	if (cnt >= 3) {		//�ּ� 3�� �ؾ���
		for (int i = 1; i <= cnt - 3; i++) {
			dp[cnt] = max(dp[cnt], method(cnt - 2 - i)*(i+1));
		}
	}
	return dp[cnt];
}