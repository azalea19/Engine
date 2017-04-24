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

string GetDirectoryFromFileName(string filename)
{
  char const* str = filename.c_str();
  int dirLength = strlen(str);

  while (dirLength > 0)
  {
    if (str[dirLength - 1] != '/' && str[dirLength - 1] != '\\')
      dirLength--;
    else
      break;
  }

  return filename.substr(0, dirLength);
}
