/**
 * \file Fish.h
 *
 * \author Stephan Hutecker
 *
 * \brief Adds special functionality to fish items
 */

#pragma once
#include "Item.h"
#include "XmlNode.h"
#include "ItemVisitor.h"

#include <string>

using namespace std;


/** \brief Base class for a fish
* This applies to all of the fish, but not the decor
* items in the aquarium.
*/
class CFish : public CItem
{
public:
	/// \brief Default constructor (disabled)
	CFish() = delete;

	/// \brief Copy constructor (disabled)
	CFish(const CFish &) = delete;

	virtual ~CFish();

	void Update(double elapsed);

	std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node);

	/// \brief loader for our fish item
	void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);

	/// \brief setter for the speed
	/// \param x Speed in x direction
	/// \param y Speed in y direction
	void SetSpeed(double x, double y) { mSpeedX = x; mSpeedY = y; }

	/// \brief setter for the speed
	/// \param gestateTime Time till birth of fish
	/// \param interestTime Time till fish is interested in breeding
	/// \param interestStat Fish interest in breeding
	/// \param gestateStat Fish gestating status
	/// \param canBreed Fish able to breed status
	/// \param isMale Fish is male status
	void SetBreed(double gestateTime, double interestTime, bool interestStat, bool gestateStat, bool canBreed, bool isMale) 
	{
		mGestatingTime = gestateTime; mInterestTime = interestTime; mIsGestating = gestateStat; mIsInterested = interestStat; mCanBreed = canBreed; mIsMale = isMale;
	}

	/// \brief setter for the age
	/// \param age of the fish
	void SetAge(double age)
	{
		mAge = age;
	}
	/** \brief Accept a visitor
	* \param visitor The visitor we accept*/
	virtual void CFish::Accept(CItemVisitor *visitor) override { visitor->VisitFish(this); }

	/** \brief Gets whether a fish is dead
	* \returns mIsDead boolean whether fish is dead*/
	bool GetDead() { return mIsDead; }

	/// Feeds the fish
	void CFish::Feed();

	/// \brief setter for the speed
	/// \param feedingTime time since the fish has been fed
	/// \param Hungry if the fish is hungry
	void SetFeeding(double feedingTime, bool Hungry) { feedingTime = mTimeFeeding; Hungry = mIsHungry; }

	/// \brief setter for the speed
	/// \return mIsInterested Interested status
	bool IsInterested() { return mIsInterested; }

	/// \brief getter for gender
	/// \return mIsMale Fish gender
	bool getGender() { return mIsMale; }

	/// \brief setter for the speed
	/// \param elapsed elapsed time
	void BreedingUpdate(double elapsed);

	/// \brief getter for the type
	/// \return string Fish type
	virtual std::string GetType() { return ""; }

	/// \brief setter for uninterested fish
	void SetUninterested() { mIsInterested = false; mInterestTime = 0; }


	/// \brief setter for gestating fish
	void SetGestating() { mIsGestating = true;}

	/// \brief getter for the fish age
	virtual double GetAge() { return mAge; }

	/// \brief update the age of the fish if it isnt at max age
	void AgeUpdate(double elapsed);

	//
	virtual void SetHungryImage() { ; }

	///
	virtual void SetNotHungryImage() { ; }

protected:
	/** 	
	* \brief Constructor
	* \param aquarium The aquarium we are in
	* \param filename Filename for the image we use
	*/
	CFish::CFish(CAquarium *aquarium, const std::wstring &filename);

	/// Fish is Hungry
	bool mIsHungry = false;

private:
	
	/// Fish speed in the X direction
	double mSpeedX = 0;

	/// Fish speed in the Y direction
	double mSpeedY = 0;

	/// Fish ability to breed
	bool mCanBreed;

	/// Fish male or female
	bool mIsMale;

	/// Fish interested in breeding
	bool mIsInterested;

	/// Fish time before interest
	double mInterestTime;

	/// Fish is gestating
	bool mIsGestating;

	/// Fish time before interest
	double mGestatingTime;

	/// Time since last feeding
	double mTimeFeeding;

	/// Fish is dead and must be deleted
	bool mIsDead = false;

	/// Fish age
	double mAge = 1;
};

