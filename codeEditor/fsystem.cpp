#include "fsystem.h"

fsystem::regular::helpers::helpers(debug* msg)
{
	this->msg = msg;
}

template<typename T> bool fsystem::regular::helpers::setPath(T path)
{
	if (!std::is_same<T, std::string>::value || std::is_same<T, std::filesystem::path>::value)
	{
		msg->push(debug::error, "fsystem::regular::helpers::setPath -> Failed to set path.", "T must be std::string || std::filesystem");  return false;
	}
	return true;
}
