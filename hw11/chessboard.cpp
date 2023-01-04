#include <iostream>
#include <vector>
#include <queue>

struct Cage {
    int x;
    int y;

    Cage(): x(0), y(0)
    {}

    Cage(int x, int y): x(x), y(y)
    {}

    friend Cage operator + (const Cage& left, const Cage& right) {
        return {left.x + right.x, left.y + right.y};
    }

    friend Cage& operator += (Cage& left, const Cage& right) {
        left.x += right.x;
        left.y += right.y;
        return left;
    }

    friend bool operator==(const Cage& left, const Cage& right) {
        return left.x == right.x and left.y == right.y;
    }

    Cage& operator=(const Cage& right) {
        if (this == &right) {
            return *this;
        }
        x = right.x;
        y = right.y;
        return *this;
    }
};

const std::vector<Cage> DX_DY {
        {1, 2},
        {2, 1},
        {2, -1},
        {1, -2},
        {-1, -2},
        {-2, -1},
        {-2, 1},
        {-1, 2}
};

void print_path(const std::vector<Cage>& p) {
    std::cout << p.size() << '\n';
    for(const auto el : p) {
        std::cout << el.x + 1 << ' ' << el.y + 1 << '\n';
    }
}

class Chessboard {
public:
    int size;
    Cage start;
    Cage target;
    std::queue<Cage> queue;
    std::vector<std::vector<std::vector<Cage>>>path;
    std::vector<std::vector<bool>> chessboard;

    Chessboard(int size, Cage start, Cage target): size(size), start(start), target(target) {
        chessboard.resize(size);
        for (int i = 0; i < size; i++) {
            chessboard[i].resize(size);
        }
        path.resize(size);
        for (int i = 0; i < size; i++) {
            path[i].resize(size);
            for (int j = 0; j < size; j++) {
                path[i][j] = std::vector{start};
            }
        }
    }

    int bfs() {
        chessboard[start.x][start.y] = true;
        queue.push(start);
        int min_len = 0;
        std::vector<Cage> min_path (1, start);
        Cage v;
        Cage cur_v;
        while(!queue.empty()) {
            v = queue.front();
            queue.pop();
            for (auto const d : DX_DY) {
                cur_v = v + d;
                if (
                        0 <= cur_v.x and cur_v.x < size and
                        0 <= cur_v.y and cur_v.y < size and
                        !chessboard[cur_v.x][cur_v.y]
                ) {
                    chessboard[cur_v.x][cur_v.y] = true;
                    path[cur_v.x][cur_v.y] = path[v.x][v.y];
                    path[cur_v.x][cur_v.y].push_back(cur_v);
                    queue.push(cur_v);
                    if (cur_v.x == target.x and cur_v.y == target.y) {
                        if (min_len == 0) {
                            min_len = path[cur_v.x][cur_v.y].size();
                            min_path = path[cur_v.x][cur_v.y];
                        }
                        else if(min_len > path[cur_v.x][cur_v.y].size()) {
                            min_len = path[cur_v.x][cur_v.y].size();
                            min_path = path[cur_v.x][cur_v.y];
                        }
                    }
                }
            }
        }
        print_path(min_path);
        return 0;
    }
};

int main() {
    int N, x1, y1, x2, y2;
    std::cin >> N >> x1 >> y1 >> x2 >> y2;

    Chessboard chessboard(N, Cage(x1 - 1, y1 - 1), Cage(x2 - 1, y2 - 1));
    chessboard.bfs();

    return 0;
}
