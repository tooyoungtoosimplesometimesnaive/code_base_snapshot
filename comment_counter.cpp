#include<iostream>
#include<fstream>

using std::string;
using std::cout;
using std::cerr;
using std::endl;

/*
This method may not be used.
*/
bool is_empty_string(string l) {
	for (auto c : l) {
		if (!isspace(c))
			return false;
	}
	return true;
}

int main(int argc, char* argv[]) {
	if (argc <= 1) {
		cerr << "Need more arguments!" << endl;
	}
	string file_path(argv[1]);
	std::ifstream f(file_path);
	string line;
	int line_number {0};
	bool in_comment {false}, start_line_occupied {false};
	int total_comment_line {0}, comment_start_line {0};

	while(std::getline(f, line)) {
		// cout << line << endl;
		line_number++;
		decltype(line.size()) i = 0;
		while (i < line.size()) {
			if (!in_comment && line[i] == '/') {
				if (i + 1 < line.size() && line[i+1] == '*') {
					in_comment = true;
					comment_start_line = line_number;
					if (!is_empty_string(line.substr(0, i))) {
						start_line_occupied = true;
					}
					i++;
				}

				else if (i + 1 < line.size() && line[i + 1] == '/') {
					if (is_empty_string(line.substr(0, i))) {
						total_comment_line += 1;
						break;
					} 
						
				}
				i++;
				continue;
			} else
			if (in_comment && line[i] == '*') {
				if (i + 1 < line.size() && line[i + 1] == '/') {
					in_comment = false;
					if (is_empty_string(line.substr(i + 2))) { // end line not occupied case
						if (start_line_occupied) {
							total_comment_line += line_number - comment_start_line;
						}
						else {
							total_comment_line += line_number - comment_start_line + 1;
						}
						break;
					}
					else {// end line occupied case
						if (start_line_occupied) {
							// if both start line and end line are occupied:
							int c = line_number == comment_start_line ? 0 : line_number - comment_start_line - 1; 
							total_comment_line += c;
						}
						else {
							total_comment_line += line_number - comment_start_line;
						}
					}
					start_line_occupied = false;
					i++;
				}
				i++;
				continue;
			}
			i++;
		}
	}
	f.close();

	// In case the code is not correct - the coder forgot to close the comment.
	if (in_comment) {
		total_comment_line += line_number - comment_start_line;
	}

	cout << "Total line number / comment line number: " << line_number << "/" << total_comment_line << endl;

	return 0;
}
