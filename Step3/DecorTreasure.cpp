/**
* \file DecorTreasure.cpp
*
* \author Stephan Hutecker
*/

#include "stdafx.h"
#include <string>
#include "DecorTreasure.h"

using namespace Gdiplus;
using namespace std;

/// filename 
const wstring DecorTreasureImageName(L"images/treasure-chest.png");

/** Constructor
* \param aquarium The aquarium this is a member of
*/
CDecorTreasure::CDecorTreasure(CAquarium *aquarium) : CItem(aquarium, DecorTreasureImageName)
{
}


/**
* \brief Destructor
*/
CDecorTreasure::~CDecorTreasure()
{
}


/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \returns a pointer to our item node
*/
std::shared_ptr<xmlnode::CXmlNode> CDecorTreasure::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CItem::XmlSave(node);

	itemNode->SetAttribute(L"type", L"treasure-chest");

	return itemNode;
}