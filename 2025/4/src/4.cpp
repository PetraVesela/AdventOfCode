#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

class CharMatrix {
private:
    std::vector<std::vector<char>> matrix;

public:
    // Load matrix from a text file
    bool load_from_file(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Cannot open file " << filename << "\n";
            return false;
        }

        matrix.clear();
        std::string line;

        while (std::getline(file, line)) {
            if (line.empty()) continue;            // skip empty lines
            matrix.emplace_back(line.begin(), line.end());
        }

        return true;
    }

    std::vector<std::pair<int, int>> get_neighbours(int r, int c, int field_size) {
        std::vector<std::pair<int, int>> neighbours = {
            {r - 1, c - 1}, {r - 1, c}, {r - 1, c + 1},
            {r,     c - 1},             {r,     c + 1},
            {r + 1, c - 1}, {r + 1, c}, {r + 1, c + 1}
        };

        std::vector<std::pair<int, int>> result;

        for (auto& nb : neighbours) {
            int nr = nb.first;
            int nc = nb.second;

            // Exclude coordinates that fall outside [0, field_size-1]
            if (nr >= 0 && nr < field_size &&
                nc >= 0 && nc < field_size)
            {
                result.push_back(nb);
            }
        }

        return result;
    }

    int get_num_accessible(bool remove_accessible) {
        int num_accessible = 0;
        for (int r = 0; r < matrix.size(); r++) {

            for (int c = 0; c < matrix[0].size(); c++) {
                // Do not bother checking empty spots
                if (matrix[r][c] != '@')
                    continue;
                //
                int neighbouring_rolls = 0;
                auto nb = get_neighbours(r, c, matrix.size());
                for (auto& nb : nb) {
                    if (matrix[nb.first][nb.second] == '@')
                        neighbouring_rolls++;
                }
                if (neighbouring_rolls < 4)
                {
                    num_accessible++;
                    // Remove the roll
                    if (remove_accessible)
                        matrix[r][c] = '.';
                }

            }
        }
        return num_accessible;
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    const std::string filename = argv[1];
    auto floor = CharMatrix();
    floor.load_from_file(filename);

    std::cout << "Number of accessible rolls: " << floor.get_num_accessible(false) <<"\n";

    int total_removed_rolls = 0;
    int single_round_removed_rolls = floor.get_num_accessible(true);
    while (0 != single_round_removed_rolls) {
        total_removed_rolls += single_round_removed_rolls;
        single_round_removed_rolls = floor.get_num_accessible(true);
    }

    std::cout << "Number of removed rolls: " << total_removed_rolls << "\n";
    return 0;
}