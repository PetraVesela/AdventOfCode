#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <numeric>
#include <unordered_set>

using num_type = long long;
class Interval
{
    num_type m_lower, m_upper;

    bool is_invalid_id(num_type id) {
        auto str = std::to_string(id);

#ifdef PART_1
        int init_length = str.length()/2;
#else
        int init_length = 1;
#endif
        for (int segment_length = init_length; segment_length <= str.length()/2; ++segment_length) {
#ifdef PART_1
            // Don't bother checking odd-length strings
            if (str.length() % 2)
                continue;
#else
            // If the string cannot be split precisely into this segment length, continue
            if (str.length() % segment_length)
                continue;
#endif            
            // Store unique segments
            std::unordered_set<std::string> substrings;

            for (int pos = 0; pos < str.length(); pos += segment_length) {
                std::string segment = str.substr(pos, segment_length);
                substrings.insert(segment);
                if (substrings.size() > 1)
                    break;
            }

            // if all the segments are the same, ID is invalid
            if (substrings.size() == 1)
                return true;

        }
        return false;
    }

public:
    Interval(num_type lower, num_type upper) {
        m_lower = lower;
        m_upper = upper;
    }
    std::vector<num_type>get_valid_ids() {
        std::vector <num_type> ret;
        for (num_type i = m_lower; i <= m_upper; ++i)
        {
            if (is_invalid_id(i))
            {
                ret.push_back(i);
            }

        }
        return ret;
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

    // Read single line of the input file
    std::string line;
    std::getline(file, line);

#   // Parse the input into a vector of intervals
    std::stringstream sstream(line);
    std::string segment;

    // And store the interval
    std::vector<Interval> intervals;

    while (std::getline(sstream, segment, ','))
    {
        size_t pos = segment.find('-');
        const num_type lower = std::stoll(segment.substr(0, pos));
        const num_type upper = std::stoll(segment.substr(pos + 1, segment.length()));
        intervals.push_back(Interval(lower, upper));
    }

    num_type sum_of_invalid_ids = 0;
    for (auto& interval : intervals) {
        auto invalid_ids = interval.get_valid_ids();
        sum_of_invalid_ids += std::reduce(invalid_ids.begin(), invalid_ids.end());
    }
	std::cout << "Sum of invalid IDs: " << sum_of_invalid_ids <<"\n";
    return 0;
}