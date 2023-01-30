#include "fsystem.h"
#include "smath.h"

fsystem::cache::basic::dir::dir(debug* msg)
{
	this->msg = msg;
}

bool fsystem::cache::basic::dir::create(std::string p)
{
	std::vector<std::string> pattern = { "ab", "cd", "ef", "gh", "zx", "nm", "vx", "12", "34", "56", "78", "90" };
	smath::random* nRand = new smath::random();
	std::string path;

	for (int attempt = 1; attempt <= 100; attempt++)
	{
		fsystem::dir::helpers* dir = new fsystem::dir::helpers(msg); 
		dir->setPath(p + nRand->string(8, pattern));

		dir->create(); path = dir->getPath().string();
		
		if (dir->validate())
		{
			dir->destroy();
			msg->push(debug::message, "fsystem::cache::basic::dir::create -> Successfully created.", path, __FILE__); return true; 
		}

		dir->destroy();
		msg->push(debug::warning, "fsystem::cache::basic::dir::create -> Failed to create", "unknown error", __FILE__);
	}

	return false; 
}