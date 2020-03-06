#include <memory.h>
#include<iostream>
#include <queue>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

#define MAX 201

int k, w, h;
int map[MAX][MAX];
bool visited[MAX][MAX][31];					//(y,x)������ �ɷ��� k�� ����Ͽ� ����
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
int k_x[] = { -2,-2,-1,-1,1,1,2,2 };
int k_y[] = { 1,-1,2,-2,2,-2,1,-1 };

queue < pair<pair<int, int>, pair<int, int>>> q;
			//(y,x)������  �ɷ��� k�� ����Ͽ� n��° ������

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	memset(visited, false, sizeof(visited));

	cin >> k >> w >> h;
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) cin >> map[i][j];
	}
	q.push(make_pair(make_pair(1, 1), make_pair(0, 0)));
	while (!q.empty()) {
		int y = q.front().first.first;
		int x = q.front().first.second;
		int abt = q.front().second.first;
		int cnt = q.front().second.second;
		q.pop();

		if (y == h && x == w) {				//����
			cout << cnt << endl;
			return 0;
		}

		if (abt < k) {							//���� �ɷ� ��밡���� ����
			for (int i = 0; i < 8; i++) {		//�ɷ� ����Ͽ� ������
				int ny = y + k_y[i];
				int nx = x + k_x[i];
				if (ny >= 1 && ny <= h&&nx >= 1 && nx <= w) {
					if (map[ny][nx] != 1 && visited[ny][nx][abt + 1] == false) {
						q.push(make_pair(make_pair(ny, nx), make_pair(abt+1, cnt+1)));
						visited[ny][nx][abt + 1] = true;
					}
				}
			}
		}

		for (int i = 0; i < 4; i++) {			//�ɷ� �Ⱦ��� �����̱�
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (ny >= 1 && ny <= h&&nx >= 1 && nx <= w) {
				if (map[ny][nx] != 1 && visited[ny][nx][abt] == false) {
					q.push(make_pair(make_pair(ny, nx), make_pair(abt, cnt+1)));
					visited[ny][nx][abt] = true;
				}
			}
		}
	}
	cout << -1 << endl;
}