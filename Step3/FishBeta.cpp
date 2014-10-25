/**
 * \file FishBeta.cpp
 *
 * \author Stephan Hutecker
 */

#include "stdafx.h"
#include <string>
#include "FishBeta.h"
#include "Fish.h"

using namespace Gdiplus;
using namespace std;

/// Fish filename 
const wstring FishBetaImageName(L"images/beta.png");

/// Hungry Fish filename
const wstring HungryBetaImageName(L"images/red-beta.png");


/** Constructor
* \param aquarium The aquarium this is a member of
*/
CFishBeta::CFishBeta(CAquarium *aquarium) : CFish(aquarium, FishBetaImageName)
{
}


/**
 * \brief Destructor
 */
CFishBeta::~CFishBeta()
{
}



/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \returns A pointer to the node
*/
std::shared_ptr<xmlnode::CXmlNode> CFishBeta::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CFish::XmlSave(node);

	itemNode->SetAttribute(L"type", L"beta");

	return itemNode;
}

/**
* \brief sets the image to a hungry fish (red image)
*/
void CFishBeta::SetHungryImage()
{
	this->SetImage(HungryBetaImageName);
}

/**
* \brief sets the image to a non hungry fish
*/
void CFishBeta::SetNotHungryImage()
{
	this->SetImage(FishBetaImageName);
}