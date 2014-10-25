#include "stdafx.h"
#include "BreedVisitor.h"


CBreedVisitor::CBreedVisitor(bool gender, std::string type)
{
	mFishGender = gender;
	mFishType = type;
}


CBreedVisitor::~CBreedVisitor()
{
}

/* 
* \brief Visit a fish to see if it is interested in breeding
* \param fish Fish that we are visiting
*/
void CBreedVisitor::VisitFish(CFish *fish)
{
	if (mIsInterested == false && fish->IsInterested() == true && fish->getGender() !=mFishGender && fish->GetType() == mFishType)
	{
		otherFish = fish;
		mIsInterested = true;
		mLocationX = fish->GetX();
		mLocationY = fish->GetY();
		
	}

}