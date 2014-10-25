/**
 * \file Bubble.cpp
 *
 * \author Stephan Hutecker
 */

#include "stdafx.h"
#include "Bubble.h"

using namespace Gdiplus;
using namespace std;

/// filename
const wstring BubbleImageName(L"images/airbubbles.png");


/** Constructor
* \param aquarium The aquarium this is a member of
*/
CBubble::CBubble(CAquarium * aquarium) : CItem(aquarium, BubbleImageName)
{
}


/**
* \brief Destructor
*/
CBubble::~CBubble()
{
}

/** \brief Handle updates in time of our fish
*
* This is called before we draw and allows us to
* move our bubble. We add our speed times the amount
* of time that has elapsed.
* \param elapsed Time elapsed since the class call
*/
void CBubble::Update(double elapsed)
{
	SetLocation(this->GetX(), GetY() + mSpeedY * elapsed);
}