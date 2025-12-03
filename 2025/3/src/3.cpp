#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#define toDigit(c) (c-'0')
using num_type = long long;
num_type fast_pow10(num_type n)
{
    static num_type pow10[12] = {
        1, 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000, 1000000000,
        10000000000, 100000000000
    };

    return pow10[n];
}

num_type get_max_joltage(std::vector<int> bank, int num_digits) {
    // Look for the highest available digit 
    int highest_digit = 9;

    while (std::find(bank.begin(), bank.end(), highest_digit) == bank.end() || 
           std::find(bank.begin(), bank.end(), highest_digit) > bank.end() - num_digits)
    {
        highest_digit--;
    }
    auto pos = std::find(bank.begin(), bank.end(), highest_digit);
    num_type max_joltage;
    if (num_digits == 1)
        return highest_digit;
    max_joltage = (fast_pow10(num_digits - 1) * highest_digit) + get_max_joltage(std::vector<int>(pos + 1, bank.end()), num_digits - 1);

    return max_joltage;

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

    // Read the input file line by line
    std::string line;
    num_type total_output_joltage = 0;
    while (std::getline(file, line)) {
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        std::vector<int> digits;
        for (char& c : line) {

            digits.push_back(toDigit(c));
        }
#ifdef PART_1
        int num_digits = 2;
#else
        int num_digits = 12;
#endif
        total_output_joltage += get_max_joltage(digits, num_digits);
    }

	std::cout << "Total output joltage: " << total_output_joltage <<"\n";
    return 0;
}