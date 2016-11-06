#include "Utility.h"
#include <sstream>

void split(const string &s, char delim, std::vector<string> &elems)
{
	std::stringstream ss(s);
	string item;
	while (getline(ss, item, delim))
	{
		elems.push_back(item);
	}
}

std::vector<string> split(const string &s, char delim)
{
	std::vector<string> elems;
	split(s, delim, elems);
	return elems;
}
