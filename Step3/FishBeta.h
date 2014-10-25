/**
 * \file FishBeta.h
 *
 * \author Stephan Hutecker
 *
 * \brief Class contains a beta fish 
 */

#pragma once
#include "Item.h"
#include "Fish.h"
#include <memory>

/** \brief contains information for a beta fish derived from an item*/
class CFishBeta : public CFish
{
public:
	/// \brief Default constructor (disabled)
	CFishBeta() = delete;

	/// \brief Copy constructor (disabled)
	CFishBeta(const CFishBeta &) = delete;

	/*! Constructor
	*/
	CFishBeta(CAquarium *aquarium);

	virtual ~CFishBeta();

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	/** Vistor function for Beta Fish 
	*\param visitor for fish 
	**/
	virtual void Accept(CItemVisitor *visitor) override { visitor->VisitFish(this); }

	virtual std::string GetType() override { return "beta"; }

	virtual int getValue(){ return mValue; }

	void SetHungryImage();

	void SetNotHungryImage();

private:
	/// The value of the item
	int mValue = 20;

};

