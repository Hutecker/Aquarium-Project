/**
 * \file Aquarium.h
 *
 * \author Stephan Hutecker
 *
 * \brief Class that holds all information on our aquarium
 *
 * Class that creates an aquarium and holds everything in our aquarium
 */



#pragma once
#include <memory>
#include <vector>
#include "Item.h"
#include "ItemVisitor.h"


/** \brief Contains everything in out aquarium*/
class CAquarium
{
public:
	CAquarium();
	virtual ~CAquarium();
	void OnDraw(Gdiplus::Graphics *graphics);
	void Add(std::shared_ptr<CItem> item);
	void AddTempItem(std::shared_ptr<CItem> item);
	std::shared_ptr<CItem> HitTest(int x, int y);
	void MoveTofront(std::shared_ptr<CItem> item);
	/** \brief setter for trashcanisactive*/
	void IsTrashActive(bool value) { mTrashCanActive = value; };
	/** \brief getter for trashcanisactive*/
	bool GetTrashActive() { return mTrashCanActive; };
	bool IsOverTrashcan(int x, int y);
	bool isOverNavIcon(int x, int y);
	bool IsOverSellSign(int x, int y);
	void RemoveItem(std::shared_ptr<CItem> item);
	void Save(const std::wstring &filename);
	void Load(const std::wstring &filename);
	void CAquarium::Clear();
	void XmlItem(const std::shared_ptr<xmlnode::CXmlNode> &node);
	void Update(double elapsed);
	void AddToScore(int x){ mCurrentScore += x; }

	void CAquarium::DeleteItem(CItem *item);

	/// Setter for Navigation active or not
	/// \param value Value you want scrolling to be
	void setNavigation(bool value) { mIsScrolling = value; }

	/// Getter for navigation active or not
	/// \returns true is scrolling is active
	bool getNavigation() { return mIsScrolling; }

	/// \brief Get the width of the aquarium
	/// \returns Aquarium width
	int GetWidth() const { return mBackground->GetWidth(); }

	/// \brief Get the height of the aquarium
	/// \returns Aquarium height
	int GetHeight() const { return mBackground->GetHeight(); }

	/// \brief set the x and y offset of the background image
	/// \param x x value of offset
	/// \param y y value of offset
	void setOffset(int x, int y) { mXOffset = x; mYOffset = y; }

	/// \brief get the x offset of the background image
	/// \returns x value of offset
	int getXOffset() { return mXOffset; }

	/// \brief get the y offset of the background image
	/// \returns y value of offset
	int getYOffset() { return mYOffset; }

	/// \brief Sets the current window size
	/// \param width Width of window
	/// \param height Height of the window
	void setWindowSize(int width, int height) { mWindowHeight = height; mWindowWidth = width; }

	/** /breif set the current time value
	* \param time Time at current
	*\returns time at current*/
	void setTime(int time) { mTime = time; }

	/** /breif Get current time 
	*\returns time at current position */
	double getTime( ) { return mTime; }

	/** \brief Accept a visitor for the collection
	* \param visitor The visitor for the collection
	*/
	void CAquarium::Accept(CItemVisitor *visitor)
	{
		for (auto item : mItems)
		{
			item->Accept(visitor);
		}
	}

	/** \brief returns the number of items in the aquarium
	*	\return int Number of items in aquarium
	*/
	int GetItemCount() { return mItems.size(); }

	/** \brief returns the score of aquarium
	*	\return int Current Score
	*/
	int GetScore() { return mCurrentScore; }

	/** \brief sets the score of aquarium
	*/
	void SubtractScore(long score) { mCurrentScore -= score; }

	/** \brief Contains iterator class for iterating through items in aquarium **/
	class Iter
	{
	public:
		/** /breif Constructor
		*\param aquarium The collection we are iterating over
		*\param pos the index
		**/
		Iter(CAquarium *aquarium, int pos) : mAquarium(aquarium), mPos(pos) {}

		/** /breif Test for end of iterator
		* \param other the thing we are comparing to
		*\returns True if this position equals not equal to the other position*/
		bool operator != (const Iter &other) const
		{
			return mPos != other.mPos;
		}

		/** /breif Get value at current position
		*\returns Value at mPos in teh collection */
		std::shared_ptr<CItem> operator *() const { return mAquarium->mItems[mPos]; }

		/** /breif Increment the iterator
		*\returns Refrence to this iterator */
		const Iter& operator++()
		{
			mPos++;
			return *this;
		}

	private:
		CAquarium *mAquarium;   ///< Collection we are iterating over
		int mPos;             ///< Position in the collection
	};

	/** \brief Get the begigning of the aquarium items collection
	* \returns iterater at first element
	**/
	Iter begin() { return Iter(this, 0); }

	/** /brief Get the end of the aquarium items collection
	* \returns  iterater one past last element
	**/
	Iter end() { return Iter(this, mItems.size()); }


private:
	/// X value of current offset
	int mXOffset = 0;
	/// Y value of current offset
	int mYOffset = 0;
	/// Background image to use
	std::unique_ptr<Gdiplus::Bitmap> mBackground; 
	/// All of the items to populate our aquarium
	std::vector<std::shared_ptr<CItem> > mItems;
	/// Trash can image
	std::unique_ptr<Gdiplus::Bitmap> mTrashCan;  
	/// Whether or not the trash can is visible
	bool mTrashCanActive;
	/// Scrolling hand image, scrolling inactive
	std::unique_ptr<Gdiplus::Bitmap> mNavHand;
	/// Scrolling hand image, scrolling active
	std::unique_ptr<Gdiplus::Bitmap> mNavHandActive;
	/// True when scrolling is active
	bool mIsScrolling = false;
	/// Window width
	int mWindowWidth = 0;
	/// Window height
	int mWindowHeight = 0;
	/// List of items we want to add after iterating
	std::vector<std::shared_ptr<CItem> > mTempItems;
	/// List of items we want to delete after iterating
	std::vector<std::shared_ptr<CItem> > mTempItemsDelete;
	/// Keeps track of the time for tank changes
	double mTime;
	/// keeps track of how dirty the tank is
	double mDirt = 0;
	/// Keeps track of the current score
	long mCurrentScore = 400;
	/// Image for our dollar sign which allows selling fish
	std::unique_ptr<Gdiplus::Bitmap> mSellSign;
};

