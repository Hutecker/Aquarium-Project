/**
* \file KillDeadFish.h
*
* \author Emily Klopfer
*
* \brief Visitor class for deleteing dead fish.
*/

#pragma once

#include <vector>
#include "stdafx.h"
#include "ItemVisitor.h"
#include "Fish.h"

/** \brief KillDeadFish visitor base class */
class CKillDeadFish : public CItemVisitor
{
public:
	/** \brief KillDead fish constructor **/
	CKillDeadFish();

	/**\brief  KillDeadFish destructor**/
	virtual ~CKillDeadFish();

	/** \brief Visit a Fish object
	* \param fish Fish we are visiting */
	void CKillDeadFish::VisitFish(CFish *fish) override;

	/** /brief creates a vector of dead fish
	*\returns a vecotr of dead fish 
	**/
	std::vector<CFish *> GetIsDead() { return mDeadFish; }


private:
	/// a vector containing all the currently dead fish
	std::vector<CFish *> mDeadFish;
};

