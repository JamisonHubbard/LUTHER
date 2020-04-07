#include "SourceFile.h"

using std::string;

int SourceFile::get() {
	int character = file.get();

	if (character == EOF) {
		return character;
	}

	Position current = position();
	if (character == '\n') {
		posStack.push_back({ current.line + 1, 1 });
	}
	else {
		posStack.push_back({ current.line, current.column + 1 });
	}
	lastChars.push_back(character);

	return character;
}

bool SourceFile::get(char& character) {
	character = get();
	return character != EOF;
}

bool SourceFile::empty() {
	return file.peek() == EOF;
}

bool SourceFile::file_open() const {
	return !!file;
}

SourceFile::Position SourceFile::put_back(const std::string& str) {
	for (int i = str.size() - 1; i >= 0; i--) {
		char character = str[i];
		file.putback(character);
		posStack.pop_back();
		lastChars.pop_back();
	}

	return position();
}

SourceFile::Position SourceFile::put_back(const char& c) {
	return put_back(string(1, c));
}

SourceFile::Position SourceFile::position() const {
	return posStack.back();
}