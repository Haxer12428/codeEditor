#pragma once
#include "globalinclude.h"

class debug
{
public:
	debug();

	enum codes
	{
		error = 0,
		warning = 1,
		message = 2
	};

	void setMessageState(debug::codes type, bool state);

	void push(debug::codes type, std::string message, std::string reason = "No info.", const char* filename = "?");

	std::vector<bool> enabled = { false, false, false };

	bool write_to_file(std::string file_path);

private:
	void print(debug::codes type, size_t index);
	
	std::vector<std::string> emojis = { "!", "*", "." };


	std::vector<std::vector<std::string>> logger = { {}, {}, {} };
};

