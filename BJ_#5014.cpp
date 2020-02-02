#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
using namespace std;

int f, s, g, u, d;
//f:건물높이, s:초기위치, g:목표위치
bool visit[1000001];
queue<pair<int, int>> q;

int bfs() {
	q.push(make_pair(s, 0));
	visit[s] = true;
	while (!q.empty()) {
		int cur = q.front().first;
		int cnt = q.front().second;
		q.pop();

		if (cur == g) return cnt;							//도착
		if (cur + u <= f&&visit[cur + u] == false) {		//올라갈 수 있는 경우
			q.push(make_pair(cur + u, cnt + 1));
			visit[cur + u] = true;
		}
		if (cur - d >= 0 && visit[cur - d] == false) {		//내려갈 수 있는 경우
			q.push(make_pair(cur - d, cnt + 1));
			visit[cur - d] = true;
		}
	}
	return -1;												//도착못함
}

int main() {
	cin >> f >> s >> g >> u >> d;
	int ans = bfs();
	if (ans == -1) cout << "use the stairs" << endl;
	else cout << ans << endl;

	return 0;
}