#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int t, n, cnt = 0;

void sum(int s) {
	if (s == n)
		cnt++;
	if (s > n) return;		//±âÀú

	sum(s + 1);
	sum(s + 2);
	sum(s + 3);
}

int main() {
	cin >> t;
	for (int i = 0; i < t; i++) {
		cin >> n;
		sum(0);
		cout << cnt << endl;
		cnt = 0;
	}

	return 0;
}