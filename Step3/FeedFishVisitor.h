/**
* \file FeedFishVisitor.h
*
* \author Emily Klopfer
*
* \brief Visits each fish object and "feeds" it
*/

#pragma once

#include "ItemVisitor.h"

/** \brief contains the vistor that travels to each fish and "feeds" it*/
class CFeedFishVisitor : public CItemVisitor
{
public:
	/// Constrctor for the FeedFishVisitor
	CFeedFishVisitor();
	/// Destructor for the FeedFishVisitor
	virtual ~CFeedFishVisitor();

	//Visit a CFish object
	virtual void VisitFish(CFish *fish) override;

};

