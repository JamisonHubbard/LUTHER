#include<bits/stdc++.h>
#include "SourceFile.h"

using std::string;

int SourceFile::get() {
	int character;

	if (eofReached) {
		if (endOfFile.size() == 0) {
			character = EOF;
		}
		else {
			character = endOfFile[endOfFile.size()-1];
			endOfFile.pop_back();
		}
	}
	else {
		character = file.get();
	}

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
	string forEOF;
	
	for (int i = str.size() - 1; i >= 0; i--) {
		char character = str[i];
		if (eofReached) {
			forEOF += character;
		}
		else {
			file.putback(character);
		}
		posStack.pop_back();
		lastChars.pop_back();
	}

	if (forEOF.length() > 0) {
		for (size_t i = 0; i < forEOF.length(); ++i) {
			endOfFile.push_back(forEOF[i]);
		}
	}

	return position();
}

SourceFile::Position SourceFile::put_back(const char& c) {
	return put_back(string(1, c));
}

SourceFile::Position SourceFile::prevPosition() {
	return posStack[posStack.size()-2];
}

SourceFile::Position SourceFile::position() const {
	return posStack.back();
}

void SourceFile::backup() {
	posStack.pop_back();
}

void SourceFile::end() {
	eofReached = true;
	file.close();
}