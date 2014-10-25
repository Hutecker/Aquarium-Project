/**
* \file FishBubbles.cpp
*
* \author Stephan Hutecker
*/

#include "stdafx.h"
#include <string>
#include "FishBubbles.h"

using namespace Gdiplus;
using namespace std;

/// Fish filename 
const wstring FishBubblesImageName(L"images/bubbles.png");

/// Hungry Fish filename
const wstring HungryBubblesImageName(L"images/red-bubbles.png");

/** Constructor
* \param aquarium The aquarium this is a member of
*/
CFishBubbles::CFishBubbles(CAquarium *aquarium) : CFish(aquarium, FishBubblesImageName)
{
}


/**
* \brief Destructor
*/
CFishBubbles::~CFishBubbles()
{
}


/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \returns A pointer to the node
*/
std::shared_ptr<xmlnode::CXmlNode> CFishBubbles::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CFish::XmlSave(node);

	itemNode->SetAttribute(L"type", L"bubbles");

	return itemNode;
}

/**
* \brief sets the image to a hungry fish (red image)
*/
void CFishBubbles::SetHungryImage()
{
	this->SetImage(HungryBubblesImageName);
}

/**
* \brief sets the image to a non hungry fish
*/
void CFishBubbles::SetNotHungryImage()
{
	this->SetImage(FishBubblesImageName);
}