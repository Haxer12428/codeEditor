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



private:
	
	std::vector<bool> enabled = { false, false, false };
	std::vector<std::string> emojis = { "!", "*", "." };

};

