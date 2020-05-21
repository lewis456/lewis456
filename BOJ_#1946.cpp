#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
using namespace std;

int t, n;

int main() {
	cin >> t;
	while(t--) {
		vector<pair<int, int>> v;
		cin >> n;
		for (int i = 0; i < n; i++) {
			int a, b;
			cin >> a >> b;
			v.push_back(make_pair(a, b));
		}
		sort(v.begin(), v.end());		//첫번째 성적 기준 오름차순
										//두번째 성적만 비교하면 됨
		int cur = v[0].second;
		int ans = 1;
		for (int i = 1; i < n; i++) {
			if (v[i].second < cur) {	//더 낮은 점수를 골라야 최대로 늘릴 수 있음
				ans++;
				cur = v[i].second;
			}
		}
		cout << ans << endl;
	}
	
	return 0;
}