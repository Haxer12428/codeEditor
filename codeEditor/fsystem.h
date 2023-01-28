#pragma once
#include "globalinclude.h"
#include "debug.h"

namespace fsystem
{

	namespace regular
	{

		class helpers
		{
		public:

			helpers(debug* msg = new debug());

			template<typename T> bool setPath(T path)
			{
				if (!std::is_same<T, std::string>::value || std::is_same<T, std::filesystem::path>::value)
				{
					msg->push(debug::error, "fsystem::regular::helpers::setPath -> Failed to set path.", "T must be std::string || std::filesystem"); return false;
				}

				this->path = path;
				return true;
			}

			std::filesystem::path getPath();

			bool validate();

			bool open(std::ios::openmode mode);
			
			std::vector<std::string> getBuffer();

			bool close();
			
			bool setBuffer(std::vector<std::string> buffer);

		private:

			std::fstream file;

			debug* msg;
			std::filesystem::path path; 
		};

	};

	namespace dir
	{

	};

};

