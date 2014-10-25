/**
 * \file FishDory.h
 *
 * \author Stephan Hutecker
 *
 * \brief Class contains a Dory fish 
 */

#pragma once
#include "Item.h"
#include "Fish.h"
#include <memory>

/** \brief contains information for a Dory fish derived from an item*/
class CFishDory : public CFish
{
public:
	/// \brief Default constructor (disabled)
	CFishDory() = delete;

	/// \brief Copy constructor (disabled)
	CFishDory(const CFishDory &) = delete;

	/*! Constructor
	*/
	CFishDory(CAquarium *aquarium);

	virtual ~CFishDory();

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	/** /brief Visitor function for Dory Fish
	*\param visitor for fish
	**/
	virtual void Accept(CItemVisitor *visitor) override { visitor->VisitFish(this); }

	virtual std::string GetType() override { return "dory"; }

	virtual int getValue(){ return mValue; }

	void SetHungryImage();

	void SetNotHungryImage();

private:
	/// The value of the item
	int mValue = 70;
};

