/**
 * \file DecorTreasureChest.h
 *
 * \author Stephan Hutecker
 *
 * \brief Class that contains our treaure chest item
 */

#pragma once
#include "Item.h"
#include "Aquarium.h"
#include <memory>
#include "ItemVisitor.h"


/** \brief Contains the treasure chest which opens and closes and releases bubbles*/
class CDecorTreasureChest : public CItem
{
public:
	/// \brief Default constructor (disabled)
	CDecorTreasureChest() = delete;

	/// \brief Copy constructor (disabled)
	CDecorTreasureChest(const CDecorTreasureChest &) = delete;

	CDecorTreasureChest(CAquarium *aquarium);

	virtual ~CDecorTreasureChest();

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	void Update(double elapsed);

	/** \brief Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor *visitor) override { visitor->VisitTreasureChest(this); }

	virtual int getValue() { return mValue; }

private:
	/// The value of the item
	int mValue = 150;
	/// we will use this to pause our animation
	int mHoldAnimation = 0;
	/// image the chest is currently on
	int mCurrentImage = 0;
	/// if the chest has reached its open position or not
	bool mHasOpened = false;
	/// Address of our aquarium
	CAquarium *mAquarium;
};

