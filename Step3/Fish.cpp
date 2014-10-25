/**
 * \file Fish.cpp
 *
 * \author Stephan Hutecker
 */


#include "stdafx.h"
#include "Fish.h"
#include "Aquarium.h"
#include "BreedVisitor.h"
#include "ChildView.h"
#include "FishBeta.h"
#include "FishBubbles.h"
#include "FishDory.h"

/// The width of our background in pixels
const int BackgroundWidth = 2560;

/// The height of our background in pixels
const int BackgroundHeight = 806;

/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedX = 50;

/// Maximum speed in the Y direction in
/// in pixels per second
const double MaxSpeedY = 50;

/// Distance we want to keep from
/// the edge of the tank before
/// the fish reverses
const int EdgeTolerance = 40;

/// This will be used to make
/// bubbles swim faster
const int BubblesSpeed = 0;

/// This will be used to make
/// Beta swim slower
const int BetaSpeed = 30;

/// This will be used to make
/// dory swim really fast
const int DorySpeed = 150;

/// This will be used to 
/// multiply speed for breeding
const int BreedMultuplier = 10;

/// This will be used to make
/// calculate when fish is interested in breeding
const double InterestTimePreBreed = 100;

/// This will be used to make
/// calculate when fish is interested in breeding
const double GestatingTime = 500;

///amount of time untill the fish will become hungry
const double TimeTillHungry = 300;

///amount of time untill the fish will become dead
const double TimeTillDead = 1000;

///max age that a fish can reach to be fully grown
const double MaxAge = 5;

/// growth rate for our fish
const float GrowthRate = 0.01;

CFish::CFish(CAquarium *aquarium, const std::wstring &filename) :
CItem(aquarium, filename)
{
	mInterestTime = 0;
	mGestatingTime = 0;
	if (filename == L"images/bubbles.png")
	{
		mSpeedX = ((double)rand() / RAND_MAX) * (MaxSpeedX - BubblesSpeed);
		mSpeedY = ((double)rand() / RAND_MAX) * (MaxSpeedY - BubblesSpeed);
		mCanBreed = true;
		mIsMale = (rand() % 2 == 1);
		mIsGestating = false;
	}
	else if (filename == L"images/beta.png")
	{
		mSpeedX = ((double)rand() / RAND_MAX) * (MaxSpeedX - BetaSpeed);
		mSpeedY = ((double)rand() / RAND_MAX) * (MaxSpeedY - BetaSpeed);
		mCanBreed = true;
		mIsMale = (rand() % 2 == 1);
		mIsGestating = false;
	}
	else if (filename == L"images/dory.png")
	{
		mSpeedX = ((double)rand() / RAND_MAX) * DorySpeed;
		mSpeedY = -1*((double)rand() / RAND_MAX) * DorySpeed;
		mCanBreed = true;
		mIsMale = (rand() % 2 == 1);
		mIsGestating = false;
	}

	//sets the time since fed to none
	mTimeFeeding = 0;
}

CFish::~CFish()
{
}


/** \brief Handle updates in time of our fish
*
* This is called before we draw and allows us to
* move our fish. We add our speed times the amount
* of time that has elapsed.
* \param elapsed Time elapsed since the class call
*/
void CFish::Update(double elapsed)
{
	SetLocation(GetX() + mSpeedX * elapsed,
		GetY() + mSpeedY * elapsed);


	int reverseAtXLocation = BackgroundWidth - EdgeTolerance - (GetImageWidth() / 2);
	int reverseAtStart = BackgroundWidth - reverseAtXLocation;

	int HitTopYLocation = BackgroundHeight - 2 * EdgeTolerance - (GetImageHeight() / 2);
	int HitBottomYLocation = BackgroundHeight  - EdgeTolerance - HitTopYLocation;


	//Fish logic to stay inbounds
	if (mSpeedX > 0 && GetX() >= reverseAtXLocation)
	{
		mSpeedX = -mSpeedX;
		SetMirror(mSpeedX < 0);
	}
	else if (mSpeedX < 0 && GetX() <= reverseAtStart)
	{
		mSpeedX = abs(mSpeedX);
		SetMirror(false);
	}
	else if (mSpeedY > 0 && GetY() >= HitTopYLocation)
	{
		mSpeedY = -mSpeedY;
	}
	else if (mSpeedY < 0 && GetY() <= HitBottomYLocation)
	{
		mSpeedY = -mSpeedY;
	}

	BreedingUpdate(elapsed);
	AgeUpdate(elapsed);	

	//increases the time used to track feeding for fish
	mTimeFeeding++;

	//adjusts the fishes condtion based on the time since they were fed
	if (mTimeFeeding < TimeTillHungry)
	{
		mIsHungry = false;
		mIsDead = false;
		this->SetNotHungryImage();
	}
	else if (mTimeFeeding >= TimeTillHungry && mTimeFeeding < (TimeTillDead))
	{
		mIsHungry = true;
		this->SetHungryImage();
	}
	else if (mTimeFeeding >= TimeTillDead)
	{
		mIsDead = true;
	}
}


/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \returns A pointer to our fish node
*/
std::shared_ptr<xmlnode::CXmlNode> CFish::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = node->AddChild(L"item");

	itemNode->SetAttribute(L"x", GetX());
	itemNode->SetAttribute(L"y", GetY());

	itemNode->SetAttribute(L"speedx", mSpeedX);
	itemNode->SetAttribute(L"speedy", mSpeedY);

	itemNode->SetAttribute(L"canBreed", mCanBreed);
	itemNode->SetAttribute(L"isInterested", mIsInterested);
	itemNode->SetAttribute(L"isMale", mIsMale);
	itemNode->SetAttribute(L"isGestating", mIsGestating);
	itemNode->SetAttribute(L"interestTime", mInterestTime);
	itemNode->SetAttribute(L"gestatingTime", mGestatingTime);

	itemNode->SetAttribute(L"feedingTime", mTimeFeeding);
	itemNode->SetAttribute(L"isHungry", mIsHungry);
	itemNode->SetAttribute(L"age", mAge);

	return itemNode;
}

/**
* brief Load the attributes for an Fish node.
*
* \param node The Xml node we are loading the item from
*/
void CFish::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	SetLocation(node->GetAttributeDoubleValue(L"x", 0), node->GetAttributeDoubleValue(L"y", 0));
	SetSpeed(node->GetAttributeDoubleValue(L"speedx", 0), node->GetAttributeDoubleValue(L"speedy", 0));
	SetBreed(node->GetAttributeDoubleValue(L"gestatingTime", 0), node->GetAttributeDoubleValue(L"interestTime", 0), 
		node->GetAttributeDoubleValue(L"isInterested", 0), node->GetAttributeDoubleValue(L"isGestating", 0), node->GetAttributeDoubleValue(L"canBreed", 0), node->GetAttributeDoubleValue(L"isMale", 0));
	SetFeeding(node->GetAttributeDoubleValue(L"feedingTime", 0), node->GetAttributeDoubleValue(L"isHungry", 0));
	SetAge(node->GetAttributeDoubleValue(L"age", 0));

}


void CFish::BreedingUpdate(double elapsed)
{
	
	CAquarium *aquarium = GetAquarium();
	//fish logic for breeding
	if (mCanBreed == true && mAge >= MaxAge)
	{
		if (mInterestTime >= InterestTimePreBreed)
		{
			mIsInterested = true;
		}
		else if (mIsGestating == false)
			mInterestTime++;
		if (mIsGestating == true)
			mGestatingTime++;

		if (mIsInterested == true)
		{
			CBreedVisitor visitor(mIsMale, GetType());
			
			aquarium->Accept(&visitor);
			if (visitor.IsInterested())
			{
				// Compute a vector from (x1,y1) to (x2,y2)
					
				double dx = visitor.GetX() - GetX();
				double dy = visitor.GetY() - GetY();				
				
				// How long is that vector?
				double len = sqrt(dx * dx + dy * dy);
				if (len > 0)
				{
					// Normalize the vector
					dx /= len;
					dy /= len;
				}

				// Update the location
				if (GetType() == "beta")
				{
					mSpeedX = dx * (MaxSpeedX - BetaSpeed) * BreedMultuplier * elapsed;
					mSpeedY = dy * (MaxSpeedY - BetaSpeed) * BreedMultuplier * elapsed;
				}

				if (GetType() == "bubbles")
				{
					mSpeedX = dx * (MaxSpeedX - BubblesSpeed) * BreedMultuplier * elapsed;
					mSpeedY = dy * (MaxSpeedY - BubblesSpeed) * BreedMultuplier * elapsed;
				}

				if (GetType() == "dory")
				{
					mSpeedX = dx * (DorySpeed - MaxSpeedX) * BreedMultuplier * elapsed;
					mSpeedY = dy * (DorySpeed - MaxSpeedY) * BreedMultuplier * elapsed;
				}

				

				// check if the visited fish overlaps this one
				if (OverlapTest(visitor.GetX(), visitor.GetY()))
				{
					if (mIsMale == 0)
					{
						mIsGestating = true;
					}
					else
					{
						visitor.SetGestating();
					}
					mIsInterested = false;
					mInterestTime = 0;
					visitor.SetUninterested();
					if (GetType() == "beta")
					{
						mSpeedX = ((double)rand() / RAND_MAX) * (MaxSpeedX - BetaSpeed);
						mSpeedY = ((double)rand() / RAND_MAX) * (MaxSpeedY - BetaSpeed);
					}
					else if (GetType() == "bubbles")
					{
						mSpeedX = ((double)rand() / RAND_MAX) * (MaxSpeedX - BubblesSpeed);
						mSpeedY = ((double)rand() / RAND_MAX) * (MaxSpeedY - BubblesSpeed);
					}
					else if (GetType() == "dory")
					{
						mSpeedX = ((double)rand() / RAND_MAX) * (DorySpeed- MaxSpeedX);
						mSpeedY = ((double)rand() / RAND_MAX) * (DorySpeed- MaxSpeedY);
					}
					
										
				}
				
			}


		}

		if (mGestatingTime >= GestatingTime)
		{
			mIsGestating = false;
			mGestatingTime = 0;
			if (GetType() == "beta")
			{
				auto fish = make_shared<CFishBeta>(aquarium);
				fish->SetLocation(GetX(), GetY());
				aquarium->AddTempItem(fish);
			}

			if (GetType() == "bubbles")
			{
				auto fish = make_shared<CFishBubbles>(aquarium);
				fish->SetLocation(GetX(), GetY());
				aquarium->AddTempItem(fish);
			}
			if (GetType() == "dory")
			{
				auto fish = make_shared<CFishDory>(aquarium);
				fish->SetLocation(GetX(), GetY());
				aquarium->AddTempItem(fish);
			}

			
		}
		if (mSpeedX < 0)
			SetMirror(true);
		if (mSpeedX > 0)
			SetMirror(false);
	}

}

/** /brief Function that "feeds" the fish*/
void CFish::Feed()
{
	//feeds the fish by setting them to not hungry and resetting the time since they were fed to 0
	mIsHungry = false;
	mTimeFeeding = 0;
}

/** /brief Function that ages the fish*/
void CFish::AgeUpdate(double elapsed)
{
	if (mAge < MaxAge)
		mAge += GrowthRate;
}