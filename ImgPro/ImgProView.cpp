// ImgProView.cpp : implementation of the CImgProView class
//

#include "stdafx.h"
#include "ImgPro.h"

#include "ImgProDoc.h"
#include "ImgProView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ZOOMRATIO 1.2
#define ROTATEANGLE 30
/////////////////////////////////////////////////////////////////////////////
// CImgProView

IMPLEMENT_DYNCREATE(CImgProView, CView)

//Const = 384

BEGIN_MESSAGE_MAP(CImgProView, CView)
	//{{AFX_MSG_MAP(CImgProView)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImgProView construction/destruction

CImgProView::CImgProView()
{
	// TODO: add construction code here
	image = 0;
	findex = 0;
	for (int i = 0; i < 10; ++i)
		outImg[i] = 0;
}

CImgProView::~CImgProView()
{
	if( image )
		delete image;
	for (int i = 0; i < 10; ++i)
		if (outImg[i])
			delete outImg[i];
}

BOOL CImgProView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CImgProView drawing

void CImgProView::OnDraw(CDC* pDC)
{
	CImgProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	if( image == 0 )
		return;

	int i, j;
	int ptr = 0;
	BYTE gray;
	for( i=0; i<height; i++)
	{
		for( j=0; j<width; j++)
		{
			//gray = image[i*width+j];
			gray = image[ptr++];
			//gray = outImg[ptr++];
			pDC->SetPixel( j, i, RGB(gray,gray,gray));
			//show outImg if processed
		}
	}

	/*
	/////////////////////////////////E5 Show Image///////////////////////////////////
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			gray = outImg[0][i * width + j];
			pDC->SetPixel(width + 10 + j, i, RGB(gray, gray, gray));
		}
	}
	pDC->TextOutA(width + 60, 10, "2.0");

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			gray = outImg[1][i * width + j];
			pDC->SetPixel(2*width + 20 + j, i, RGB(gray, gray, gray));
		}
	}
	pDC->TextOutA(2*width + 60, 10, "3.0");
	*/

	/*
	/////////////////////////////////E6 Show Image///////////////////////////////////
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			gray = outImg[0][i * width + j];
			pDC->SetPixel(width + 10 + j, i, RGB(gray, gray, gray));
		}
	}
	pDC->TextOutA(width + 60, 10, "Smooth");

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			gray = outImg[1][i * width + j];
			pDC->SetPixel(2*width + 20 + j, i, RGB(gray, gray, gray));
		}
	}
	pDC->TextOutA(2*width + 60, 10, "GuassSmooth");
	*/

	/*
	/////////////////////////////////E7 Show Image///////////////////////////////////
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			gray = outImg[0][i * width + j];
			pDC->SetPixel(width + 10 + j, i, RGB(gray, gray, gray));
		}
	}
	*/

	/*
	/////////////////////////////////E8 Show Image///////////////////////////////////
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			gray = outImg[0][i * width + j];
			pDC->SetPixel(width + 10 + j, i, RGB(gray, gray, gray));
		}
	}
	*/

	/////////////////////////////////E9 Show Image///////////////////////////////////
	int newHeight = height * ZOOMRATIO;
	int newWidth = width * ZOOMRATIO;
	for (i = 0; i < newHeight; i++)
	{
		for (j = 0; j < newWidth; j++)
		{
			gray = outImg[0][i * newWidth + j];
			pDC->SetPixel(width + 10 + j, i, RGB(gray, gray, gray));
		}
	}
	int newWidth2, newHeight2;
	rotateImgSize(width, height, newWidth2, newHeight2, ROTATEANGLE);
	for (i = 0; i < newHeight2; i++)
	{
		for (j = 0; j < newWidth2; j++)
		{
			gray = outImg[1][i * newWidth2 + j];
			pDC->SetPixel(width + newWidth + 20 + j, i, RGB(gray, gray, gray));
		}
	}


	//////   show outImg here //////////////////////


}


/////////////////////////////////////////////////////////////////////////////
// CImgProView printing

BOOL CImgProView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CImgProView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CImgProView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CImgProView diagnostics

#ifdef _DEBUG
void CImgProView::AssertValid() const
{
	CView::AssertValid();
}

void CImgProView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImgProDoc* CImgProView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImgProDoc)));
	return (CImgProDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImgProView message handlers

void CImgProView::OnFileOpen() 
{
	// TODO: Add your command handler code here
	CFileDialog MyFDlg(TRUE, NULL,NULL, OFN_HIDEREADONLY, NULL,NULL );

	MyFDlg.m_ofn.lpstrFilter = "(*.lst;*.raw)\0*.lst;*.raw\0";
	MyFDlg.m_ofn.lpstrInitialDir = "C:\\Users\\a1176\\Desktop\\E1\\bb\\bb";

	if( MyFDlg.DoModal() == IDOK )
	{
		CString SFName;

		SFName = MyFDlg.GetPathName( ); //full name with path

		char *fnstr;
		fnstr = SFName.GetBuffer(4); //read the name from string 

		FILE *fpLst;
		int n;

		int len;
		len = strlen( fnstr );
		if( !strcmp( fnstr+len-3, "raw" ) ) //single raw image
		{
			fnum = 0;
			char *ptr;
			ptr = fnstr+len-3;
			while( *ptr != '\\')
				ptr--;
			*ptr = 0;
			strcpy( directory, fnstr);//Directory

			fnames = new char[500];
			strcpy( fnames, ptr+1); //image name
		}
		else //list file
		{
			//fpLst = fopen( fnstr, "rb");
			fpLst = fopen(fnstr, "r");
			fscanf( fpLst, "%3d", &fnum);
			fscanf( fpLst, "%s", directory);//directory

			fnames = new char[fnum*100];
			fname = new char[100];
			for( n=0; n<fnum; n++)
				fscanf( fpLst, "%s", fnames+n*100);// image names
			for (n = 0; n < fnum; n++)
				fname = fnames + n * 100;

			fclose(fpLst);
		}

		findex = 0;
		readImg( findex);
	}
}	

void CImgProView::readImg( int findex)
{
	
	char fullName[120];
	sprintf( fullName, "%s\\%s", directory, fnames+findex*100);

	FILE *fpImg;
	fpImg = fopen( fullName, "rb");
	if( fpImg==0 )
	{
		AfxMessageBox( "Cannot open the image file", MB_OK, 0 );
		return;
	}

	CString sFTitle;
	sFTitle.Format( "%s", fnames+findex*100 );

	CImgProDoc* pDoc;
	pDoc = GetDocument();
	pDoc->SetTitle( sFTitle );

	fread( &width, sizeof(int), 1, fpImg);
	fread( &height, sizeof(int), 1, fpImg);

	if( image )
		delete image;

	image = new BYTE[width*height];

	fread( image, sizeof(BYTE), width * height, fpImg);
	fclose(fpImg);

////////  add processing function here  ///////////////////

	/*
	//////////////////////////////E5///////////////////////////////
	outImg[0] = new BYTE[width*height];
	grayTrans(image, width, height, 2, 250, 0, outImg[0]);

	outImg[1] = new BYTE[width * height];
	grayTrans(image, width, height, 3, 250, 0, outImg[1]);
	*/

	/*
	//////////////////////////////E6///////////////////////////////
	outImg[0] = new BYTE[width * height];
	smooth(image, width, height, outImg[0]);

	outImg[1] = new BYTE[width * height];
	gaussSmooth(image, width, height, outImg[1]);
	*/

	/*
	//////////////////////////////E7///////////////////////////////
	outImg[0] = new BYTE[width * height];
	middleSmooth(image, width, height, outImg[0]);
	*/

	/*
	//////////////////////////////E8///////////////////////////////
	outImg[0] = new BYTE[width * height];
	outImg[1] = new BYTE[width * height];
	smooth(image, width, height, outImg[1]);
	sobel(outImg[1], width, height, 200, 80, outImg[0]);
	*/

	//////////////////////////////E9///////////////////////////////
	outImg[0] = new BYTE[int(width * ZOOMRATIO) * int(height * ZOOMRATIO)];
	imageZoomIn(image, width, height, int(width * ZOOMRATIO), int(height * ZOOMRATIO), outImg[0]);
	int newWidth, newHeight;
	rotateImgSize(width, height, newWidth, newHeight, ROTATEANGLE);
	outImg[1] = new BYTE[newWidth * newHeight];
	imageRotate(image, width, height, newWidth, newHeight, ROTATEANGLE, outImg[1]);
		
////////////////////////////////////////////////////////////
	
    OnInitialUpdate();
	CRect ClientRect;
	GetClientRect( &ClientRect );
	InvalidateRect(  &ClientRect );	

}

void CImgProView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if( nChar == VK_NEXT)
	{
		if( findex < fnum )
		{
			findex++;
			readImg( findex );
		}
	}
	if( nChar == VK_PRIOR )
	{
		if( findex > 0 )
		{
			findex--;
			readImg( findex );
		}
	}	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CImgProView::OnFileSave() 
{
	// TODO: Add your command handler code here
	char str[40], *ptr;
	sprintf( str, fnames+findex*40 );
	ptr = str;
	while( *ptr!='.' )
		ptr ++;
	*ptr = 0;

	char fname[80];
	//sprintf( fname, "..\\bb\\out%s.raw", str );
	sprintf(fname, "C:\\Users\\a1176\\Desktop\\out%s.raw", str);

	FILE* fpOut;
	fpOut = fopen( fname, "wb" );

	fwrite( &width, 4, 1, fpOut );
	fwrite( &height, 4, 1, fpOut );
	fwrite( outImg, 1, width*height, fpOut );

	fclose( fpOut );

}


void CImgProView::lineTrans(float* inImg, int width, int height, int outMax, int outMin, BYTE* outImg) {
	float inMin, inMax;
	inMin = inMax = inImg[0];
	int lenght = width * height;
	for (int i = 0; i < lenght; ++i) {
		if (inMax < inImg[i])
			inMax = inImg[i];
		if (inMin > inImg[i])
			inMin = inImg[i];
	}
	float A = (outMax - outMin) / (inMax - inMin);
	for (int i = 0; i < lenght; ++i)
		outImg[i] = A * (inImg[i] - inMin) + outMin;
}
void CImgProView::powTrans(BYTE* inImg, int width, int height, float powNum, float* outImg) {
	int lenght = width * height;
	for (int i = 0; i < lenght; ++i)
		outImg[i] = pow(inImg[i], powNum) + 0.5;
}

void CImgProView::grayTrans(BYTE* inImg, int width, int height, float powNum, int outMax, int outMin, BYTE* outImg) {
	float* tmp = new float[width * height];
	powTrans(inImg, width, height, powNum, tmp);
	lineTrans(tmp, width, height, outMax, outMin, outImg);
	delete tmp;
}

void CImgProView::conv3_3(BYTE* inImg, int width, int height, int* convArray, BYTE* outImg) {
	int outImgPtr = 0;
	int tHeight = height + 2;
	int tWidth = width + 2;
	BYTE** tmp = new BYTE * [tHeight];
	for (int i = 0; i < tHeight; ++i)
		tmp[i] = new BYTE[tWidth];

	for (int i = 0; i < tHeight; ++i) {
		for (int j = 0; j < tWidth; ++j) {
			if (i == 0 || j == 0 || i == tHeight - 1 || j == tWidth - 1)
				tmp[i][j] = 0;
			else
				tmp[i][j] = inImg[(i-1) * width + (j-1)];
		}
	}

	int convSum = 0;
	for (int i = 0; i < 9; ++i)
		convSum += convArray[i];

	if (convSum == 0)
		convSum = 1;

	for (int i = 1; i < tHeight-1; ++i) {
		for (int j = 1; j < tWidth-1; ++j) {
			int value = 0;
			for (int a = -1; a <= 1; ++a)
				for (int b = -1; b <= 1; ++b)
					value += tmp[i + a][j + b] * convArray[(a + 1) * 3 + (b + 1)];
			value /= convSum;
			outImg[outImgPtr++] = value;
		}
	}
	for (int i = 0; i < tHeight; ++i)
		delete tmp[i];
	delete tmp;
}

void CImgProView::smooth(BYTE* inImg, int width, int height, BYTE* outImg) {
	int smoothArray[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	conv3_3(inImg, width, height, smoothArray, outImg);
}

void CImgProView::gaussSmooth(BYTE* inImg, int width, int height, BYTE* outImg) {
	int gaussArray[9] = { 1, 2, 1, 2, 4, 2, 1, 2, 1 };
	conv3_3(inImg, width, height, gaussArray, outImg);
}

BYTE CImgProView::getMiddle(BYTE* list, int listLen) {
	int tmp;
	for (int i = 0; i < listLen - 1; ++i) {
		for (int j = i; j < listLen - 1; ++j)
			if (list[j] > list[j + 1]) {
				tmp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = tmp;
			}
	}
	return list[listLen / 2];
}

void CImgProView::middleSmooth(BYTE* inImg, int width, int height, BYTE* outImg) {
	BYTE tmp[9];
	int imgSize = width * height;
	int outImgPtr = 0;

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			if (i == 0 || j == 0 || i == height - 1 || j == width - 1) {
				outImg[outImgPtr] = inImg[outImgPtr];
				outImgPtr += 1;
			} else {
				int tmpPtr = 0;
				for (int a = -1; a <= 1; ++a)
					for (int b = -1; b <= 1; ++b)
						tmp[tmpPtr++] = inImg[(i + a) * height + j + b];
				outImg[outImgPtr++] = getMiddle(tmp, 9);
			}
		}
	}
}

void CImgProView::sobel(BYTE* inImg, int width, int height, BYTE max, BYTE min, BYTE* outImg) {
	int imgSize = width * height;
	int sobelH[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
	int sobelV[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
	int tmp;
	BYTE* outImgH = new BYTE[imgSize];
	BYTE* outImgV = new BYTE[imgSize];
	conv3_3(inImg, width, height, sobelH, outImgH);
	conv3_3(inImg, width, height, sobelV, outImgV);

	for (int i = 0; i < imgSize; ++i) {
		//tmp = abs(outImgH[i]) + abs(outImgV[i]);
		tmp = sqrt(long(outImgH[i]) * outImgH[i] + long(outImgV[i]) * outImgV[i]);
		if (tmp >= max)
			outImg[i] = max;
		else if (tmp <= min)
			outImg[i] = min;
		else
			outImg[i] = tmp;
	}
	delete outImgH;
	delete outImgV;
}

BYTE CImgProView::getInterPoint(BYTE value1, BYTE value2, double inter) {
	int dt = (value2 - value1) * inter;
	int base = value1;
	return BYTE(base + dt);
}

BYTE CImgProView::getBilinearInterpolation(BYTE upl, BYTE upr, BYTE downl, BYTE downr, double lr_inter, double ud_inter) {
	BYTE upi = getInterPoint(upl, upr, lr_inter);
	BYTE downi = getInterPoint(downl, downr, lr_inter);
	BYTE p = getInterPoint(upi, downi, ud_inter);
	return p;
}

void CImgProView::imageZoomIn(BYTE* inImg, int width, int height, int newWidth, int newHeight, BYTE* outImg) {
	double widthRatio = double(width) / newWidth;
	double heightRatio = double(height) / newHeight;
	double widthPtr, heightPtr;
	double dHeightInter, dWidthInter;
	int intHeightInter, intWidthInter;
	int newWidthPtr, newHeightPtr;
	for (heightPtr = newHeightPtr = 0; newHeightPtr < newHeight; ++newHeightPtr, heightPtr += heightRatio) {
		for (widthPtr = newWidthPtr = 0; newWidthPtr < newWidth; ++newWidthPtr, widthPtr += widthRatio) {
			intHeightInter = int(heightPtr);
			intWidthInter = int(widthPtr);
			dHeightInter = heightPtr - intHeightInter;
			dWidthInter = widthPtr - intWidthInter;
			outImg[newHeightPtr * newWidth + newWidthPtr] = getBilinearInterpolation(
				inImg[intHeightInter * width + intWidthInter], inImg[intHeightInter * width + intWidthInter + 1],
				inImg[(intHeightInter + 1) * width + intWidthInter], inImg[(intHeightInter + 1) * width + intWidthInter + 1],
				dWidthInter, dHeightInter
			);
		}
	}
}

void CImgProView::arcPointRotate(int newX, int newY, int& x, int& y, double rotateAngle) {
	x = newY * sin(rotateAngle) + newX * cos(rotateAngle);
	y = newY * cos(rotateAngle) - newX * sin(rotateAngle);
}

void CImgProView::pointRotate(int x, int y, int& newX, int& newY, double rotateAngle) {
	newX = x * cos(rotateAngle) - y * sin(rotateAngle);
	newY = x * sin(rotateAngle) + y * cos(rotateAngle);
}

void CImgProView::rotateImgSize(int width, int height, int& newWidth, int& newHeight, double rotateAngle) {
	int x1, x2, x3;
	int y1, y2, y3;
	pointRotate(0, height, x1, y1, rotateAngle);
	pointRotate(width, 0, x2, y2, rotateAngle);
	pointRotate(width, height, x3, y3, rotateAngle);
	int minWidth = min(min(x1, x2), min(x3, 0));
	int maxWidth = max(max(x1, x2), max(x3, 0));
	int minHeight = min(min(y1, y2), min(y3, 0));
	int maxHeight = max(max(y1, y2), max(y3, 0));
	newWidth = maxWidth - minWidth;
	newHeight = maxHeight - minHeight;
}

void CImgProView::index2coord(int index, int width, int height, int& x, int& y) {
	int arrayX = index % width;
	int arrayY = index / width;
	int coordX = arrayX;
	int coordY = height - arrayY;
	int middleX = width / 2;
	int middleY = height / 2;
	x = coordX - middleX;
	y = coordY - middleY;
}

void CImgProView::coord2index(int x, int y, int width, int height, int& index) {
	int middleX = width / 2;
	int middleY = height / 2;
	int coordX = x + middleX;
	int coordY = y + middleY;
	int arrayX = coordX;
	int arrayY = height - coordY;
	index = arrayY * height + arrayX;
}

void CImgProView::imageRotate(BYTE* inImg, int width, int height, int newWidth, int newHeight, double rotateAngle, BYTE* outImg) {
	int newImgSize = newWidth * newHeight;
	int widthL = -width / 2;
	int widthR = width / 2;
	int heightU = height / 2;
	int heightD = -height / 2;
	int x, y;
	int index;
	int newX, newY;
	for (int i = 0; i < newImgSize; ++i) {
		index2coord(i, newWidth, newHeight, newX, newY);
		arcPointRotate(newX, newY, x, y, rotateAngle);
		if (x <= widthL || x >= widthR || y <= heightD || y >= heightU) {
			outImg[i] = 255;
			continue;
		} else {
			coord2index(x, y, width, height, index);
			outImg[i] = inImg[index];
		}
	}
}