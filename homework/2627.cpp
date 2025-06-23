#include <stdio.h>
#include <queue>
using namespace std;

int main() {
    int n, x, y, x2, y2;
    scanf("%d", &n);
    char* temp = new char[n + 1];
    bool** board = new bool*[n];
    int** dist = new int*[n];
    for (int i = 0; i < n; ++i) {
        dist[i] = new int[n]{};
        board[i] = new bool[n];
        scanf("%s", temp);
        for (int j = 0; j < n; ++j) {
            board[i][j] = temp[j] - '0';
        }
    }
    scanf("%d %d %d %d", &x, &y, &x2, &y2);
    --x; --y; --x2; --y2;

    if (x == x2 && y == y2) {
        printf("0");
        return 0;
    }

    queue<pair<int, int>> q;
    q.push(pair(x, y));

    while(!q.empty()) {
        x = q.front().first;
        y = q.front().second;
        q.pop();
        board[x][y] = 1;

        if (x != 0 && !board[x - 1][y]) {
            dist[x - 1][y] = dist[x][y] + 1;
            board[x - 1][y] = 1;
            q.push(pair(x - 1, y));
        }
        if (x != n - 1 && !board[x + 1][y]) {
            dist[x + 1][y] = dist[x][y] + 1;
            board[x + 1][y] = 1;
            q.push(pair(x + 1, y));
        }
        if (y != 0 && !board[x][y - 1]) {
            dist[x][y - 1] = dist[x][y] + 1;
            board[x][y - 1] = 1;
            q.push(pair(x, y - 1));
        }
        if (y != n - 1 && !board[x][y + 1]) {
            dist[x][y + 1] = dist[x][y] + 1;
            board[x][y + 1] = 1;
            q.push(pair(x, y + 1));
        }

        if (dist[x2][y2]) break;
    }

    printf("%d", dist[x2][y2] ? dist[x2][y2] : -1);
    return 0;
}