#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

long long dp[31][31];
//한조각w개, 반조각h개 있을 때 가능한 경우의 수
int n;

long long method(int, int);

int main() {
	for (int i = 0; i < 1000; i++) {
		memset(dp, -1, sizeof(dp));
		cin >> n;
		if (n == 0) break;
		cout << method(n, 0)<<endl;
	}
	return 0;
}

long long method(int w, int h) {
	if (dp[w][h] != -1) return dp[w][h];

	//한조각 짜리가 없다면 반조각을 먹는 경우뿐
	if (w == 0) return 1;				

	dp[w][h] = method(w - 1, h + 1);		//한조각짜리를 먹는 경우
	if (h > 0) {							//반조각짜리 먹는 경우
		dp[w][h] += method(w, h - 1);
	}
	
	return dp[w][h];
}