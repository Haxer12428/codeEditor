#include "fsystem.h"
#include "smath.h"

fsystem::cache::basic::file::file(fsystem::cache::basic::dir* dir, debug* msg)
{
	this->msg = msg; 
	this->dirPath = dir->getPath();
}

std::filesystem::path fsystem::cache::basic::file::getPath()
{
	return this->path; 
}

bool fsystem::cache::basic::file::create()
{
	std::string path;
	smath::random* rmath = new smath::random();
	
	for (int attempt = 1; attempt <= 100; attempt++)
	{
		std::string name = rmath->string<std::vector<std::string>>(6, { "ab", "cd", "ef", "gh", "kl", "zx", "cv", "12", "48", "xa", "53" });
		fsystem::regular::helpers* file = new fsystem::regular::helpers(this->msg);

		path = this->dirPath.string() + "/" + name + ".txt"; 
		file->setPath(path);

		if (!file->validate()) {
			file->create();
			this->path = path; 
			file->destory();
			return true; 
		}

		file->destory();
	}

	return false; 
}

void fsystem::cache::basic::file::destory()
{
	fsystem::regular::helpers* file = new fsystem::regular::helpers(this->msg);
	file->setPath<std::string>(this->path.string());
	file->remove();
	file->destory();
	delete this;
}