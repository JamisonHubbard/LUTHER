#ifndef SOURCE_FILE_H
#define SOURCE_FILE_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

class SourceFile {
public:
	typedef struct {
		int line;
		int column;

		std::string str() const {
			std::string result = "";
			result += std::to_string(line);
			result += " ";
			result += std::to_string(column);
			return result;
		}

	} Position;

public:
	template<typename T>
	SourceFile(T fname) : file(fname) {
		posStack.push_back({ 1, 1 });
		eofReached = false;
	};
	
	~SourceFile() {
		file.close();
	}

	int get();

	bool get(char& c);

	bool empty();

	bool file_open() const;

	Position put_back(const std::string& str);

	Position put_back(const char& c);

	void backup();

	Position prevPosition();

	/*
		Returns the position of the next character that will be read
	*/
	Position position() const;

	void end();

private:
	std::ifstream file;
	std::vector<Position> posStack;
	std::vector<char> lastChars;
	bool eofReached;
	std::vector<char> endOfFile;
};

#endif // SOURCE_FILE_H
