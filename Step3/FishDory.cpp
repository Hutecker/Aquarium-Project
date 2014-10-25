/**
* \file FishDory.cpp
*
* \author Stephan Hutecker
*/

#include "stdafx.h"
#include <string>
#include "FishDory.h"

using namespace Gdiplus;
using namespace std;

/// Fish filename 
const wstring FishDoryImageName(L"images/dory.png");

/// Hungry Fish filename
const wstring HungryDoryImageName(L"images/red-dory.png");

/** Constructor
* \param aquarium The aquarium this is a member of
*/
CFishDory::CFishDory(CAquarium *aquarium) : CFish(aquarium, FishDoryImageName)
{
}

/**
* \brief Destructor
*/
CFishDory::~CFishDory()
{
}

/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \returns A pointer to the node
*/
std::shared_ptr<xmlnode::CXmlNode> CFishDory::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CFish::XmlSave(node);

	itemNode->SetAttribute(L"type", L"dory");

	return itemNode;
}

/**
* \brief sets the image to a hungry fish (red image)
*/
void CFishDory::SetHungryImage()
{
	this->SetImage(HungryDoryImageName);
}

/**
* \brief sets the image to a non hungry fish
*/
void CFishDory::SetNotHungryImage()
{
	this->SetImage(FishDoryImageName);
}