#include<cstdio>
#include <memory.h>
#include<iostream>
#include<queue>
#include <algorithm>
#include <string>

#define MAX 100000
using namespace std;

queue<pair<int, int>> q;		//first:����ġ, second: �ð�
int n, k;			//������ġn, ������ġk
bool visited[MAX+1];		//�̹� ���� ��ġ ��Ž�� ����

int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(0);

	cin >> n >> k;
	visited[n] = true;

	q.push(make_pair(n, 0));
	while (!q.empty()) {
		int loc = q.front().first;
		int sec = q.front().second;
		if (loc == k) break;
		q.pop();
		if (loc + 1 <= MAX && visited[loc + 1] != true) {
			q.push(make_pair(loc + 1, sec + 1));
			visited[loc + 1] = true;
		}
		if (loc - 1 >= 0 && visited[loc - 1] != true) {
			q.push(make_pair(loc - 1, sec + 1));
			visited[loc - 1] = true;
		}
		if (loc * 2 <= MAX && visited[loc * 2] != true) {
			q.push(make_pair(loc * 2, sec + 1));
			visited[loc * 2] = true;
		}
	}

	cout << q.front().second << endl;

	return 0;
}
