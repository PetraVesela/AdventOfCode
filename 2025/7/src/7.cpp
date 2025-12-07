#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <ranges>
#include <algorithm>
#include <cmath>
#include <map>

class Manifold
{
    std::vector<std::string> m_diagram;
    int m_num_split = 0;
    std::set<int> m_beam_current_positions;
    long long m_num_timelines = 1;
    std::map <int /*last_visited_indes*/, 
              long long /*number of paths to this point*/>
        m_timelines;

public:

    Manifold(std::istream &file) {
        std::string line;
        while (std::getline(file, line)) {
            m_diagram.push_back(line);
        }
        int start_position = m_diagram[0].find('S');
        m_beam_current_positions.insert(start_position);
        m_timelines[start_position] = 1;
    };

    void print() {
        for (const auto& row : m_diagram){
            std::cout << row << "\n";
        }
    }

    void fire_beam() {
        for (int row = 1; row < m_diagram.size(); ++row) {
            std::set<int> to_erase, to_insert;
            for (auto& beam_pos : m_beam_current_positions) {
                if (m_diagram[row][beam_pos] != '^') {
                    // Shoot straight down
                    m_diagram[row][beam_pos] = '|';
                }
                else {
                    // split
                    m_num_split++;
                    // Mark the split as Activated
                    m_diagram[row][beam_pos] = 'A';
                    m_diagram[row][beam_pos - 1] = '|';
                    m_diagram[row][beam_pos + 1] = '|';
                        
                    to_insert.insert(beam_pos - 1);
                    to_insert.insert(beam_pos + 1);
                    to_erase.insert(beam_pos);
                }
            }
            for (auto& beam_pos : to_erase) {
                m_beam_current_positions.erase(beam_pos);
            }
            for (auto& beam_pos : to_insert) {
                m_beam_current_positions.insert(beam_pos);
            }
        }
    }
    void count_num_timelines() {
        for (int row_ind = 2; row_ind < m_diagram.size()-1; row_ind += 2) {
            auto row =  m_diagram[row_ind];
            for (int ch_ind = 0; ch_ind < row.size() ; ++ch_ind) {
                // Look for all activated splitters
                if (row[ch_ind] == 'A') {
                    m_timelines[ch_ind - 1] += m_timelines[ch_ind];
                    m_timelines[ch_ind + 1] += m_timelines[ch_ind];
                    m_timelines[ch_ind] = 0;
                }
            }
        }
    }

    int get_num_splits() {
        return m_num_split;
    }

    long long get_num_timelines() {
        long long sum = 0;
        for (const auto& pair : m_timelines)
            sum += pair.second;
        return sum;
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

    auto manifold = Manifold(file);
    manifold.fire_beam();   
    manifold.count_num_timelines();

    std::cout << "Number of splits: " << manifold.get_num_splits() << ".\n";
    std::cout << "Number of timelines: " << manifold.get_num_timelines() << ".\n";
    return 0;
}