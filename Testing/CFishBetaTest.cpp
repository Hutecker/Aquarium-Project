#include "stdafx.h"
#include "CppUnitTest.h"
#include "FishBeta.h"
#include "Aquarium.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(UnitTest)
	{
	public:
		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}

		TEST_METHOD(TestCFishBetaHitTest)
		{
			// Create a fish to test
			CAquarium aquarium;
			CFishBeta fish(&aquarium);

		}

	};
}