#include "stdafx.h"
#include "Hanoi.h"

// For Debug print to edit control in Dialog
#include "TowerOfHanoiDlg.h"

#define COLOR_YELLOW	RGB(255, 255, 0)
#define COLOR_ORANGE	RGB(255, 128, 0)
#define COLOR_RED		RGB(255, 0, 0)
#define COLOR_DEEPGREEN	RGB(0, 128, 0)
#define COLOR_MAGENTA	RGB(64, 0, 128)
#define COLOR_GREEN		RGB(0, 255, 0)
#define COLOR_BLUE		RGB(0, 0, 255)
#define COLOR_VIOLET	RGB(128, 0, 255)
#define COLOR_CYAN		RGB(0, 0, 255)
#define COLOR_BLACK		RGB(0, 0, 0)
#define COLOR_WHITE		RGB(255, 255, 255)

static COLORREF gColorTable[MAX_PLATE] = {
	COLOR_YELLOW,
	COLOR_ORANGE,
	COLOR_RED,
	COLOR_DEEPGREEN,
	COLOR_MAGENTA,
	COLOR_GREEN,
	COLOR_BLUE,
	COLOR_VIOLET,
	COLOR_CYAN,
	COLOR_BLACK,
};

// 그림 그리는 함수들
#define DRAWAREA_POR_X	20
#define DRAWAREA_POR_Y	40

// Peg common
#define PEG_BASE_WIDTH			150
#define PEG_BASE_HEIGHT			6
#define PEG_POLE_WIDTH			4
#define PEG_POLE_HEIGHT			260

// Peg 1
#define PEG_BASE1_POINT_TOPLEFT_X	DRAWAREA_POR_X
#define PEG_BASE1_POINT_TOPLEFT_Y	DRAWAREA_POR_Y + 280
#define PEG_POLE1_POINT_TOPLEFT_X	DRAWAREA_POR_X + (PEG_BASE_WIDTH / 2) - (PEG_POLE_WIDTH / 2)
#define PEG_POLE1_POINT_TOPLEFT_Y	PEG_BASE1_POINT_TOPLEFT_Y - PEG_POLE_HEIGHT

// Peg 2
#define PEG_BASE2_POINT_TOPLEFT_X	PEG_BASE1_POINT_TOPLEFT_X + 180
#define PEG_BASE2_POINT_TOPLEFT_Y	PEG_BASE1_POINT_TOPLEFT_Y
#define PEG_POLE2_POINT_TOPLEFT_X	PEG_POLE1_POINT_TOPLEFT_X + 180
#define PEG_POLE2_POINT_TOPLEFT_Y	PEG_POLE1_POINT_TOPLEFT_Y

// Peg 3
#define PEG_BASE3_POINT_TOPLEFT_X	PEG_BASE2_POINT_TOPLEFT_X + 180
#define PEG_BASE3_POINT_TOPLEFT_Y	PEG_BASE2_POINT_TOPLEFT_Y
#define PEG_POLE3_POINT_TOPLEFT_X	PEG_POLE2_POINT_TOPLEFT_X + 180
#define PEG_POLE3_POINT_TOPLEFT_Y	PEG_POLE2_POINT_TOPLEFT_Y

#define PLATE_HEIGHT	20

Plate::Plate(UINT id)
{
	mId = id;
	mWidth = 130 - 10 * (9 - mId);	// mId가 0일때 40px, 9일때 130px.
	mColor = gColorTable[id];
}


void Plate::Draw(CDC *pDC, BOOLEAN bDraw)
{
	CRect rect;
	POINT topLeft, bottomRight;
	
	topLeft.x = (PEG_BASE1_POINT_TOPLEFT_X + 180 * mPosPeg) + (PEG_BASE_WIDTH - mWidth) / 2;
	topLeft.y = PEG_BASE1_POINT_TOPLEFT_Y - PLATE_HEIGHT * (mPosRow + 1);

	bottomRight.x = topLeft.x + mWidth;
	bottomRight.y = topLeft.y + PLATE_HEIGHT;
	
	rect.SetRect(topLeft, bottomRight);

	if (bDraw)
	{	
		// 그린다
		pDC->FillSolidRect(rect, mColor);
	}
	else
	{
		// 지운다. 
		// 1. 원래 있던것을 빈칸으로 만든다. 
		pDC->FillSolidRect(rect, COLOR_WHITE);

		// 2. Peg을 그린다. topLeft와 bottomRight의 y는 지운 Plate의 height와 같다.
		topLeft.x = PEG_POLE1_POINT_TOPLEFT_X + (180 * mPosPeg);
		bottomRight.x = topLeft.x + PEG_POLE_WIDTH;

		rect.SetRect(topLeft, bottomRight);
		pDC->FillSolidRect(rect, COLOR_BLACK);
	}

	return;
}

void Plate::Move(UINT to, UINT row)
{
	mPosPeg = to;
	mPosRow = row;

	return;
}

// Hanoi클래스의 생성자.
Hanoi::Hanoi(UINT num_plate, void *pDlg)
{
	UINT index;
	CTowerOfHanoiDlg *pclsDlg = (CTowerOfHanoiDlg *)pDlg;

	mpclsDialog = pDlg;

	// TODO: 대화상자의 Edit control에서 설정된 plate의 갯수를 가져온다.	

	// Plate객체를 만들어둔다.
	for (index = 0; index < MAX_PLATE; index++)
		pPlate[index] = new Plate(index);	// Plate객채의 동적생성. Plate의 index는 1부터 시작.
	
	InitPlateStatus(pclsDlg->muiNumPlate);
}

void Hanoi::InitPlateStatus(UINT numPlate)
{
	// mPlateStatus 초기화.
	UINT numPeg, numRow;
	UINT index;

	mNumPlates = numPlate;

	for (numPeg = 0; numPeg < NUM_PEGS; numPeg++)
		for (numRow = 0; numRow < MAX_PLATE; numRow++)
			mPlateStatus[numPeg][numRow] = NO_PLATE;

	// 첫번째 Peg에 plate를 설정한다.
	for (index = 0; index < MAX_PLATE; index++)
	{
		pPlate[index]->mPosPeg = 0;			// 초기의 Peg번호는 0.
		if (index < mNumPlates)
		{
			pPlate[index]->mPosRow = (mNumPlates - 1) - index;	// Row: mNumPlates부터 Row: 0까지 설정
			mPlateStatus[0][pPlate[index]->mPosRow] = index;	// 첫번째 peg에 대한 plate상태를 기록한다.
		}
		else
		{
			pPlate[index]->mPosRow = 0;		// 초기에 사용되지 않을 plate를 Row를 0으로 둔다. 
		}
	}
}

Hanoi::~Hanoi(void)
{
	UINT index;
	
	for (index = 0; index < MAX_PLATE; index++)
	{
		delete pPlate[index];	// 동적으로 생성되었던 Plate객체의 해제.
	}
}

void Hanoi::DoHanoi(void)
{
	TowerOfHanoi(0, 1, 2, mNumPlates);
	return;
}

void Hanoi::TowerOfHanoi(UINT from, UINT use, UINT to, UINT num_plate)
{
	if (num_plate == 0)
		return;
	
	TowerOfHanoi(from, to, use, num_plate - 1);
	Move(from, to);
	TowerOfHanoi(use, from, to, num_plate - 1);

	return;
}

void Hanoi::Move(UINT from, UINT to)
{
	UINT id;
	UINT row_from = 0;
	UINT row_to = 0;

	CString msgDebug;
	CTowerOfHanoiDlg *pclsDebugDlg = (CTowerOfHanoiDlg *)mpclsDialog;
	CDC *pDC = pclsDebugDlg->GetDC();

	// from Peg에 있는 맨 위에 놓은 plate의 row를 알아낸다.
	while (mPlateStatus[from][row_from] != NO_PLATE)
		row_from++;
	
	// row_from에 있는 plate의 ID는 mPlateStatus[from][row_from - 1]이다.
	id = mPlateStatus[from][row_from - 1];
	
	// row_from의 옮겨갈 plate 자리를 NO_PLATE로 채운다.
	mPlateStatus[from][row_from - 1] = NO_PLATE;

	// row_to의 NO_PLATE인 곳을 찾는다.
	while (mPlateStatus[to][row_to] != NO_PLATE)
		row_to++;

	// row_to의 자리에 옮겨 놓여질 plate의 id를 적는다.
	mPlateStatus[to][row_to] = id;

	// Plate 현재 위치를 지운다.
	pPlate[id]->Draw(pDC, FALSE);

	// Plate 인스턴스의 값을 바꾼다.
	pPlate[id]->Move(to, row_to);
	
	// Plate 바뀐 위치를 그린다.
	pPlate[id]->Draw(pDC, TRUE);
			
	msgDebug.Format(_T("(%d, %d) --> (%d, %d)\r\n"), from, row_from - 1, to, row_to);
	pclsDebugDlg->DebugPrint(msgDebug);
}


void Hanoi::DrawPeg(CDC *pDC)
{
	// 그림그리는 기준점 TOP-LEFT, Point of Reference(POR)
	CRect rect;
	COLORREF color;
	POINT topLeft, bottomRight;

	// Draw base 1
	topLeft.x = PEG_BASE1_POINT_TOPLEFT_X;
	topLeft.y = PEG_BASE1_POINT_TOPLEFT_Y;
	bottomRight.x = PEG_BASE1_POINT_TOPLEFT_X + PEG_BASE_WIDTH;
	bottomRight.y = PEG_BASE1_POINT_TOPLEFT_Y + PEG_BASE_HEIGHT;
	color = COLOR_BLACK;

	rect.SetRect(topLeft, bottomRight);
	pDC->FillSolidRect(rect, color);

	// Draw pole 1
	topLeft.x = PEG_POLE1_POINT_TOPLEFT_X;
	topLeft.y = PEG_POLE1_POINT_TOPLEFT_Y;
	bottomRight.x = PEG_POLE1_POINT_TOPLEFT_X + PEG_POLE_WIDTH;
	bottomRight.y = PEG_POLE1_POINT_TOPLEFT_Y + PEG_POLE_HEIGHT;

	rect.SetRect(topLeft, bottomRight);
	pDC->FillSolidRect(rect, color);

	// Draw base 2
	topLeft.x = PEG_BASE2_POINT_TOPLEFT_X;
	topLeft.y = PEG_BASE2_POINT_TOPLEFT_Y;
	bottomRight.x = PEG_BASE2_POINT_TOPLEFT_X + PEG_BASE_WIDTH;
	bottomRight.y = PEG_BASE2_POINT_TOPLEFT_Y + PEG_BASE_HEIGHT;
	color = COLOR_BLACK;

	rect.SetRect(topLeft, bottomRight);
	pDC->FillSolidRect(rect, color);

	// Draw pole 2
	topLeft.x = PEG_POLE2_POINT_TOPLEFT_X;
	topLeft.y = PEG_POLE2_POINT_TOPLEFT_Y;
	bottomRight.x = PEG_POLE2_POINT_TOPLEFT_X + PEG_POLE_WIDTH;
	bottomRight.y = PEG_POLE2_POINT_TOPLEFT_Y + PEG_POLE_HEIGHT;

	rect.SetRect(topLeft, bottomRight);
	pDC->FillSolidRect(rect, color);

	// Draw base 3
	topLeft.x = PEG_BASE3_POINT_TOPLEFT_X;
	topLeft.y = PEG_BASE3_POINT_TOPLEFT_Y;
	bottomRight.x = PEG_BASE3_POINT_TOPLEFT_X + PEG_BASE_WIDTH;
	bottomRight.y = PEG_BASE3_POINT_TOPLEFT_Y + PEG_BASE_HEIGHT;
	color = COLOR_BLACK;

	rect.SetRect(topLeft, bottomRight);
	pDC->FillSolidRect(rect, color);

	// Draw pole 3
	topLeft.x = PEG_POLE3_POINT_TOPLEFT_X;
	topLeft.y = PEG_POLE3_POINT_TOPLEFT_Y;
	bottomRight.x = PEG_POLE3_POINT_TOPLEFT_X + PEG_POLE_WIDTH;
	bottomRight.y = PEG_POLE3_POINT_TOPLEFT_Y + PEG_POLE_HEIGHT;

	rect.SetRect(topLeft, bottomRight);
	pDC->FillSolidRect(rect, color);

	return;
}

void Hanoi::DrawPlate(CDC *pDC, UINT index)
{
	pPlate[index]->Draw(pDC, TRUE);
}