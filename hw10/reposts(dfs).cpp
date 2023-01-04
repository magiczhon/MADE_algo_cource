#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

class Graph {
private:
    std::map<std::string, int32_t> dict_of_names;
    std::vector<std::vector<int32_t>> adjacency;
    std::vector<int32_t> color;
    int32_t current_number;

    int32_t dfs(int32_t vertice) {
        color[vertice] = 1;
        int32_t depth = 0;
        for (int32_t i : adjacency[vertice]) {
            if (color[i] == 0) {
                int32_t res = dfs(i);
                if (res > depth) {
                    depth = res;
                }
            }
        }
        return depth + 1;
    }
public:
    Graph() {
        current_number = 0;
    }

    void add_edge(std::string name1, std::string name2) {
        std::transform(name1.begin(), name1.end(), name1.begin(), tolower);
        std::transform(name2.begin(), name2.end(), name2.begin(), tolower);
        int32_t begin, end;
        if (dict_of_names.find(name2) == dict_of_names.end()) {
            dict_of_names.insert(std::make_pair(name2, current_number));
            begin = current_number;
            ++current_number;
            adjacency.emplace_back();
            color.push_back(0);
        }
        else {
            begin = dict_of_names.find(name2)->second;
        }
        if (dict_of_names.find(name1) == dict_of_names.end()) {
            dict_of_names.insert(std::make_pair(name1, current_number));
            end = current_number;
            ++current_number;
            adjacency.emplace_back();
            color.push_back(0);
        }
        else {
            end = dict_of_names.find(name1)->second;
        }
        adjacency[begin].push_back(end);
    }

    int32_t max_depth() {
        return dfs(0);
    }
};

int32_t main()
{
    int32_t n;
    std::string name1, name2, reposted;
    Graph graph;
    std::cin >> n;
    for (int32_t i = 0; i < n; i++) {
        std::cin >> name1 >> reposted >> name2;
        graph.add_edge(name1, name2);
    }
    std::cout << graph.max_depth();
    return 0;
}