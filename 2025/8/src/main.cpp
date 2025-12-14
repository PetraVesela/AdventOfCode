#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <map>
#include <set>


using num_type = long long;

struct Junction
{
    num_type m_x;
    num_type m_y;
    num_type m_z;


    Junction(num_type x, num_type y, num_type z) {
        m_x = x;
        m_y = y;
        m_z = z;
    }
    double get_distance(const auto & other) const {
        
        return sqrt( 
                (other.m_x - m_x) * (other.m_x - m_x) +
                (other.m_y - m_y) * (other.m_y - m_y) +
                (other.m_z - m_z) * (other.m_z - m_z) );
    }

    auto operator<=>(const Junction&) const = default;
};

struct Circuit {
    std::set<Junction> m_connected_junctions;

    Circuit(const Junction& a)
    {
        m_connected_junctions.insert(a);
    }
    Circuit(const Junction& a, const Junction& b)
    {
        m_connected_junctions.insert(a);
        m_connected_junctions.insert(b);
    }
    Circuit(num_type x, num_type y, num_type z) {
        m_connected_junctions.insert({ x, y, z });
    }

    bool contains(const Junction& junc) const {
        return m_connected_junctions.contains(junc);
    };

    void merge(Circuit &other) {
        m_connected_junctions.merge(other.m_connected_junctions);
    }

    size_t size() const {
        return m_connected_junctions.size();
    }

    bool operator < (const Circuit& other) const {
        if (m_connected_junctions.size() == other.m_connected_junctions.size())
            return *m_connected_junctions.begin() < *other.m_connected_junctions.begin();
        return m_connected_junctions.size() < other.m_connected_junctions.size();
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    const std::string filename = argv[1];

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << '\n';
        return 1;
    }

    // Parse the input file
    std::string line;
    std::vector<Circuit> circuits;
    while (std::getline(file, line)) {
        std::stringstream sstream(line);
        std::string x;
        std::string y;
        std::string z;
        std::getline(sstream, x, ',');
        std::getline(sstream, y, ',');
        std::getline(sstream, z, ',');
        circuits.push_back({ std::stoll(x), std::stoll(y), std::stoll(z)});
    }

    // Collect the distances between junctions
    std::map<double, std::pair<Junction, Junction>> distances;
    for (auto it_first = circuits.begin(); it_first != circuits.end(); ++it_first) {
        auto first = *it_first->m_connected_junctions.begin();
        for (auto it_second = std::next(it_first, 1); it_second != circuits.end(); ++it_second) {
            auto second = *it_second->m_connected_junctions.begin();
            distances.insert({first.get_distance(second), {first, second}});
        }
    }
    
    // Make connections
#ifdef SHORT_INPUT
    int num_connections = 10;
#elif PART_2
    int num_connections = distances.size();
#else
    int num_connections = 1000;
#endif

    std::set<Junction> all_connected_junctions;
    auto it = distances.begin();
    for (int c = 0; c < num_connections; ++c) {
        std::pair<Junction, Junction> closest_pair = (it++)->second;
        Junction first = closest_pair.first;
        Junction second = closest_pair.second;
        
        // Find the circuits that contain the first and second junctions
        int ind_first = -1;
        int ind_second = -1;
        for (int i = 0; i < circuits.size(); ++i) {
            if (circuits[i].contains(first) && !circuits[i].contains(second))
                ind_first = i;
            if (circuits[i].contains(second))
                ind_second = i;
        }
        // Merge
        if (ind_first != -1) {
            circuits[ind_first].merge(circuits[ind_second]);
            circuits.erase(circuits.begin() + ind_second);
        }
        if (circuits.size() == 1) {
            std::cout << "Product of X coordinates: " << first.m_x * second.m_x << ".\n";
            break;
        }

    }

    std::sort(circuits.begin(), circuits.end());

    size_t rest = 1;

    for (int i = 1; i < 4; ++i) {
        rest *= circuits[circuits.size()-i].size();
    }

    std::cout << "Product of circuit sizes: " << rest << ".\n";
    return 0;
}