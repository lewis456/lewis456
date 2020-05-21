#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
using namespace std;

#define MAX 100001

int n, k, m;
int ans = 1;
vector<int> v[MAX+MAX];
queue<int> q;
bool visited[MAX+MAX];

int main() {
	cin >> n >> k >> m;
	//n:전체 역 개수  k:하이퍼튜브가 연결하는 역 수  m:하이퍼튜브 수
	for (int i = 1; i <= m; i++) {
		for (int j = 0; j < k; j++) {
			int temp;
			cin >> temp;
			//i번째 하이퍼튜브에 k개의 역을 연결
			v[i + n].push_back(temp);
			//역을 하이퍼튜브에 연결
			v[temp].push_back(i + n);
		}
	}
	q.push(1);
	visited[1] = true;
	while (!q.empty()) {
		int size = q.size();
		while (size--) {
			int cur = q.front();	//현재 살펴볼 역
			q.pop();
			if (cur == n) {
				cout << ans/2+1 << endl;
				return 0;
			}
			for (auto &i : v[cur]) {	//i:현재 역에 연결된 역
					if (visited[i]) continue;
					q.push(i);
					visited[i] = true;
			}
		}
		ans++;
	}
	cout << -1 << endl;
	return 0;
}