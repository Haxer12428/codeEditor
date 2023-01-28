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

			template<typename T> bool setPath(T path);

		private:

			debug* msg;
		};

	};

	namespace dir
	{

	};

};

