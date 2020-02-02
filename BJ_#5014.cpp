#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
using namespace std;

int f, s, g, u, d;
//f:�ǹ�����, s:�ʱ���ġ, g:��ǥ��ġ
bool visit[1000001];
queue<pair<int, int>> q;

int bfs() {
	q.push(make_pair(s, 0));
	visit[s] = true;
	while (!q.empty()) {
		int cur = q.front().first;
		int cnt = q.front().second;
		q.pop();

		if (cur == g) return cnt;							//����
		if (cur + u <= f&&visit[cur + u] == false) {		//�ö� �� �ִ� ���
			q.push(make_pair(cur + u, cnt + 1));
			visit[cur + u] = true;
		}
		if (cur - d >= 0 && visit[cur - d] == false) {		//������ �� �ִ� ���
			q.push(make_pair(cur - d, cnt + 1));
			visit[cur - d] = true;
		}
	}
	return -1;												//��������
}

int main() {
	cin >> f >> s >> g >> u >> d;
	int ans = bfs();
	if (ans == -1) cout << "use the stairs" << endl;
	else cout << ans << endl;

	return 0;
}