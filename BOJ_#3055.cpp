#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
using namespace std;
#define MAX 50

int r, c;
int dx[] = { 0,1,0,-1 };
int dy[] = { 1,0,-1,0 };
char map[MAX+1][MAX+1];
bool visited[MAX][MAX];
queue<pair<pair<int, int>, int>> q;
queue<pair<int, int>> water;

int main() {
	memset(visited, false, sizeof(visited));
	cin >> r >> c;
	for (int i = 0; i < r; i++) {
		cin >> map[i];
		for (int j = 0; j < c; j++) {
			//고슴도치
			if (map[i][j] == 'S') {
				q.push(make_pair(make_pair(i, j), 0));
				visited[i][j] = true;
			}
			//물
			if (map[i][j] == '*') {
				water.push(make_pair(i, j));
			}
		}
	}

	while (!q.empty()) {
		int wsize = water.size();
		//홍수 먼저 map에 적용
		for (int i = 0; i < wsize; i++) {
			int y = water.front().first;
			int x = water.front().second;
			water.pop();

			for (int j = 0; j < 4; j++) {
				int ny = y + dy[j];
				int nx = x + dx[j];
				if (ny < 0 || ny >= r || nx < 0 || nx >= c) continue;
				if (map[ny][nx] == '.') {
					map[ny][nx] = '*';
					water.push(make_pair(ny, nx));
				}
			}
		}

		//홍수 적용된 map에서 고슴도치 이동
		int ksize = q.size();
		for (int k = 0; k < ksize; k++) {
			int y = q.front().first.first;
			int x = q.front().first.second;
			int count = q.front().second;
			q.pop();

			if (map[y][x] == 'D') {
				cout << count << endl;
				return 0;
			}
			for (int i = 0; i < 4; i++) {
				int ny = y + dy[i];
				int nx = x + dx[i];
				if (ny < 0 || ny >= r || nx < 0 || nx >= c) continue;
				if (map[ny][nx] == '*' || map[ny][nx] == 'X') continue;
				if (visited[ny][nx]) continue;

				visited[ny][nx] = true;
				q.push(make_pair(make_pair(ny, nx), count + 1));
			}
		}
	}
	cout << "KAKTUS" << endl;

	return 0;
}