/**
 * \file DecorTreasureChest.cpp
 *
 * \author Stephan Hutecker
 */

#include "stdafx.h"
#include "DecorTreasureChest.h"
#include "Bubble.h"

using namespace Gdiplus;
using namespace std;

/// filename
const wstring DecorTreasureChestImageName(L"images/chest1.png");
/// image two of the animation
const wstring DecorTreasureChestImageName2(L"images/chest2.png");
/// image three of the animation
const wstring DecorTreasureChestImageName3(L"images/chest3.png");
/// image four of the animation
const wstring DecorTreasureChestImageName4(L"images/chest4.png");
/// image five of the animation
const wstring DecorTreasureChestImageName5(L"images/chest5.png");
/// update number to start open animation
const int StartOpenAnimation = 60;
/// update number to start close animation
const int StartCloseAnimation = 90;


/** Constructor
* \param aquarium The aquarium this is a member of
*/
CDecorTreasureChest::CDecorTreasureChest(CAquarium * aquarium) : CItem(aquarium, DecorTreasureChestImageName)
{
	mAquarium = this->GetAquarium();
}

/**
* \brief Destructor
*/
CDecorTreasureChest::~CDecorTreasureChest()
{
}


/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \returns a pointer to our item node
*/
std::shared_ptr<xmlnode::CXmlNode> CDecorTreasureChest::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CItem::XmlSave(node);

	itemNode->SetAttribute(L"type", L"treasure-chest-animation");

	return itemNode;
}


/** \brief Handle updates in time of our fish
*
* This is called before we draw and allows us to
* move our chest. We add our speed times the amount
* of time that has elapsed.
* \param elapsed Time elapsed since the class call
*/
void CDecorTreasureChest::Update(double elapsed)
{ 
	mHoldAnimation++;

	//Start opening chest
	if (mCurrentImage == 0 && !mHasOpened && mHoldAnimation == StartOpenAnimation)
	{
		this->SetImage(DecorTreasureChestImageName2);
		mCurrentImage = 1;
	}
	else if (mCurrentImage == 1 && !mHasOpened)
	{
		this->SetImage(DecorTreasureChestImageName3);
		mCurrentImage = 2;
	}
	else if (mCurrentImage == 2 && !mHasOpened)
	{
		this->SetImage(DecorTreasureChestImageName4);
		mCurrentImage = 3;
	}
	else if (mCurrentImage == 3 && !mHasOpened)
	{
		this->SetImage(DecorTreasureChestImageName5);
		mCurrentImage = 4;
		mHasOpened = true;
		
		//Bubbles created here
		auto bubbles = make_shared<CBubble>(mAquarium);
		bubbles->SetLocation(this->GetX(), this->GetY());
		mAquarium->AddTempItem(bubbles);
	}

	// closing chest
	else if (mCurrentImage == 4 && mHasOpened && mHoldAnimation == StartCloseAnimation)
	{
		this->SetImage(DecorTreasureChestImageName4);
		mCurrentImage = 3;
	}
	else if (mCurrentImage == 3 && mHasOpened)
	{
		this->SetImage(DecorTreasureChestImageName3);
		mCurrentImage = 2;
	}
	else if (mCurrentImage == 2 && mHasOpened)
	{
		this->SetImage(DecorTreasureChestImageName2);
		mCurrentImage = 1;
	}
	else if (mCurrentImage == 1 && mHasOpened)
	{
		this->SetImage(DecorTreasureChestImageName);
		mCurrentImage = 0;
		mHasOpened = false;
		mHoldAnimation = 0;
	}
}