#include <fstream>
#include <iostream>
#include <string>

int get_in_range(int num, int range, int *num_zero_crossings)
{
    while (num < 0) {
        num += range;
#ifdef PART_2
        (*num_zero_crossings)++;
#endif
    }

    while (num > (range - 1)) {
        num -= range;
#ifdef PART_2
        if (num != 0)
            (*num_zero_crossings)++;
#endif
    }

    return num;
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

    std::string line;
	int num_zero_crossings = 0;
	int position = 50;
    const int range = 100;

    while (std::getline(file, line)) {

		int num = std::stoi(line.substr(1));
        if (line[0] == 'R') {

            position += num;

		} else if (line[0] == 'L') {
#ifdef PART_2
            // If we start at 0 and move left, we don't count this as a zero crossing.
            if (position == 0)
                num_zero_crossings--;
#endif // PART_2

            position -= num;
		}

        position = get_in_range(position, range, &num_zero_crossings);

		if (position == 0)
			num_zero_crossings++;
	}

	std::cout << "Password is: " << num_zero_crossings <<"\n";
    return 0;
}
