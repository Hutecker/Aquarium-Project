/**
* \file DecorTreasure.h
*
* \author Stephan Hutecker
*
* \brief Class contains a beta fish
*/

#pragma once
#include "Item.h"
#include <memory>
#include "ItemVisitor.h"


/** \brief contains information for a beta fish derived from an item*/
class CDecorTreasure : public CItem
{
public:
	/// \brief Default constructor (disabled)
	CDecorTreasure() = delete;

	/// \brief Copy constructor (disabled)
	CDecorTreasure(const CDecorTreasure &) = delete;

	/*! Constructor
	*/
	CDecorTreasure(CAquarium *aquarium);

	virtual ~CDecorTreasure();

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	/** \brief Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor *visitor) override { visitor->VisitTreasure(this); }

	virtual int getValue(){ return mValue; }

private:
	/// The value of the item
	int mValue = 110;
};


