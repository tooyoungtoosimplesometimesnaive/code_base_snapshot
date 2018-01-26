#include<iostream>
#include "snapshot.h"

int main() {
	snapshot s("comment_counter_test_suite");
	s.get_snapshot();
	std::cout << s <<std::endl;
	return 0;
}
