/**
* \file ChildView.h
*
* \author Stephan Hutecker 
*
* \brief Class that implements the child window our program draws in.
*
* The window is a child of the main frame, which holds this
* window, the menu bar, and the status bar.
*/


// ChildView.h : interface of the CChildView class
//


#pragma once
#include "Aquarium.h"

// CChildView window
/** \brief The child window our program draws in. */
class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();
	/// Adds a beta fish to our tank
	afx_msg void OnAddfishBetafish();
	/// Action for left mouse button down
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	/// Action for left mouse button up
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	/// Action for moving our mouse
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	/// Any item we are currently dragging
	std::shared_ptr<CItem> mGrabbedItem;
	/// Erases our background
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	/// Handler we aren't using
	afx_msg void OnSize(UINT nType, int cx, int cy);
	/// Adds a bubble fish to our tank
	afx_msg void OnAddfishBubblesfish();
	/// Adds a dory fish to our tank
	afx_msg void OnAddfishDoryfish();
	/// Toggles trash can
	afx_msg void OnFileTrashcan();
	/// Adds a treasure chest to the tank
	afx_msg void OnAdddecorTreasurechest();
	/// Saves our file
	afx_msg void OnFileSaveas();
	/// Opens a saved file
	afx_msg void OnFileOpen32778();
	/// A timer to enable animations
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	/// creates the treasure chest
	afx_msg void OnAdddecorAnimatedteasurechest();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

private:
	/// An object that describes our aquarium
	CAquarium  mAquarium;
	/// Initial fish X location
	const int InitialX = 200;
	/// Initial fish Y location
	const int InitialY = 200;
	/// bool, true if trash is visible, false else
	bool mTrashCanActive = false;
	/// True until the first time we draw
	bool mFirstDraw = true;
	/// Last time we read the timer
	long long mLastTime; 
	/// Rate the timer updates
	double mTimeFreq;       
	/// Whether or not we clicked the aquarium
	bool mAquariumClick = false;
	/// Where we pressed the mouse X
	int mMouseLocationX = 0;
	/// Where we pressed the mouse Y
	int mMouseLocationY = 0;
	/// Top right corner of aquarium offset x
	int mAquariumOffsetX = 0;
	/// Top right corner of aquarium offset y
	int mAquariumOffsetY = 0;
	/// Where we last pressed the mouse X
	int mMouseLocationPreviousX = 0;
	/// Where we last pressed the mouse Y
	int mMouseLocationPreviousY = 0;

public:
	afx_msg void OnTankmaintenceCleantank();
	afx_msg void OnTankmaintenceFeedfish();
	afx_msg void OnFileGoals();
};

