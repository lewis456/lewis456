#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define MAX 200001

int map[3][MAX];
bool visited[3][MAX];
int n, k;
queue<pair<pair<int, int>, int>> q;		//n번 라인의 i번째 칸, 시간

int main() {
	memset(visited, false, sizeof(visited));
	memset(map, 1, sizeof(map));
	cin >> n >> k;
	for (int i = 1; i <= 2; i++) {
		for (int j = 1; j <= n; j++)
			scanf("%1d", &map[i][j]);
	}
	visited[1][1] = true;
	q.push(make_pair(make_pair(1, 1), 1));
	while (!q.empty()) {
		int line = q.front().first.first;
		int loc = q.front().first.second;
		int sec = q.front().second;

		q.pop();

		if (loc >= n) {
			cout << 1 << endl;
			return 0;
		}
		//한 칸 앞으로 이동 가능
		if (map[line][loc + 1] != 0 && visited[line][loc + 1] == false) {
			visited[line][loc + 1] = true;
			q.push(make_pair(make_pair(line, loc + 1), sec + 1));
		}
		//한 칸 뒤로 이동 가능
		if (loc - 1 > sec && map[line][loc - 1] != 0 && visited[line][loc - 1] == false) {
			visited[line][loc - 1] = true;
			q.push(make_pair(make_pair(line, loc - 1), sec + 1));
		}

		//반대편으로 점프
		int cross = 2 / line;
		if (map[cross][loc + k] != 0 && visited[cross][loc + k] == false) {
			visited[cross][loc + k] = true;
			q.push(make_pair(make_pair(cross, loc + k), sec + 1));
		}
	}

	cout << 0 << endl;

	return 0;
}