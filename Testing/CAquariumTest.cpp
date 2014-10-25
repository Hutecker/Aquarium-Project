#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>
#include "ItemVisitor.h"
#include "Aquarium.h"
#include "FishBeta.h"
#include "FishBubbles.h"
#include "FishDory.h"
#include "DecorTreasure.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Testing
{
	/** /brief test class for Item Visitor **/
	class CTestVisitor : public CItemVisitor
	{
	public:

		/*\breif visitor for fish
		*param item traveling to
		**/
		virtual void VisitFish(CFish *item) { mNumFish++; }
		/// the number of fish iterator travels to
		int   mNumFish = 0;

		/*\breif visitor for treasure
		*param item traveling to
		**/
		virtual void VisitTreasure(CDecorTreasure *item) { mNumTreasure++; }
		/// the number of treasure iterator travels to
		int   mNumTreasure = 0;

		/**
		*\brief visitor for treasure chest
		* \param item traveling to 
		*/
		virtual void VisitTreasureChest(CDecorTreasure *item) { mNumTreasureChest++; }
		/// the number of treasure-chest iterator travels to
		int   mNumTreasureChest = 0;

		/**
		*\brief visitor for bubbles
		*\param item traveling to
		*/
		virtual void VisitBubbles(CDecorTreasure *item) { mNumBubbles++; }
		/// the number of bubbles iterator travels to
		int   mNumBubbles = 0;
	};

	TEST_CLASS(CAquariumTest)
	{
	public:
		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}

		TEST_METHOD(TestCAquariumHitTest)
		{
			CAquarium aquarium;

			Assert::IsTrue(aquarium.HitTest(100, 200) == nullptr, L"Testing empty aquarium");

			shared_ptr<CFishBeta> fish1 = make_shared<CFishBeta>(&aquarium);
			fish1->SetLocation(100, 200);
			aquarium.Add(fish1);

			Assert::IsTrue(aquarium.HitTest(100, 200) == fish1, L"Testing fish at 100, 200");

			//Fish on top test
			shared_ptr<CFishBeta> fishBottom = make_shared<CFishBeta>(&aquarium);
			shared_ptr<CFishBeta> fishTop = make_shared<CFishBeta>(&aquarium);

			fishBottom->SetLocation(100, 200);
			fishTop->SetLocation(100, 200);

			aquarium.Add(fishBottom);
			aquarium.Add(fishTop);

			Assert::IsTrue(aquarium.HitTest(100, 200) == fishTop, L"Test for fish on top");

			//Test for no image, no image at 700, 700 (excluding background)
			Assert::IsTrue(aquarium.HitTest(700, 700) == nullptr, L"Test for no fish");

		}

		/** \brief Create a fish, call delete and check if it is gone*/
		TEST_METHOD(TestCAquariumClear)
		{
			CAquarium aquarium;
			shared_ptr<CFishBeta> fish = make_shared<CFishBeta>(&aquarium);
			fish->SetLocation(100, 200);
			aquarium.Add(fish);

			aquarium.Clear();

			Assert::IsTrue(aquarium.HitTest(100, 200) == nullptr, L"Testing if fish is gone at 100, 200");

		}

		/* \brief create objects, travel to them and check how many times traveled*/
		TEST_METHOD(TestCItemVisitor)
		{
			// Construct a aquarium object
			CAquarium aquarium;

			//adds a treasure decor
			shared_ptr<CDecorTreasure> treasure = make_shared<CDecorTreasure>(&aquarium);
			treasure->SetLocation(100, 200);
			aquarium.Add(treasure);

			//adds a fish 
			shared_ptr<CFishBeta> fish = make_shared<CFishBeta>(&aquarium);
			fish->SetLocation(100, 100);
			aquarium.Add(fish);

			CTestVisitor visitor;
			aquarium.Accept(&visitor);
			Assert::AreEqual(1, visitor.mNumTreasure, L"Visitor number of treasure");
			Assert::AreEqual(1, visitor.mNumFish, L"Visitor number of treasure");
		}
	};
}