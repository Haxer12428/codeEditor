#include "debug.h"
#include "ctime.h"

debug::debug()
{

}

void debug::setMessageState(debug::codes type, bool state)
{
	this->enabled[type] = state;
}

void debug::push(debug::codes type, std::string msg, std::string reason)
{
	this->logger[type].push_back("[" + ctime::get_system_time("%Y-%m-%d %X") +  "][" + this->emojis[type] + "] " + msg + " [" + reason + "]");
	if (this->enabled[type]) this->print(type, this->logger[type].size() - 1);
}

void debug::print(debug::codes type, size_t index)
{
	std::cout << this->logger[type][index] << std::endl;
}

bool debug::write_to_file(std::string file_path)
{
	std::fstream file;

	file.open(file_path, std::ios::out);

	if (!file.is_open()) return false;

	std::string all_logs;
	
	for (std::vector<std::string> message_type : this->logger)
	{
		for (std::string msg_to_exit : message_type)
		{
			all_logs += msg_to_exit + "\n";
		};
	}

	file << all_logs;
	file.close();
	return true;
}