#include "stdafx.h"
#include "Hanoi.h"

// For Debug print to edit control in Dialog
#include "TowerOfHanoiDlg.h"

// 색상정보: type COLORREF
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

// 원판의 mId에 따라 유일한 색을 할당하기 위한 배열
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

// 그림 그리는데 사용되는 좌표 및 크기정보.
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

// 생성자에 의해 ID가 결정되었으므로 원판의 크기와 색깔이 결정된다.
Plate::Plate(UINT id)
{
	mId = id;
	mWidth = 130 - 10 * (9 - mId);	// mId가 0일때 40px, 9일때 130px.
	mColor = gColorTable[id];
}

// bDraw에 의해 현재의 원판을 그리거나 지운다.
// TRUE: 그린다. FALSE: 원판을 지우고 기둥부분을 그린다.
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

// 원판이 옮겨진 위치정보를 저장한다
void Plate::Move(CDC *pDC, UINT to, UINT row)
{
	// Plate 현재 위치를 지운다.
	Draw(pDC, FALSE);

	mPosPeg = to;
	mPosRow = row;

	Draw(pDC, TRUE);

	return;
}

// Hanoi클래스의 생성자.
Hanoi::Hanoi(UINT num_plate, void *pDlg)
{
	UINT index;
	CTowerOfHanoiDlg *pclsDlg = (CTowerOfHanoiDlg *)pDlg;

	// Hanoi 클래스의 인스턴스를 만든 클래스의 포인터를 저장한다.
	// 상위 클래스의 public 메소드를 이용할 때 사용한다.
	mpclsDialog = pDlg;

	// Hanoi클래스가 만들어 질 때 mNumPlates = 0 으로 초기화 한다.
	// 왜냐하면 OnInitDialog()에서 InitPlateStatus()를 호출하면서 mNumPlates를 초기화 하게 된다.
	mNumPlates = 0;

	// Plate객체를 만들어둔다.
	for (index = 0; index < MAX_PLATE; index++)
		pPlate[index] = new Plate(index);	// Plate객채의 동적생성.
}

// 만들었던 원판 객체를 메모리에서 해제한다.
Hanoi::~Hanoi(void)
{
	UINT index;

	for (index = 0; index < MAX_PLATE; index++)
	{
		delete pPlate[index];	// 동적으로 생성되었던 Plate객체의 해제.
	}
}


// Hanoi를 시작하기 전에 Peg 0에 설정한 만큼의 원판을 걸어주는 함수.
void Hanoi::InitPlateStatus(UINT numPlate)
{
	// mPlateStatus 초기화.
	UINT numPeg, numRow;
	UINT index;

	// Hanoi 클래스가 갖는 원판의 갯수를 설정한다.
	mNumPlates = numPlate;

	// Peg에 걸려있는 원판의 번호를 저장하는 배열의 초기화.
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

// Hanoi tower의 원판을 옯기는 함수를 실행하는 시작점.
void Hanoi::DoHanoi(void)
{
	
	TowerOfHanoi(0, 1, 2, mNumPlates);
	return;
}

// from에 있는 원판 num_plate개를 use를 이용하여 to로 보내는 함수 
void Hanoi::TowerOfHanoi(UINT from, UINT use, UINT to, UINT num_plate)
{
	if (num_plate == 0)
		return;
	
	TowerOfHanoi(from, to, use, num_plate - 1);
	Move(from, to);
	TowerOfHanoi(use, from, to, num_plate - 1);

	return;
}

// 원판을 from에서 to로 옮기는 연산.
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

	// Plate 인스턴스의 값을 바꾼다.
	pPlate[id]->Move(pDC, to, row_to);
	
	// 원판이 옮겨지는것을 텍스트로 표시.
	msgDebug.Format(_T("(%d, %d) --> (%d, %d)\r\n"), from, row_from - 1, to, row_to);
	pclsDebugDlg->DebugPrint(msgDebug);
}

// 화면에 고정된 기둥을 그리는 함수.
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

// Hanoi클래스를 통해서 index에 해당하는 원판을 그리기 위한 함수.
void Hanoi::DrawPlate(CDC *pDC, UINT index)
{
	pPlate[index]->Draw(pDC, TRUE);
}