#include<cstdio>
#include <memory.h>
#include<iostream>
#include<queue>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
int map[26][26];
queue<pair<int, int>> q;
int n, total_num = 0;
vector<int> v;

int bfs();
int main() {
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			scanf("%1d", &map[i][j]);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] == 1) {			//�� �߰�
				map[i][j] = 0;				//�ߺ� ���ϱ� ���� 0���� ����
				q.push(make_pair(i, j));	//�� ��ǥ�� ť�� push
				total_num++;				//������++
				v.push_back(bfs());			//bfs()�Լ��� ���� ���� �� ���� �� ���Ϳ� push
			}
		}
	}
	cout << total_num << endl;
	sort(v.begin(), v.end());
	for (int i = 0; i < v.size(); i++) cout << v[i] << endl;
	return 0;
}

int bfs() {
	int cnt = 1;
	while (!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (ny >= n || ny < 0 || nx >= n || nx < 0) continue;
			if (map[ny][nx] == 1) {				//�� �ֺ��� �ٸ� ���� �ִٸ�
				cnt++;							//���� �� ���� �� ++
				map[ny][nx] = 0;				//�ߺ� ���ϱ� ���� 0���� ����
				q.push(make_pair(ny, nx));		//�ֺ� �� ��ǥ�� ť�� push
			}
		}
	}
	return cnt;
}