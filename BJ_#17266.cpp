#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, m;
int map[100001];
int longest = 0;
int dim = 0;
bool first = true;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	memset(map, 0, sizeof(map));
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int loc;
		cin >> loc;
		map[loc] = 1;					//������ ���� 1
	}

	//���� �� ���ӵ� ��ο� �� ���� ã��
	for (int i = 0; i <= n; i++) {		//���������� Ž��
		if (map[i] == 0) {				//���ε� ���°�
			dim++;						//��ο��++
		}
		else if (map[i] == 1) {			//���ε� �ִ°�
			if (first) {					//ù ���ε�
				longest = dim;
				first = false;
			}
			else {						//�� ������ ���ε�
				if ((dim+1) % 2 == 0 && (dim+1) / 2 > longest)
					longest = (dim+1) / 2;
				else if ((dim+1) % 2 == 1 && (dim+1) / 2 + 1 > longest)
					longest = (dim+1) / 2 + 1;
			}
			dim = 0;
		}
	}
	if (dim > longest) longest = dim;
	cout << longest << endl;
}