#include <iostream>
#include <boost/filesystem.hpp>
 
using std::cout;
using std::endl;
using std::string;

using namespace boost::filesystem;

void walk(path p) {
	if (is_regular_file(p)) {
		cout << p.filename() << endl;
		return;
	}
	for (auto entry : directory_iterator(p)) {
		walk(entry);
	}	
}

// This version is using boost::filesystem::recursive_directory_iterator
void walk2(path p) {
	for (auto entry : recursive_directory_iterator(p)) {
		if (is_regular_file(entry)) {
			cout << entry.path().filename() << endl;
		}
	}
}

int main(int argc, char* argv[]) {
	if (argc <= 1) {
		std::cerr << "Need more arguments!" << endl;
	}
	string root_dir{argv[1]};
	cout << "The root dir is " << root_dir << endl;
	
	path p {root_dir};
	
	walk(p);

	cout << "........" << endl;
	walk2(p);

	return 0;
}
