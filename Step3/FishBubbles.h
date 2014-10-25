/**
* \file FishBubbles.h
*
* \author Stephan Hutecker
*
* \brief Class contains a 'bubbles' fish
*/

#pragma once
#include "Item.h"
#include "Fish.h"
#include <memory>

/** \brief contains information for a 'bubbles' fish derived from an item*/
class CFishBubbles : public CFish
{
public:
	/// \brief Default constructor (disabled)
	CFishBubbles() = delete;

	/// \brief Copy constructor (disabled)
	CFishBubbles(const CFishBubbles &) = delete;

	/*! Constructor
	*/
	CFishBubbles(CAquarium *aquarium);

	virtual ~CFishBubbles();

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	/** /brief Visitor function for Bubbles Fish
	*\param visitor for fish
	**/
	virtual void Accept(CItemVisitor *visitor) override { visitor->VisitFish(this); }

	virtual std::string GetType() override { return "bubbles"; }

	virtual int getValue(){ return mValue; }

	void SetHungryImage();

	void SetNotHungryImage();

private:
	/// The value of the item
	int mValue = 50;
};