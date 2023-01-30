#pragma once
#include "globalinclude.h"
#include "debug.h"

namespace smath
{

	class random
	{
	public:
		random(debug* msg = new debug()); 

		int randomInt(int radius);

		template<typename T> std::string string(size_t lenght, const T& pattern)
		{
			if (!std::is_same<T, std::string>::value && !std::is_same<T, std::vector<std::string>>::value)
			{
				msg->push(debug::error, "smath::random::string -> Failed check", "Invaild template (std::string || std::vector<std::string>)", __FILE__); return "check debug";
			}
			std::string generated; 
			for (int l = 0; l < lenght; l++) generated += pattern[this->randomInt(pattern.size() - 1)]; 

			return generated;
		}


	private:
		debug* msg;
	};

};

