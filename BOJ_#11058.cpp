#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n;
long long dp[101];			//n번 눌렀을 때 최댓값

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
	dp[cnt] = method(cnt - 1) + 1;			//A하나 출력
	
	//버퍼에 한번 복사해 놓으면 계속 붙여넣기 가능
	//전체선택+복사 -> 2번 후 붙여넣기 i번
	if (cnt >= 3) {		//최소 3번 해야함
		for (int i = 1; i <= cnt - 3; i++) {
			dp[cnt] = max(dp[cnt], method(cnt - 2 - i)*(i+1));
		}
	}
	return dp[cnt];
}