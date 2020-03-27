#pragma once

#include <string>  // std::string
#include <map>     // std::map
#include <set>     // std::set
#include <ostream> // std::ostream

class Sigma {
public:
	static Sigma fromString(std::string line);
	static std::string print(const char c);

	// Printing Helpers
	static bool isLiteralChar(char c);
	static int hexValue(char c);

	// Iterator stuff
	size_t size() const;
	std::set<char>::const_iterator begin() const;
	std::set<char>::const_iterator end() const;

	// Index translation stuff
	bool hasIndex(size_t idx);
	bool hasChar(char c);
	char indexToChar(size_t idx);
	size_t charToIndex(char c);

	// Printing stuff
	friend std::ostream& operator<<(std::ostream& out, const Sigma& sigma);

private:
	// Maps elements in sigma to their indices
	std::map<char, size_t> forwardIdMap;

	// Maps indices to elements in sigma
	std::map<size_t, char> backwardIdMap;

	// Since we know from the write-up that the characters will be in ascending ASCII order, we
	// can use a set (it preserves this order)
	std::set<char> sigma;

	// I feel like this class shouldn't really be mutable, so this is private
	void addItem(char item);
};