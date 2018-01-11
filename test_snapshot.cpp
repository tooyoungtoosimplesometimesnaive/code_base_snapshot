#include<iostream>
#include "snapshot.h"

int main() {
	snapshot s;
	std::cout << s.total_line <<std::endl;
	std::cout << s.total_file <<std::endl;
	std::cout << "ok!"  <<std::endl;
	return 0;
}
