/**
 * \file Item.h
 *
 * \author Stephan Hutecker
 *
 * \brief Hold information on an item that will be inside our aquarium
 *
 * Holds and item in our aquarium
 */


#pragma once

#include <memory>
#include <string>
#include "XmlNode.h"
#include "ItemVisitor.h"

class CAquarium;

/** \brief Holds an item which is in our aquarium*/
class CItem
{
public:
	/// \brief Default constructor (disabled)
	CItem() = delete;

	/// \brief Copy constructor (disabled)
	CItem(const CItem &) = delete;

	virtual ~CItem();

	/** The X location of the item
	* \returns X location in pixels */
	double GetX() const { return mX; }

	/** The Y location of the item
	* \returns Y location in pixels */
	double GetY() const { return mY; }

	/// Set the item location
	/// \param x X location
	/// \param y Y location
	void SetLocation(double x, double y) { mX = x; mY = y; }

	//! Draw this item
	//! \param graphics Device context to draw on
	virtual void Draw(Gdiplus::Graphics *graphics);

	/** \brief Test this item to see if it has been clicked on
	* \param x X location on the aquarium to test
	* \param y Y location on the aquarium to test
	* \return true if clicked on */
	virtual bool HitTest(int x, int y);

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node);

	virtual void CItem::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);

	/// \brief Handle updates for animation
	/// \param elapsed The time since the last update
	virtual void Update(double elapsed) {}

	/// \brief Get the aquarium this item is in
	/// \returns Aquarium pointer
	CAquarium *GetAquarium() { return mAquarium; }

	/// \brief Set the mirror status
	/// \param m New mirror flag
	void SetMirror(bool m) { mMirror = m; }

	/// \brief get the image width
	int GetImageWidth() { return mItemImage->GetWidth(); }

	/// \brief get the image hieght
	int GetImageHeight() { return mItemImage->GetHeight(); }

	/// \brief set the item image, used for changing images such as the treasure chest
	/// \param filename The name of the file of the image we want
	void SetImage(const std::wstring &filename) { mItemImage = std::unique_ptr<Gdiplus::Bitmap>(Gdiplus::Bitmap::FromFile(filename.c_str())); }

	//std::unique_ptr<Gdiplus::Bitmap> GetImage() { return mItemImage->; }

	/** \brief Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor *visitor) = 0;

	/**
	* \brief Test if fish is overlapping another, this doesnt take into account the displacement of background
	* \return bool Return true if fish position is over another fish
	* \param x Xposition of fish
	* \param y YPosition of fish
	*/
	bool OverlapTest(int x, int y);

	virtual int getValue() { return 0; }

	/// \brief getter for the item age, all items return 0 if not fish
	virtual double GetAge() { return mItemAge; }

protected:
	CItem(CAquarium *aquarium, const std::wstring &filename);

private:
	/// The aquarium this item is contained in
	CAquarium   *mAquarium;

	// Item location in the aquarium
	double  mX = 0;     ///< X location for the center of the item
	double  mY = 0;     ///< Y location for the center of the item


	///pointer to the image of the fish
	std::unique_ptr<Gdiplus::Bitmap> mItemImage;

	/// True mirrors the fish image
	bool mMirror = false;   

	/// age of items set to max since decor items and such do not age
	double mItemAge = 5;
};

