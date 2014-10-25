/**
* \file ChildView.cpp
*
* \author Stephan Hutecker 
*/


// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include <memory>
#include <sstream>

#include "Step2.h"
#include "ChildView.h"
#include "FishBeta.h"
#include "FishBubbles.h"
#include "FishDory.h"
#include "DecorTreasure.h"
#include "DecorTreasureChest.h"
#include "KillDeadFish.h"
#include "FeedFishVisitor.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace Gdiplus;
using namespace std;

// CChildView

/// Frame duration in milliseconds
const int FrameDuration = 30;

/// Background image width
const int backgroundWidth = 2560;
/// Background image height
const int backgroundHeight = 806;

///max age for an item, to be divided
const int PointAgeDivisor = 5;

///max age for an item, to be divided
const int FishGoal = 30;

///max age for an item, to be divided
const int ScoreGoal = 1000;

/** \brief Constructor */
CChildView::CChildView()
{
	srand((unsigned int)time(nullptr));
	OnFileGoals();
}

/** \brief Destructor */
CChildView::~CChildView()
{
}



BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_ADDFISH_BETAFISH, &CChildView::OnAddfishBetafish)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_COMMAND(ID_ADDFISH_BUBBLESFISH, &CChildView::OnAddfishBubblesfish)
	ON_COMMAND(ID_ADDFISH_DORYFISH, &CChildView::OnAddfishDoryfish)
	ON_COMMAND(ID_FILE_TRASHCAN, &CChildView::OnFileTrashcan)
	ON_COMMAND(ID_ADDDECOR_TREASURECHEST, &CChildView::OnAdddecorTreasurechest)
	ON_COMMAND(ID_FILE_SAVEAS, &CChildView::OnFileSaveas)
	ON_COMMAND(ID_FILE_OPEN32778, &CChildView::OnFileOpen32778)
	ON_WM_TIMER()
	ON_COMMAND(ID_ADDDECOR_ANIMATEDTEASURECHEST, &CChildView::OnAdddecorAnimatedteasurechest)
	ON_COMMAND(ID_TANKMAINTENCE_CLEANTANK, &CChildView::OnTankmaintenceCleantank)
	ON_COMMAND(ID_TANKMAINTENCE_FEEDFISH, &CChildView::OnTankmaintenceFeedfish)
	ON_COMMAND(ID_VIEW_GOALS, &CChildView::OnFileGoals)
END_MESSAGE_MAP()



// CChildView message handlers
/** \brief This function is called before the window is created.
* \param cs A structure with the window creation parameters
* \returns TRUE
*/
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);


	return TRUE;
}

/** \brief This function is called to draw in the window.
*
* This function is called in response to a drawing message
* whenever we need to redraw the window on the screen.
* It is responsible for painting the window.
*/
void CChildView::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	// Get the size of the window
	CRect rect;
	GetClientRect(&rect);

	mAquarium.setWindowSize(rect.Width(), rect.Height());

	// Create a memory buffer
	Bitmap memory(rect.Width(), rect.Height(), PixelFormat32bppARGB);

	// And a graphics context for that buffer
	Graphics graphics(&memory);
	graphics.Clear(Color(0, 0, 0));

	mAquarium.OnDraw(&graphics);

	Graphics graphicsReal(dc.m_hDC);
	graphicsReal.DrawImage(&memory, 0, 0, rect.Width(), rect.Height());

	if (mFirstDraw)
	{
		mFirstDraw = false;
		SetTimer(1, FrameDuration, nullptr);

		/*
		* Initialize the elapsed time system
		*/
		LARGE_INTEGER time, freq;
		QueryPerformanceCounter(&time);
		QueryPerformanceFrequency(&freq);

		mLastTime = time.QuadPart;
		mTimeFreq = double(freq.QuadPart);
	}

	/*
	* Compute the elapsed time since the last draw
	*/
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	long long diff = time.QuadPart - mLastTime;
	double elapsed = double(diff) / mTimeFreq;
	mLastTime = time.QuadPart;

	mAquarium.Update(elapsed);
}

/** \brief Add Fish/Beta menu option handler
*/
void CChildView::OnAddfishBetafish()
{
	auto fish = make_shared<CFishBeta>(&mAquarium);
	fish->SetLocation(InitialX, InitialY);

	//subtracts cost of the fish from total funds
	if (mAquarium.GetScore() >= fish->getValue())
	{
		mAquarium.SubtractScore(fish->getValue());
		mAquarium.Add(fish);
	}
	else
		AfxMessageBox(L"Unable to Purchase;  Not enough Funds");

	Invalidate();
}

/** \brief Called when there is a left mouse button press
* \param nFlags Flags associated with the mouse button press
* \param point Where the button was pressed
*/
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	mMouseLocationX =  point.x - mAquariumOffsetX;
	mMouseLocationY = point.y - mAquariumOffsetY;

	mGrabbedItem = mAquarium.HitTest(point.x, point.y);
	if (mGrabbedItem != nullptr)
	{
		mAquarium.MoveTofront(mGrabbedItem);
	}
	else if (mAquarium.isOverNavIcon(point.x, point.y))
	{
		if (mAquarium.getNavigation())
		{
			mAquarium.setNavigation(false);
			Invalidate();
		}
		else
		{
			mAquarium.setNavigation(true);
			Invalidate();
		}
	}
	else
	{
		mAquariumClick = true;
	}
}

/** \brief Called when the left mouse button is released
* \param nFlags Flags associated with the mouse button release
* \param point Where the button was pressed
*/
void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	OnMouseMove(nFlags, point);
	mMouseLocationPreviousX = point.x;
	mMouseLocationPreviousY = point.y;
}

/** \brief Called when the mouse is moved
* \param nFlags Flags associated with the mouse movement
* \param point Where the button was pressed
*/
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// See if an item is currently being moved by the mouse
	if (mGrabbedItem != nullptr)
	{
		// If an item is being moved, we only continue to 
		// move it while the left button is down.
		if (nFlags & MK_LBUTTON)
		{
			mGrabbedItem->SetLocation(point.x - mAquarium.getXOffset(), point.y - mAquarium.getYOffset());
		}
		else
		{
			// When the left button is released, we release the
			// item. if the item is over the trash can, it is deleted.
			if (mAquarium.IsOverTrashcan(point.x, point.y))
			{
				mAquarium.RemoveItem(mGrabbedItem);
				Invalidate();
			}

			// If the item is over the sell sign when it is released, it is sold
			if (mAquarium.IsOverSellSign(point.x, point.y))
			{
				mAquarium.AddToScore(int(mGrabbedItem->getValue()*(mGrabbedItem->GetAge()/PointAgeDivisor)));
				mAquarium.RemoveItem(mGrabbedItem);
				Invalidate();
			}

			mGrabbedItem = nullptr;
		}

		// Force the screen to redraw
		Invalidate();

	}
	// moves the aquarium/ scrolling
	else if (mAquariumClick && mAquarium.getNavigation())
	{
		if (nFlags & MK_LBUTTON)
		{
			mAquariumOffsetX = point.x - mMouseLocationX;
			mAquariumOffsetY = point.y - mMouseLocationY;

			// get window size
			CRect rect;
			GetClientRect(&rect);

			// Don't allow scrolling off screen ( Bottom right corner )
			mAquariumOffsetX < rect.Width() - backgroundWidth ? mAquariumOffsetX = rect.Width() - backgroundWidth : mAquariumOffsetX = mAquariumOffsetX;
			mAquariumOffsetY < rect.Height() - backgroundHeight ? mAquariumOffsetY = rect.Height() - backgroundHeight : mAquariumOffsetY = mAquariumOffsetY;

			// Don't allow scrolling off screen ( top corner )
			mAquariumOffsetX > 0 ? mAquariumOffsetX = 0 : mAquariumOffsetX = mAquariumOffsetX;
			mAquariumOffsetY > 0 ? mAquariumOffsetY = 0 : mAquariumOffsetY = mAquariumOffsetY;

			mAquarium.setOffset(0, mAquariumOffsetY);
		}
		mAquarium.setOffset(mAquariumOffsetX, mAquariumOffsetY);
		Invalidate();
	}
	else
	{
		mAquariumClick = false;
	}
}

/**
* \brief Erase the background prior to drawing.
* \param pDC A device context to draw on
* \returns true
*/
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// This disabled the default background erase
	return TRUE;
}


void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
}


void CChildView::OnAddfishBubblesfish()
{
	auto fish = make_shared<CFishBubbles>(&mAquarium);
	fish->SetLocation(InitialX, InitialY);

	//subtracts cost of the fish from total funds
	if (mAquarium.GetScore() >= fish->getValue())
	{
		mAquarium.SubtractScore(fish->getValue());
		mAquarium.Add(fish);
	}
	else
		AfxMessageBox(L"Unable to Purchase;  Not enough Funds");

	Invalidate();
}


void CChildView::OnAddfishDoryfish()
{
	auto fish = make_shared<CFishDory>(&mAquarium);
	fish->SetLocation(InitialX, InitialY);

	//subtracts cost of the fish from total funds
	if (mAquarium.GetScore() >= fish->getValue())
	{
		mAquarium.SubtractScore(fish->getValue());
		mAquarium.Add(fish);
	}
	else
		AfxMessageBox(L"Unable to Purchase;  Not enough Funds");

	Invalidate();
}


void CChildView::OnFileTrashcan()
{
	if (!mAquarium.GetTrashActive())
	{
		mAquarium.IsTrashActive(true);
		Invalidate();
	}
	else
	{
		mAquarium.IsTrashActive(false);
		Invalidate();
	}
}


void CChildView::OnAdddecorTreasurechest()
{
	auto Chest = make_shared<CDecorTreasure>(&mAquarium);
	Chest->SetLocation(InitialX, InitialY);

	//subtracts cost of the fish from total funds
	if (mAquarium.GetScore() >= Chest->getValue() )
	{
		mAquarium.SubtractScore(Chest->getValue());
		mAquarium.Add(Chest);
	}
	else
		AfxMessageBox(L"Unable to Purchase;  Not enough Funds");

	Invalidate();
}


void CChildView::OnFileSaveas()
{
	CFileDialog dlg(false,  // false = Save dialog box
		L".aqua",           // Default file extension
		nullptr,            // Default file name (none)
		OFN_OVERWRITEPROMPT,      // Flags (none)
		L"Aquarium Files (*.aqua)|*.aqua|All Files (*.*)|*.*||");    // Filter 
	if (dlg.DoModal() != IDOK)
		return;

	wstring filename = dlg.GetPathName();
	mAquarium.Save(filename);
}


/** This function is called when an File Open menu item is selected.
*
* It loads the aquarium from a file.
* 
*/
void CChildView::OnFileOpen32778()
{
	CFileDialog dlg(true,  // true = Open dialog box
		L".aqua",           // Default file extension
		nullptr,            // Default file name (none)
		0,    // Flags
		L"Aquarium Files (*.aqua)|*.aqua|All Files (*.*)|*.*||");    // Filter
	if (dlg.DoModal() != IDOK)
		return;

	wstring filename = dlg.GetPathName();

	mAquarium.Load(filename);
	Invalidate();

}

/**
* \brief Handle timer events
* \param nIDEvent The timer event ID
*/
void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	Invalidate();
	CWnd::OnTimer(nIDEvent);
}


/**
 * \brief Adds an animated treasure chest to our tank
 */
void CChildView::OnAdddecorAnimatedteasurechest()
{
	auto Chest = make_shared<CDecorTreasureChest>(&mAquarium);
	Chest->SetLocation(InitialX, InitialY);

	//subtracts cost of the fish from total funds
	if (mAquarium.GetScore() >= Chest->getValue())
	{
		mAquarium.SubtractScore(Chest->getValue());
		mAquarium.Add(Chest);
	}
	else
		AfxMessageBox(L"Unable to Purchase;  Not enough Funds");
	
	Invalidate();
}

/**
* \brief Cleans the fishtank
*/
void CChildView::OnTankmaintenceCleantank()
{
	//resets the timer (and the image)
	mAquarium.setTime(NULL);
}

/**
* \brief Feeds every fish in the tank
*/
void CChildView::OnTankmaintenceFeedfish()
{
	CFeedFishVisitor visitor;
	mAquarium.Accept(&visitor);
	Invalidate();
}

/** \brief Display a message box containing the goals and status of the goals
*/
void CChildView::OnFileGoals()
{
	wstringstream str;
	str << L"-Have " << FishGoal << L" fish in the tank at one time : "; 
	if (mAquarium.GetItemCount() >= FishGoal)
		str << L"Achieved";
	else
		str << L"Unachieved";

	str << L"\n-Reach $" << ScoreGoal << L": ";
	if (mAquarium.GetScore() >= ScoreGoal)
		str << L"Achieved";
	else
		str << L"Unachieved";

	if (mAquarium.GetItemCount() >= FishGoal && mAquarium.GetScore() >= ScoreGoal)
		str << L"\n\nYOU WIN!!!";

	str << L"\n\n\nYou can view goals at anytime via the view menu.";

	MessageBox(str.str().c_str(), L"GAME GOALS", MB_OK);
}
