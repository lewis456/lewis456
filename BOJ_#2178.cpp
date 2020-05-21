#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define MAX 101

int n, m;
int map[MAX][MAX];
bool visited[MAX][MAX];
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int rst = 2e9;
queue<pair<pair<int, int>, int>> q;		//현재 위치 좌표, 이동 수

int main() {
	memset(visited, false, sizeof(visited));
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%1d", &map[i][j]);
		}
	}
	q.push(make_pair(make_pair(1, 1), 1));
	visited[1][1] = true;

	while (!q.empty()) {
		int y = q.front().first.first;
		int x = q.front().first.second;
		int count = q.front().second;
		q.pop();

		//목표지점 도착
		if (y == n && x == m) {
			rst = min(rst, count);
			continue;
		}

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			//이동 불가능한 경우 continue
			if (ny<1 || ny>n || nx<1 || nx>m) continue;
			if (visited[ny][nx] == true) continue;
			if (map[ny][nx] == 0) continue;

			//이동 가능한 경우
			visited[ny][nx] = true;
			q.push(make_pair(make_pair(ny, nx), count + 1));
		}
	}

	cout << rst << endl;
	return 0;
}