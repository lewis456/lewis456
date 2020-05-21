#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
using namespace std;

#define MAX 20

char map[MAX][MAX];
int R, C, ans = 1;
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
bool visited[26];

bool check(int y, int x, bool visited[26]) {
	if (y < 0 || y >= R || x < 0 || x >= C) return true;
	if (visited[map[y][x] - 'A']) return true;
	return false;
}

void dfs(int y, int x, int count) {
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (check(ny, nx, visited)) continue;

		visited[map[ny][nx] - 'A'] = true;			
		dfs(ny, nx, count + 1);			
		visited[map[ny][nx] - 'A'] = false;						
	}
	ans = max(ans, count);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> R >> C;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++)
			cin >> map[i][j];
	}
	visited[map[0][0] - 'A'] = true;
	dfs(0, 0, 1);
	cout << ans << endl;

	return 0;
}