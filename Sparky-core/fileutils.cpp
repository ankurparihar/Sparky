#include "fileutils.h"

namespace sparky {
	std::string read_file(const char* filepath) {
		FILE* file = fopen(filepath, "r");
		fseek(file, 0, SEEK_END);
		unsigned long length = ftell(file);
		char* buffer = new char[length + 1];
		memset(buffer, 0, length + 1);
		fseek(file, 0, SEEK_SET);
		fread(buffer, length, 1, file);
		fclose(file);

		std::string result(buffer);
		delete[] buffer;
		return result;
	}
}