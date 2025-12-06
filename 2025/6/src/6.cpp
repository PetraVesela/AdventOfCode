#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>


using num_type = long long;
using op_pair = std::pair<char, int>;

num_type solve(std::vector <num_type> operands, char op) {
    if (op == '+') {
        return std::ranges::fold_left(operands.begin(), operands.end(), 0, std::plus<int>());
    }
    return std::ranges::fold_left(operands, 1LL, std::multiplies<num_type>());
}

num_type strip_zeros_and_convert(std::string str) {
    auto end = str.find_last_not_of('0');
    return std::stoll(str.erase(end + 1));
}

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

    // Read file line by line
    std::vector<std::string> lines;
    
    std::string line;
    while (std::getline(file, line)) {

        // replace spaces with zeros
        std::replace(line.begin(), line.end(), ' ', '0');

        if (!line.contains('*'))
            lines.push_back(line);

    }
    // Read the operators first to decide the number of digits
    std::vector<op_pair> operators;
    for (int i = 0; i < line.length(); ++i) {
        if (line[i] == '*' || line[i] == '+') {
            auto next = line.find_first_not_of('0', i+1);
            operators.push_back(op_pair(line[i], 0));
        }
        else {
            operators.back().second++;
        }
    }
    // Correct the last number of digit
    operators.back().second++;

    // Now parse the operands
    std::vector<std::vector<std::string>> operand_rows;
    for (const auto& line : lines) {
        operand_rows.push_back(std::vector<std::string>());
        int it = 0;
        for (const auto& op : operators) {
            operand_rows.back().push_back(line.substr(it, op.second));
            it += op.second + 1;
        }
    }

    // Now solve the problems
    num_type grand_total = 0;
    for (int i = 0; i < operators.size(); ++i) {
        std::vector<num_type> operands;

#ifdef PART_1
        for (auto op : operand_rows) {
            operands.push_back(strip_zeros_and_convert(op[i]));
        }
#else
        // For each digit column
        for (int j = 0; j < operators[i].second; ++j) {
            std::vector <char> operand_char;
            // For each row
            for (int row = 0; row < operand_rows.size(); ++row) {
                operand_char.push_back(operand_rows[row][i][j]);
            }
            std::string str(operand_char.begin(), operand_char.end());
            operands.push_back(strip_zeros_and_convert(str));
        }

#endif
        grand_total += solve(operands, operators[i].first);
    }

   std::cout << "Grand total is: " << grand_total << ".\n";
   return 0;
    
}
