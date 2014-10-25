/**
* \file FeedFishVisitor.cpp
*
* \author Emily Klopfer
*/

#include "stdafx.h"
#include "FeedFishVisitor.h"
#include "Fish.h"

/** \brief Constructor for the CFeedFishVisitor Class **/
CFeedFishVisitor::CFeedFishVisitor()
{
}

/** \brief Destructor for the CFeedFishVisitor Class **/
CFeedFishVisitor::~CFeedFishVisitor()
{
}

/** \brief Visit a CFish object
* \param fish Fish tile we are visiting */
void CFeedFishVisitor::VisitFish(CFish *fish)
{
	//"feed" all fish setting making them not hungry and setting the time since fed to 0
	fish->Feed();
}
