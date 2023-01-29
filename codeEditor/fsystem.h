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

			std::string getName();

		private:

			std::fstream file;

			debug* msg;
			std::filesystem::path path; 
		};

	};

	namespace dir
	{

		class helpers
		{
		public:

			helpers(debug* msg = new debug());

			template<typename T> bool setPath(T path)
			{
				if (!std::is_same<T, std::string>::value || std::is_same<T, std::filesystem::path>::value)
				{
					msg->push(debug::error, "fsystem::dir::helpers::setPath -> Failed", "Invaild template. (std::string | std::filesystem::path)", __FILE__); return false;
				}
				this->path = path; return true; 
			}

			bool validate()
			{
				try {
					return std::filesystem::is_directory(this->path);
				}
				catch (std::exception& ex) { msg->push(debug::warning, "fsystem::dir::helpers::validate -> Validation failed.", ex.what(), __FILE__); return false; }
			}

			std::vector<std::string> getPaths()
			{
				if (!this->validate()) { msg->push(debug::error, "fsystem::dir::helpers::getPaths -> Failed.", "validation failed", __FILE__); return std::vector<std::string>(); }
				
				std::vector<std::string> paths; 
				try {
					for (const auto& entry : std::filesystem::directory_iterator(this->path))
					{
						paths.push_back(entry.path().string());
					}
				}
				catch (std::exception& ex) { msg->push(debug::warning, "fsystem::dir::helpers::getPaths -> Failed to access.", ex.what(), __FILE__); }

				return paths;
			}

		private:
			debug* msg;
			std::filesystem::path path;
		};

	};

};

