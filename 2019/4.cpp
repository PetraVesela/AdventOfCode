#include <iostream>
#include <vector>

void collect_digits(std::vector<short>& digits, unsigned long num) {
    if (num > 9) {
        collect_digits(digits, num / 10);
    }
    digits.push_back(num % 10);
}

int main(){
	long start = 123456;
	long stop = 123457;
	std::vector<short> digits;
	
	for (long int i = start; i < stop; i++){
		
		collect_digits(digits, i);
		short j = 0;
		while(digits[j] <= digits[++j])
		{
			std::cout << j << std::endl;
		}
		if (j==5)
			std::cout << "I'm here";
	}
	return 0;
}