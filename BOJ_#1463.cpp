#include <iostream>
using namespace std;

int dp[1000001];		//dp[n] : n일때 최소연산
int main() {
	int n;
	cin >> n;
	dp[1] = 0;
	for (int i = 2; i <= n; i++) {
		//먼저 1을 뺀다고 가정
		dp[i] = 1 + dp[i - 1];

		//2로 나누어 떨어지고 연산이 더 적은 경우
		if (i % 2 == 0 && dp[i] > dp[i / 2] + 1)
			dp[i] = dp[i / 2] + 1;

		//3으로 나누어 떨어지고 연산이 더 적은 경우
		if (i % 3 == 0 && dp[i] > dp[i / 3] + 1)
			dp[i] = dp[i / 3] + 1;
	}
	cout << dp[n] << endl;
	return 0;
}