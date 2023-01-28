#include "debug.h"

debug::debug()
{

}

void debug::setMessageState(debug::codes type, bool state)
{
	this->enabled[type] = state;
}

void debug::push(debug::codes type, std::string msg, std::string reason)
{
	this->logger[type].push_back("[" + this->emojis[type] + "] " + msg + " [" + reason + "]");
	if (this->enabled[type]) this->print(type, this->logger[type].size() - 1);
}

void debug::print(debug::codes type, size_t index)
{
	std::cout << this->logger[type][index] << std::endl;
}