/**
* \file ItemVisitor.h
*
* \author Emily Klopfer
*
* \brief Item visitor base class.
*/

#pragma once

// Forward references to all tile types
class CFish;
class CDecorTreasure;
class CDecorTreasureChest;
class CBubble;

/** \brief Item visitor base class */
class CItemVisitor
{
public:
	CItemVisitor();
	virtual ~CItemVisitor();

	/** \brief Visit a Fish object
	* \param fish we are visitng in the tank */
	virtual void VisitFish(CFish *fish) {}


	/** \brief Visit a Treasure object
	* \param treasure we are visitng in the tank */
	virtual void VisitTreasure(CDecorTreasure *treasure) {}


	/** \brief Visit a TreasureChest object
	* \param treasurechest we are visitng in the tank */
	virtual void VisitTreasureChest(CDecorTreasureChest *treasurechest) {}


	/** \brief Visit a Bubble object
	* \param bubble we are visitng in the tank */
	virtual void VisitBubble(CBubble *bubble) {}

};



