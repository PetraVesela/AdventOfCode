#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <regex>
#include <algorithm>

struct Schematic {
    int indicator = -1;
    std::vector<int> buttons;
    std::vector<int> joltage_requirements;
};

int get_minimum_number_button_presses(Schematic& s)
{
    int button_presses = 1;
    // Use a bool vector to generate combinations of increasing length
    std::vector<bool> mask(s.buttons.size(), 0);
    while (true) {
        std::sort(mask.begin(), mask.end());
        mask[0] = 1;
        std::sort(mask.begin(), mask.end());
        do {
            // Calculate XOR of the chosen buttons
            int reg = 0;
            for (std::size_t i = 0; i < mask.size(); ++i) {
                if (mask[i]) {
;                    reg ^= s.buttons[i];
                }
            }

            if (reg == s.indicator) {
                return button_presses;
            }
        } while (std::next_permutation(mask.begin(), mask.end()));
        ++button_presses;
    }
    return -1;
}

void parse_input(std::ifstream& file, std::vector<Schematic>& schematics)
{
    // Thank you, ChatGPT
    std::regex pattern(R"(\[([^\]]*)\]|\(([^)]*)\)|\{([^}]*)\})");
    std::smatch match;
    std::string line;

    while (std::getline(file, line))
    {
        Schematic s;
        auto it = line.cbegin();
        std::string binary_string;
        while (std::regex_search(it, line.cend(), match, pattern)) {
            if (match[1].matched) {
                // parse indicator
                for (const auto& c : match[1].str()) {
                    if (c == '.')
                        binary_string.append("0");
                    else
                        binary_string.append("1");
                }
                s.indicator = std::stoi(binary_string, nullptr, 2);

            }
            else if (match[2].matched) {
                std::string button = std::string(binary_string.size(), '0');

                std::istringstream ss(match[2].str());
                std::string segment;
                while (std::getline(ss, segment, ',')) {
                    int i = std::stoi(segment);
                    button[i] = '1';
                }
                s.buttons.emplace_back(std::stoi(button, nullptr, 2));
            }
                
            else if (match[3].matched)
                std::cout << "{}  -> " << match[3] << "\n";

            it = match.suffix().first;

        }
        schematics.push_back(s);
    }
};

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

    std::vector<Schematic> schematics;
    parse_input(file, schematics);
    int total_button_presses = 0;

    // Find button combinations:
    for (auto& schematic : schematics) {
        total_button_presses += get_minimum_number_button_presses(schematic);
    }
    std::cout << "Number of button presses: " << total_button_presses << ".\n";
    return 0;
}