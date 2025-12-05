#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <numeric>
#include <cassert>
#include <algorithm>

using num_type = long long;
class Interval
{
    num_type m_lower, m_upper = 0;
public:

    Interval(num_type lower, num_type upper) {
        m_lower = lower;
        m_upper = upper;
        assert(m_upper >= m_lower);
    }
    bool contains(num_type num) {
        return (num >= m_lower) && (num <= m_upper);
    }

    num_type overlap_length(const Interval& other) {
        num_type smaller_upper = (this->m_upper < other.m_upper) ? this->m_upper : other.m_upper;
        num_type bigger_lower = (this->m_lower > other.m_lower) ? this->m_lower : other.m_lower;

        if (smaller_upper >= bigger_lower)
        {
            // overlaps
            return smaller_upper - bigger_lower + 1;
        }
        return 0;
    }
    Interval merge(const auto& other) {
        num_type smaller_lower = (this->m_lower < other.m_lower) ? this->m_lower : other.m_lower;
        num_type bigger_upper  = (this->m_upper > other.m_upper) ? this->m_upper : other.m_upper; 
        return Interval(smaller_lower, bigger_upper);

    }
    num_type length() const {
        return m_upper - m_lower + 1;
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

    // Read file line by line
    // First the intervals
    std::vector<Interval> intervals;
    std::string line;
    while (std::getline(file, line)) {
        if (line.length() < 2)
            // Found the empty line
            break;
        size_t pos = line.find('-');
        const num_type lower = std::stoll(line.substr(0, pos));
        const num_type upper = std::stoll(line.substr(pos + 1, line.length()));
        intervals.push_back(Interval(lower, upper));
    }

    // then the ingredient IDs
    std::vector <num_type> ingredients;
    num_type num_fresh_ingredients = 0;
    while (std::getline(file, line)) {
        ingredients.push_back(std::stoll(line));
    }

    // Now count the fresh ones
    for (const auto& ingredient : ingredients) {
        // Check if the ID is fresh
        for (auto& interval : intervals) {
            if (interval.contains(ingredient)) {
                num_fresh_ingredients++;
                break;
            }              
        }
    }
    std::cout << "Number of fresh ingredients: " << num_fresh_ingredients << "\n";

    // Part 2
    // First prune
    for (auto it_first = intervals.begin(); it_first != intervals.end(); ++it_first) {
        auto& first = *it_first;
        auto it_second = it_first + 1;
        while (it_second != intervals.end())
        {
            if (0 != first.overlap_length(*it_second)) {
                
                first = first.merge(*it_second);
                it_second = intervals.erase(it_second);
            }
            else ++it_second;
        }
    }
  
    // Then evaluate
    num_type total_num_fresh_ingredients = 0;
    int num_overlaps = 0;
    for (auto it_first = intervals.begin(); it_first != intervals.end(); ++it_first)
    {
        auto& first = *it_first;
        total_num_fresh_ingredients += first.length();

        for (auto& second : std::vector<Interval>(it_first + 1, intervals.end())) {
            auto overlap = first.overlap_length(second);
            total_num_fresh_ingredients -= overlap;
        }
    }
    std::cout << "Total number of fresh ingredients: " << total_num_fresh_ingredients << ".\n";
    return 0;
    
}
