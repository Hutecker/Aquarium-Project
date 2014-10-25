/**
 * \file Bubble.h
 *
 * \author Stephan Hutecker
 *
 * \brief Bubble animation for our treasure chest
 */

#pragma once
#include "Item.h"
#include <memory>
#include "ItemVisitor.h"


/** \brief animation of bubble floating to the top of the tank from treasure chest*/
class CBubble : public CItem
{
public: 
	/// \brief Default constructor (disabled)
	CBubble() = delete;

	/// \brief Copy constructor (disabled)
	CBubble(const CBubble &) = delete;

	CBubble(CAquarium *aquarium);

	virtual ~CBubble();

	void Update(double elapsed);

	/** \brief Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor *visitor) override { visitor->VisitBubble(this); }


private:
	/// bubble speed in the Y direction
	double mSpeedY = -55;

};

