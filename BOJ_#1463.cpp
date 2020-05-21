#include <iostream>
using namespace std;

int dp[1000001];		//dp[n] : n�϶� �ּҿ���
int main() {
	int n;
	cin >> n;
	dp[1] = 0;
	for (int i = 2; i <= n; i++) {
		//���� 1�� ���ٰ� ����
		dp[i] = 1 + dp[i - 1];

		//2�� ������ �������� ������ �� ���� ���
		if (i % 2 == 0 && dp[i] > dp[i / 2] + 1)
			dp[i] = dp[i / 2] + 1;

		//3���� ������ �������� ������ �� ���� ���
		if (i % 3 == 0 && dp[i] > dp[i / 3] + 1)
			dp[i] = dp[i / 3] + 1;
	}
	cout << dp[n] << endl;
	return 0;
}