#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, k, a[100];
int total = 0;

int main() {
	cin >> n >> k;
	for (int i = 0; i < k; i++) {
		int hole;
		cin >> hole;
		a[i] = (hole + 1) / 2;
		total += a[i];
	}

	if (total >= n) cout << "YES" << endl;
	else cout << "NO" << endl;

}