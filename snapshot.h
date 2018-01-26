#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <string>
#include <iostream>
#include <boost/filesystem.hpp>

class snapshot {
friend std::ostream& operator<<(std::ostream & os, const snapshot & s);
public:
	std::string root_dir;
	int total_line;
	int total_file;
	int total_comment;
	snapshot(std::string rd): root_dir(rd), total_line(0), total_file(0) {};
	void get_snapshot();

private:
	void walk(boost::filesystem::path p);
	void count_comment(boost::filesystem::path file_path);

	bool is_empty_string(std::string l);
};

#endif
