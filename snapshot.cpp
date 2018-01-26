#include "snapshot.h"
#include <string>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>

std::ostream& operator<<(std::ostream & os, const snapshot & s) {
	os << "The summary: \n"
		<< "Total line: " << s.total_line << "\n"
		<< "Total comment line: " << s.total_comment << "\n"
		<< "Total file number: " << s.total_file << "\n"
		<< std::endl;
	return os;
}

bool snapshot::is_empty_string(std::string l) {
	for (auto c : l) {
		if (!isspace(c))
			return false;
	}
	return true;
}

void snapshot::get_snapshot() {
	walk(root_dir);
}

void snapshot::walk(boost::filesystem::path p) {
	if (boost::filesystem::is_regular_file(p)) {
		// cout << p.filename() << endl;
		count_comment(p);
		total_file ++;
		return;
	}

	for (auto entry : boost::filesystem::directory_iterator(p)) {
		walk(entry);
	}
}

// This version is using boost::filesystem::recursive_directory_iterator
// void walk2(path p) {
// 	for (auto entry : recursive_directory_iterator(p)) {
// 		if (is_regular_file(entry)) {
// 			cout << entry.path().filename() << endl;
// 		}
// 	}
// }

void snapshot::count_comment(boost::filesystem::path file_path) {
	// std::string file_path(argv[1]);
	// std::string path {file_path};
	std::ifstream f(file_path.string());
	std::string line;
	int line_number {0};
	bool in_comment {false}, start_line_occupied {false};
	int total_comment_line {0}, comment_start_line {0};

	while(std::getline(f, line)) {

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

	// update the class member.
	total_comment += total_comment_line;
	// the line_number is the total number of line of this file.
	total_line += line_number;
}
