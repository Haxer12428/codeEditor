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

std::string fsystem::regular::helpers::getName()
{
	if (!this->validate()) { msg->push(debug::error, "Failed.", "validation failed", __FILE__); return ""; }
	return this->path.filename().string();
}

void fsystem::regular::helpers::destory()
{
	delete this;
}

void fsystem::dir::helpers::destroy()
{
	delete this;
}

std::string fsystem::dir::helpers::getName()
{
	if (!this->validate()) { msg->push(debug::error, "fsystem::dir::helpers::getName -> Failed check.", "failed to validate", __FILE__); return ""; }
	return this->path.filename().string();
}

size_t fsystem::dir::helpers::getSize()
{
	if (!this->validate()) { msg->push(debug::error, "fsystem::dir::helpers::getSize -> Check failed", "failed to validate", __FILE__); return -1; }
		
	uintmax_t size = 0;
	std::vector<std::string> filePaths = fsystem::global::helpers::getFiles(this->getAllRecursivePaths());

	for (std::string path : filePaths) size += std::filesystem::file_size(path);
	return size; 
}

double_t fsystem::global::helpers::formatSizeInBytes(fsystem::global::helpers::formats format, uintmax_t bytes)
{
	return bytes / format;
}

fsystem::network::regular::regular(debug* msg)
{
	this->msg = msg;
}

void fsystem::network::regular::setUrl(std::string url)
{
	this->url = url;
	msg->push(debug::message, "Updated url", url, __FILE__);
}


bool fsystem::regular::helpers::create()
{
	if (this->validate()) { 
		msg->push(debug::warning, "fsystem::regular::helpers::create -> Failed", "exists", __FILE__); return true; 
	} this->setBuffer(std::vector<std::string>{" "});
	
	if (!this->validate()) { msg->push(debug::warning, "fsystem::regular::helpers::create -> Failed", "failed to create", __FILE__); return false; }
	return true; 
}
bool fsystem::dir::helpers::create()
{
	if (this->validate()) { 
		msg->push(debug::warning, "fsystem::dir::helpers::create -> Failed", "exists", __FILE__); return true; 
	} std::filesystem::create_directory(this->path);
	
	if (!this->validate()) {
		msg->push(debug::error, "fsystem::dir::helpers::create -> Failed", "creation failed", __FILE__); return false;
	} return true; 
}


void fsystem::regular::helpers::remove()
{
	std::filesystem::remove(this->path);
}

void fsystem::dir::helpers::removeAll()
{
	std::filesystem::remove_all(this->path);
}
