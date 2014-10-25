/**
* \file KillFish.cpp
*
* \author Emily Klopfer
*/

#include "stdafx.h"
#include "KillDeadFish.h"
#include "Fish.h"

/** constructor for the ItemVisitor Class **/
CKillDeadFish::CKillDeadFish()
{
}

/** destructor for the ItemVisitor Class **/
CKillDeadFish::~CKillDeadFish()
{
}

/** /brief visits each fish and asks if it is dead
*
* creates a vector of all the dead fish
**/
void CKillDeadFish::VisitFish(CFish *fish)
{
	if (fish->GetDead() == true)
		mDeadFish.push_back(fish);
}