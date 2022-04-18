#include "dllist.hpp"
#include <string>
#include <fstream>

int main() {
	std::ofstream fout("../data/output.txt");
	list<std::string> l;
	l.push_back("father1");
	l.push_back("father2");
	l.push_back("father3");
	l.push_back("father4");
	l.fprint(fout);
	pnode<std::string> item = l.front();
	while (item != 0) {
		item->set_value("mother");
		item = item->get_next();
	}
	l.fprint(fout);
	fout.close();
	return 0;
}