#include "fsystem.h"

fsystem::regular::helpers::helpers(debug* msg)
{
	this->msg = msg;
}

std::filesystem::path fsystem::regular::helpers::getPath()
{
	return this->path;
}

bool fsystem::regular::helpers::validate()
{
	try {
		return std::filesystem::is_regular_file(this->path);
	}
	catch (std::exception& ex) { msg->push(debug::error, "fsystem::regular::helpers::validate -> Failed to validate.", ex.what()); return false; }
}

bool fsystem::regular::helpers::open(std::ios::openmode mode)
{
	try {
		this->file.open(this->path, mode); 
		return this->file.is_open();
	}
	catch (std::exception& ex) { msg->push(debug::error, "fsystem::regular::helpers::open -> Failed to open.", ex.what()); return false; }
}

bool fsystem::regular::helpers::close()
{
	if (this->file.is_open()) { msg->push(debug::warning, "fsystem::regular::helpers::close -> Failed to close.", "File is already closed."); return true; }
	file.close();
	return file.is_open();
}

std::vector<std::string> fsystem::regular::helpers::getBuffer()
{
	if (!this->open(std::ios::in)) { msg->push(debug::error, "fsystem::regular::helpers::getBuffer -> Failed to get buffer.", "Failed to open."); return std::vector<std::string>(); };

	std::vector<std::string> buffer; 
	std::string currentLine; 

	while (std::getline(this->file, currentLine))
	{
		buffer.push_back(currentLine);
	}

	this->close();
	return buffer;
}

bool fsystem::regular::helpers::setBuffer(std::vector<std::string> buffer)
{
	if (!this->open(std::ios::out)) {
		msg->push(debug::error, "fsystem::regular::helpers::setBuffer -> Failed to set buffer.", "Failed to open.");
		return false;
	}

	std::string buffer_string;
	for (std::string line : buffer)
	{
		buffer_string += line;
	}

	this->file << buffer_string;
	this->close();
	return true;
}

fsystem::dir::helpers::helpers(debug* msg)
{
	this->msg = msg; 
}