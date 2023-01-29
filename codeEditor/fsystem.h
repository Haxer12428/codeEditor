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

			void destory();

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

			std::filesystem::path getPath()
			{
				return this->path;
			}

			std::vector<std::string> getAllRecursivePaths()
			{
				msg->push(debug::message, "fsystem::dir::helpers::getAllRecursivePaths -> Attempting", "", __FILE__);
				if (!this->validate()) { msg->push(debug::error, "fsystem::dir::helpers::getAllRecursivePaths -> Failed", "validation failed", __FILE__); return std::vector<std::string>(); }
				
				std::vector<std::string> paths;

				try {
					for (const auto& entry : std::filesystem::recursive_directory_iterator(this->path))
					{
						paths.push_back(entry.path().string());
					}
				}
				catch (std::exception& ex) { msg->push(debug::warning, "fsystem::dir::helpers::getAllRecursivePaths -> Failed to access.", ex.what(), __FILE__); }

				msg->push(debug::message, "fsystem::dir::helpers::getAllRecursivePaths -> Success", "Got " + std::to_string(paths.size()) + " paths", __FILE__);
				return paths;
			}
	
			void destroy(); 

			std::string getName();

			size_t getSize();

		private:
			debug* msg;
			std::filesystem::path path;
		};

	};

	namespace global
	{
		class helpers
		{
		public:
			enum formats
			{
				B = 8,
				KB = 8 * 1024,
				MB = 8 * 1024^2,
				GB = 8 * 1024^3,
				TB = 8 * 1024^4
			};

			static double_t formatSizeInBytes(fsystem::global::helpers::formats format, uintmax_t sizeInBytes);

			template<typename T> static std::vector<T> getFolders(std::vector<T> list, debug* msg = new debug())
			{
				if (!std::is_same<T, std::string>::value || std::is_same<T, std::filesystem::path>::value) 
				{ msg->push(debug::error, "fsystem::global::helpers::getFolders -> Check failed.", "Invaild template (std::string || std::filesystem::path)", __FILE__); return list; }
			
				try {
					std::vector<T> newList; 

					for (T path : list)
					{
						std::filesystem::path pathFixed = path; 
						if (std::filesystem::is_directory(pathFixed)) newList.push_back(path);
					}

					return newList;
				}
				catch (std::exception& ex) { msg->push(debug::error, "fsystem::global::helpers::getFolders -> Failed", ex.what(), __FILE__); return list; }
			}
			template<typename T> static std::vector<T> getFiles(std::vector<T> list, debug* msg = new debug())
			{
				if (!std::is_same<T, std::string>::value || std::is_same<T, std::filesystem::path>::value)
				{
					msg->push(debug::error, "fsystem::global::helpers::getFiles -> Failed check.", "Invaild template (std::string || std::filesystem::path)", __FILE__); return list;
				}

				try {
					std::vector<T> newList; 
					for (T path : list)
					{
						if (std::filesystem::is_regular_file(path)) newList.push_back(path);
					}

					return newList;
				}
				catch (std::exception& ex) { msg->push(debug::error, "fsystem::global::helpers::getFiles -> Failed", ex.what(), __FILE__); return list; }
			}
			
		};
	}; 

};

