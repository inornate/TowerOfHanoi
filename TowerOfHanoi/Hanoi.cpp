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

// �׸� �׸��� �Լ���
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
	mWidth = 130 - 10 * (9 - mId);	// mId�� 0�϶� 40px, 9�϶� 130px.
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
		// �׸���
		pDC->FillSolidRect(rect, mColor);
	}
	else
	{
		// �����. 
		// 1. ���� �ִ����� ��ĭ���� �����. 
		pDC->FillSolidRect(rect, COLOR_WHITE);

		// 2. Peg�� �׸���. topLeft�� bottomRight�� y�� ���� Plate�� height�� ����.
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

// HanoiŬ������ ������.
Hanoi::Hanoi(UINT num_plate, void *pDlg)
{
	UINT index;
	CTowerOfHanoiDlg *pclsDlg = (CTowerOfHanoiDlg *)pDlg;

	mpclsDialog = pDlg;

	// TODO: ��ȭ������ Edit control���� ������ plate�� ������ �����´�.	

	// Plate��ü�� �����д�.
	for (index = 0; index < MAX_PLATE; index++)
		pPlate[index] = new Plate(index);	// Plate��ä�� ��������. Plate�� index�� 1���� ����.
	
	InitPlateStatus(pclsDlg->muiNumPlate);
}

void Hanoi::InitPlateStatus(UINT numPlate)
{
	// mPlateStatus �ʱ�ȭ.
	UINT numPeg, numRow;
	UINT index;

	mNumPlates = numPlate;

	for (numPeg = 0; numPeg < NUM_PEGS; numPeg++)
		for (numRow = 0; numRow < MAX_PLATE; numRow++)
			mPlateStatus[numPeg][numRow] = NO_PLATE;

	// ù��° Peg�� plate�� �����Ѵ�.
	for (index = 0; index < MAX_PLATE; index++)
	{
		pPlate[index]->mPosPeg = 0;			// �ʱ��� Peg��ȣ�� 0.
		if (index < mNumPlates)
		{
			pPlate[index]->mPosRow = (mNumPlates - 1) - index;	// Row: mNumPlates���� Row: 0���� ����
			mPlateStatus[0][pPlate[index]->mPosRow] = index;	// ù��° peg�� ���� plate���¸� ����Ѵ�.
		}
		else
		{
			pPlate[index]->mPosRow = 0;		// �ʱ⿡ ������ ���� plate�� Row�� 0���� �д�. 
		}
	}
}

Hanoi::~Hanoi(void)
{
	UINT index;
	
	for (index = 0; index < MAX_PLATE; index++)
	{
		delete pPlate[index];	// �������� �����Ǿ��� Plate��ü�� ����.
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

	// from Peg�� �ִ� �� ���� ���� plate�� row�� �˾Ƴ���.
	while (mPlateStatus[from][row_from] != NO_PLATE)
		row_from++;
	
	// row_from�� �ִ� plate�� ID�� mPlateStatus[from][row_from - 1]�̴�.
	id = mPlateStatus[from][row_from - 1];
	
	// row_from�� �Űܰ� plate �ڸ��� NO_PLATE�� ä���.
	mPlateStatus[from][row_from - 1] = NO_PLATE;

	// row_to�� NO_PLATE�� ���� ã�´�.
	while (mPlateStatus[to][row_to] != NO_PLATE)
		row_to++;

	// row_to�� �ڸ��� �Ű� ������ plate�� id�� ���´�.
	mPlateStatus[to][row_to] = id;

	// Plate ���� ��ġ�� �����.
	pPlate[id]->Draw(pDC, FALSE);

	// Plate �ν��Ͻ��� ���� �ٲ۴�.
	pPlate[id]->Move(to, row_to);
	
	// Plate �ٲ� ��ġ�� �׸���.
	pPlate[id]->Draw(pDC, TRUE);
			
	msgDebug.Format(_T("(%d, %d) --> (%d, %d)\r\n"), from, row_from - 1, to, row_to);
	pclsDebugDlg->DebugPrint(msgDebug);
}


void Hanoi::DrawPeg(CDC *pDC)
{
	// �׸��׸��� ������ TOP-LEFT, Point of Reference(POR)
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