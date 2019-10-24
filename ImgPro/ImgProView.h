// ImgProView.h : interface of the CImgProView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMGPROVIEW_H__CA52376A_801B_4E87_AA91_71B205388883__INCLUDED_)
#define AFX_IMGPROVIEW_H__CA52376A_801B_4E87_AA91_71B205388883__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "math.h"
typedef unsigned char BYTE;

class CImgProView : public CView
{
protected: // create from serialization only
	CImgProView();
	DECLARE_DYNCREATE(CImgProView)

// Attributes
public:
	CImgProDoc* GetDocument();

// Operations
public:

	BYTE *image;
	int width, height;

	void readImg( int );
	int findex;
	int fnum;
	char directory[120];
	char *fnames;
	char *fname;

    // add image processing function 
	BYTE *outImg[10];
	void lineTrans(float *inImg, int width, int height, int outMax, int outMin, BYTE *outImg);
	void powTrans(BYTE *inImg, int width, int height, float powNum, float *outImg);
	void grayTrans(BYTE* inImg, int width, int height, float powNum, int outMax, int outMin, BYTE* outImg);

	void conv3_3(BYTE* inImg, int width, int height, int* convArray, BYTE* outImg);
	void smooth(BYTE* inImg, int width, int height, BYTE* outImg);
	void gaussSmooth(BYTE* inImg, int width, int height, BYTE* outImg);
	BYTE getMiddle(BYTE* list, int listLen);
	void middleSmooth(BYTE* inImg, int width, int height, BYTE* outImg);
	void sobel(BYTE* inImg, int width, int height, BYTE max, BYTE min, BYTE* outImg);
	BYTE getInterPoint(BYTE valueMin, BYTE valueMax, double inter);
	BYTE getBilinearInterpolation(BYTE upl, BYTE upr, BYTE downl, BYTE downr, double lr_inter, double ud_inter);
	void imageZoomIn(BYTE* inImg, int width, int height, int newWidth, int newHeight, BYTE* outImg);
	void arcPointRotate(int newX, int newY, int& x, int& y, double rotateAngle);
	void pointRotate(int x, int y, int& newX, int& newY, double rotateAngle);
	void imageRotate(BYTE* inImg, int width, int height, int newWidth, int newHeight, double rotateAngle, BYTE* outImg);
	void rotateImgSize(int width, int height, int& newWidth, int& newHeight, double rotateAngle);
	void index2coord(int index, int width, int height, int& x, int& y);
	void coord2index(int x, int y, int width, int height, int& index);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImgProView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImgProView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CImgProView)
	afx_msg void OnFileOpen();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnFileSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ImgProView.cpp
inline CImgProDoc* CImgProView::GetDocument()
   { return (CImgProDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMGPROVIEW_H__CA52376A_801B_4E87_AA91_71B205388883__INCLUDED_)
