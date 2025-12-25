#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <bitset>

struct Node {
    std::string id;
    std::vector<std::string> children;
    Node(std::string id) : id(id) {};
    Node() : id("") {};
    bool operator < (const Node &other) const{
        return id < other.id;
    }
};

using Graph = std::unordered_map<std::string, Node>;
// Key in the cache is in the form "inputoutput"
using Memo = std::unordered_map<std::string, long long>;
Memo cache;

void parse_input(std::ifstream& file, Graph& connections, Graph& inverted)
{
    std::string line;
    while (std::getline(file, line)) {

        std::string id = line.substr(0, line.find(':'));
        Node nd(id);
        std::stringstream rest(line.substr(line.find(':') + 1));
        std::string child;
        while (rest >> child) {
            nd.children.emplace_back(child);
        }
        connections[nd.id] = nd;
    }
    connections["out"] = Node("out");
};

long long count_valid_paths(std::string node_id, std::string end_node_id, Graph& connections){
    long long num_paths = 0;

    if (cache.contains(node_id + end_node_id) && node_id != end_node_id) {
        return cache[node_id + end_node_id];
    }
    else if (node_id == end_node_id) {
            return num_paths + 1;
    }

    for (const auto& child : connections[node_id].children) {        
        num_paths += count_valid_paths(connections[child].id, end_node_id, connections);
    }

    cache[node_id + end_node_id] = num_paths;
    return num_paths;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    const std::string filename = argv[1];

    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Failed to open file: " << filename << '\n';
        return 1;
    }

    Graph connections;
    Graph inverted;
    parse_input(file, connections, inverted);

    // Part 1
   
    const std::string start = "you";
    int num_paths = count_valid_paths("you", "out", connections);
    std::cout << "Number of unique paths: " << num_paths << ".\n";
    
    // Part 2
    long long num_valid_paths = count_valid_paths("svr", "fft", connections);
    num_valid_paths *= count_valid_paths("fft", "dac", connections);
    num_valid_paths *= count_valid_paths("dac", "out", connections);

    std::cout << "Number of valid paths: " << num_valid_paths << ".\n";

    return 0;
}