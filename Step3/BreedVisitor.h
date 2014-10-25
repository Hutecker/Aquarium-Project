/**
* \file BreedVisitor.h
*
* \author Patrick Williams
*
* \brief Visitor that calls breeding info
*
*/

#pragma once
#include "ItemVisitor.h"
#include "Fish.h"


/** \brief Visits each fish and performs breeding duties*/
class CBreedVisitor :
	public CItemVisitor
{
public:
	/**
	* \brief Constructor for our visitor
	* \param gender passed gender of fish
	* \param type Type of fish that constructs vistor
	*/
	CBreedVisitor(bool gender, std::string type);
	virtual ~CBreedVisitor();

	virtual void VisitFish(CFish *fish);

	/**
	* \brief Get the type of fish in visitor
	* \return string fish type represented in string
	*/
	std::string GetType() { return mFishType; }

	/**
	* \brief See if visited fish is interested
	* \return bool Return interested status
	*/
	bool IsInterested() { return mIsInterested; }

	/**
	* \brief Get the x location of visited fish
	* \return int X location
	*/
	int GetX() { return mLocationX; }

	/**
	* \brief Get the y location of visited fish
	* \return int Y location
	*/
	int GetY() { return mLocationY; }

	/**
	* \brief set fish to uninterested
	*/
	void SetUninterested() { otherFish->SetUninterested(); }

	/**
	* \brief set fish to gestating
	*/
	void SetGestating() { otherFish->SetGestating(); }

private:
	CFish * otherFish;					///< fish that we are visiting, this is used to set bools and is not accesible by outside classes.
	bool mIsInterested = false;			///< Visited fish interest in breeding
	bool mFishGender;					///< Visited fish gender
	int mLocationX;						///< Visited fish location X
	int  mLocationY;					///<Visited fish Y location
	std::string mFishType;				///<Visited fish type

};

