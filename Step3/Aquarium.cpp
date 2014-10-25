/**
 * \file Aquarium.cpp
 *
 * \author Stephan Hutecker
 */

#include "stdafx.h"
#include <algorithm>
#include "Aquarium.h"
#include "XmlNode.h"
#include "DecorTreasure.h"
#include "DecorTreasureChest.h"
#include "FishBeta.h"
#include "FishBubbles.h"
#include "FishDory.h"
#include "KillDeadFish.h"

using namespace xmlnode;
using namespace Gdiplus;
using namespace std;

const int TrashCanWidth = 51;   ///< Width of our trash can image
const int TrashCanHeight = 70;  ///< Height of our trash can image

const int SellSignWidth = 51;   ///< Width of our dollar sign image
const int SellSignHeight = 70;  ///< Height of our dollar sign image
const int SellSignOffset = 75; ///< how far from the top of the screen the image is

const int NavHandWidth = 68; ///< Width of our nav hand icon
const int NavHandHeight = 59; ///< Height of our nav hand icon

const int TopOfTank = -100; ///<Y coordinate for the top of the tank

const int DirtTime = 35; ///<amount of time it takes to get dirtier
const int MinTime = 1; ///< amount of time for cleanining 

const int TextOffset = 55; ///<how far over we write the text when the trash can is active

/**
 * \brief Contructor
 */
CAquarium::CAquarium()
{
	mTrashCanActive = false;
	mBackground = unique_ptr<Gdiplus::Bitmap>(Bitmap::FromFile(L"images/backgroundW.png"));
	if (mBackground->GetLastStatus() != Ok)
	{
		AfxMessageBox(L"Failed to open images/backgroundW.png");
	}
	mTrashCan = unique_ptr<Gdiplus::Bitmap>(Bitmap::FromFile(L"images/trashcan.png"));
	mNavHand = unique_ptr<Gdiplus::Bitmap>(Bitmap::FromFile(L"images/nav1.png"));
	mNavHandActive = unique_ptr<Gdiplus::Bitmap>(Bitmap::FromFile(L"images/nav2.png"));
	mSellSign = unique_ptr<Gdiplus::Bitmap>(Bitmap::FromFile(L"images/sellsign.png"));
	mTime = 0;
}


/**
 * \brief Destructor
 */
CAquarium::~CAquarium()
{
}


/** \brief Draw the aquarium
* \param graphics The GDI+ graphics context to draw on
*/
void CAquarium::OnDraw(Gdiplus::Graphics *graphics)
{
	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 16);

	// Offset controlled here
	graphics->DrawImage(mBackground.get(), mXOffset, mYOffset,
		mBackground->GetWidth(), mBackground->GetHeight());

	for (auto item : mItems)
	{
		item->Draw(graphics);
	}

	if (mTrashCanActive)
		graphics->DrawImage(mTrashCan.get(), 0, 0, mTrashCan->GetWidth(), mTrashCan->GetHeight());

	// draws the Navigation hand image
	if (mIsScrolling)
	{
		graphics->DrawImage(mNavHandActive.get(), mWindowWidth - NavHandWidth, mWindowHeight - NavHandHeight, mNavHandActive->GetWidth(), mNavHandActive->GetHeight());
	}
	else
	{
		graphics->DrawImage(mNavHand.get(), mWindowWidth - NavHandWidth, mWindowHeight - NavHandHeight, mNavHand->GetWidth(), mNavHand->GetHeight());
	}

	// draws our dollar sign to sell
	graphics->DrawImage(mSellSign.get(), 0, SellSignOffset, mSellSign->GetWidth(), mSellSign->GetHeight());

	// Scoring moves over if the trash can is active
	SolidBrush brush(Color(250, 0, 0));
	if (mTrashCanActive)
	{
		graphics->DrawString((L"Current Money: " + to_wstring(mCurrentScore)).c_str(), -1, &font, PointF(TextOffset, 0), &brush);
	}
	else
	{
		graphics->DrawString((L"Current Money: " + to_wstring(mCurrentScore)).c_str(), -1, &font, PointF(0, 0), &brush);
	}
}

/** \brief Add an item to the aquarium
* \param item New item to add
*/
void CAquarium::Add(std::shared_ptr<CItem> item)
{
		mItems.push_back(item);
}

/** \brief Add an item to a temporary list to then add to the aquarium
* \param item New item to add
*/
void CAquarium::AddTempItem(std::shared_ptr<CItem> item)
{
	mTempItems.push_back(item);
}

/** \brief Test an x,y click location to see if it clicked
* on some item in the aquarium.
* \param x X location
* \param y Y location
* \returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<CItem> CAquarium::HitTest(int x, int y)
{
	for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
	{
		if ((*i)->HitTest(x, y))
		{
			return *i;
		}
	}

	return  nullptr;
}


/**
 * \brief Removes an item from the items vector and adds it to the front
 * \param item the item you wish to move to the front
 */
void CAquarium::MoveTofront(std::shared_ptr<CItem> item)
{
	auto loc = find(mItems.begin(), mItems.end(), item);
	if (loc != mItems.end())
	{
		mItems.erase(loc);
		mItems.push_back(item);
	}
}


/**
 * \brief Checks to see if the mouse is over the trash can
 * \param x the x coordinate of the mouse
 * \param y the y coordinate of the mouse
 * \returns True if the mouse is over the can
 */
bool CAquarium::IsOverTrashcan(int x, int y)
{
	if (!mTrashCanActive)
	{
		return false;
	}

	return x < TrashCanWidth && y < TrashCanHeight;
}

/**
* \brief Checks to see if the mouse is over the dollar sign
* \param x the x coordinate of the mouse
* \param y the y coordinate of the mouse
* \returns True if the mouse is over the can
*/
bool CAquarium::IsOverSellSign(int x, int y)
{
	return x < SellSignWidth && (y < SellSignHeight + SellSignOffset) && y > SellSignHeight;
}

/**
* \brief Checks to see if the mouse is over the nav icon
* \param x the x coordinate of the mouse
* \param y the y coordinate of the mouse
* \returns True if the mouse is over the nav icon
*/
bool CAquarium::isOverNavIcon(int x, int y)
{
	return x > (mWindowWidth - NavHandWidth) && y > (mWindowHeight - NavHandHeight);
}

/**
 * \brief Removes an item from the aquarium
 * \param item The item to remove
 */
void CAquarium::RemoveItem(std::shared_ptr<CItem> item)
{
	auto loc = find(mItems.begin(), mItems.end(), item);
	if (loc != mItems.end())
	{
		mItems.erase(loc);
	}
}

/**
* \brief Removes an item from the items vector and adds it to the front
* \param item the item you wish to move to the front
*/
void CAquarium::DeleteItem(CItem *item)
{
	for (auto loc = mItems.begin(); loc != mItems.end(); loc++)
	{
		if (loc->get() == item)
		{
			mItems.erase(loc);
			break;
		}
	}
}


/** \brief Save the aquarium as a .aqua XML file.
*
* Open an XML file and stream the aquarium data to it.
*
* \param filename The filename of the file to save the aquarium to
*/
void CAquarium::Save(const std::wstring &filename)
{
	//
	// Create an XML document
	//
	auto root = CXmlNode::CreateDocument(L"aqua");

	// Saves our current score
	auto itemNode = root->AddChild(L"score");
	itemNode->SetAttribute(L"currentscore", mCurrentScore);

	// Iterate over all items and save them
	for (auto item : mItems)
	{
		item->XmlSave(root);
	}

	try
	{
		root->Save(filename);
	}
	catch (CXmlNode::Exception ex)
	{
		AfxMessageBox(ex.Message().c_str());
	}

}

/** \brief Load the aquarium from a .aqua XML file.
*
* Opens the XML file and reads the nodes, creating items as appropriate.
*
* \param filename The filename of the file to load the aquarium from.
*/
void CAquarium::Load(const std::wstring &filename)
{
	// We surround with a try/catch to handle errors
	try
	{
		// Open the document to read
		shared_ptr<CXmlNode> root = CXmlNode::OpenDocument(filename);

		// Once we know it is open, clear the existing data
		Clear();

		//
		// Traverse the children of the root
		// node of the XML document in memory!!!!
		//
		for (auto node : root->GetChildren())
		{
			if (node->GetType() == NODE_ELEMENT && node->GetName() == L"item")
			{
				XmlItem(node);
			}
			// Used to load the score
			else if (node->GetType() == NODE_ELEMENT && node->GetName() == L"score")
			{
				wstring score = node->GetAttributeValue(L"currentscore", L"");
				wchar_t * pEnd;
				mCurrentScore = wcstol(score.c_str(), &pEnd, 10);
			}
		}
	}
	catch (CXmlNode::Exception ex)
	{
		AfxMessageBox(ex.Message().c_str());
	}
}

/**
* \brief Clear the aquarium data.
*
* Deletes all known items in the aquarium.
*/
void CAquarium::Clear()
{
	mItems.clear();
}

/**
* \brief Handle an item node.
* \param node Pointer to XML node we are handling
*/
void CAquarium::XmlItem(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	// A pointer for the item we are loading
	shared_ptr<CItem> item;

	// We have an item. What type?
	wstring type = node->GetAttributeValue(L"type", L"");
	if (type == L"beta")
	{
		item = make_shared<CFishBeta>(this);
	}
	else if (type == L"treasure-chest")
	{
		item = make_shared<CDecorTreasure>(this);
	}
	else if (type == L"dory")
	{
		item = make_shared<CFishDory>(this);
	}
	else if (type == L"bubbles")
	{
		item = make_shared<CFishBubbles>(this);
	}
	else if (type == L"treasure-chest-animation")
	{
		item = make_shared<CDecorTreasureChest>(this);
	}

	if (item != nullptr)
	{
		item->XmlLoad(node);
		Add(item);
	}
}

/** \brief Handle updates for animation
* \param elapsed The time since the last update
*/
void CAquarium::Update(double elapsed)
{
	//increments the time
	mTime += elapsed;

	for (auto item : mItems)
	{
		item->Update(elapsed);
		// delete items way above the top of the tank (bubbles)
		if (item->GetY() < TopOfTank)
		{
			mTempItemsDelete.push_back(item);
		}
	}

	// delete temp items if there are and and clear list
	if (!mTempItemsDelete.empty())
	{
		for (auto item : mTempItemsDelete)
		{
			this->RemoveItem(item);
		}
		mTempItemsDelete.clear();
	}

	// add temps items if there are any and delete them
	if (!mTempItems.empty())
	{
		for (auto item : mTempItems)
		{
			this->Add(item);
		}
		mTempItems.clear();
	}

	// sets a new image as tank becomes dirty over time
	if (mTime <= MinTime)
	{
		//image of clean tank
		mBackground = unique_ptr<Gdiplus::Bitmap>(Bitmap::FromFile(L"images/backgroundW.png"));
	}
	if (mTime >= DirtTime && mTime < DirtTime*2)
	{
		mBackground = unique_ptr<Gdiplus::Bitmap>(Bitmap::FromFile(L"images/backgroundW1.png"));
	}
	if (mTime >= DirtTime * 2 && mTime < DirtTime * 3)
	{
		mBackground = unique_ptr<Gdiplus::Bitmap>(Bitmap::FromFile(L"images/backgroundW2.png"));
	}
	if (mTime >= DirtTime * 3)
	{
		mBackground = unique_ptr<Gdiplus::Bitmap>(Bitmap::FromFile(L"images/backgroundW3.png"));
	}


	CKillDeadFish visitor;
	Accept(&visitor);

	auto dead = visitor.GetIsDead();
	for (auto fish : dead)
	{
		DeleteItem(fish);
	} 
}
