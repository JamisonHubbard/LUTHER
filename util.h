#ifndef UTIL_H
#define UTIL_H

#include <vector>  // std::vector
#include <sstream> // std::stringstream
#include <string>  // std::string
#ifndef _MSC_VER
#include <locale>  // std::locale
#endif

namespace util {
	using std::vector;
	using std::string;
	using std::stringstream;

	inline vector<string> split(string& str) {
		vector<string> split;
		stringstream stream(str);

		string word;
		while (stream >> word) {
			split.push_back(word);
		}

		return split;
	}

	inline bool isblank(char c) {
		// I can't get my version of g++ to support the
		// single-argument std::isblank function, only the
		// one that needs a locale, so I'm just checking if
		// I'm not on the Visual Studio compiler and using
		// that one instead.
#ifdef _MSC_VER
		return std::isblank(c);
#else
		return std::isblank(c, std::locale::classic());
#endif
	}
}

#endif // UTIL_H