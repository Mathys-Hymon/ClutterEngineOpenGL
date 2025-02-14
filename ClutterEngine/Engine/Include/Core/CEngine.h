#pragma once
#include <Core/CCommon.h>

namespace clt
{
	class CEngine
	{
	private:
		CEngine();
		~CEngine();

		static void Destroy();

		static CEngine* mInstance;

	public:
		CLUTTER_API static CEngine* Create();
		void Release();
	};
}