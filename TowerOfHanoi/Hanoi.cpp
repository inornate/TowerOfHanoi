#include "stdafx.h"
#include "Hanoi.h"

#define COLOR_YELLOW		RGB(255, 255, 0)
#define COLOR_ORANGE		RGB(255, 128, 0)
#define COLOR_RED		RGB(255, 0, 0)
#define COLOR_DEEPGREEN	RGB(0, 128, 0)
#define COLOR_MAGENTA	RGB(64, 0, 128)
#define COLOR_GREEN		RGB(0, 255, 0)
#define COLOR_BLUE		RGB(0, 0, 255)
#define COLOR_VIOLET		RGB(128, 0, 255)
#define COLOR_CYAN		RGB(0, 0, 255)
#define COLOR_BLACK		RGB(0, 0, 0)

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


#define PLATE_HEIGHT	20

Plate::Plate(UINT id)
{
	mId = id;
	mWidth = 130 - 10 * (9 - mId);	// mId가 0일때 40px, 9일때 130px.
	mColor = gColorTable[id];
}


void Plate::Draw(BOOLEAN bDraw)
{
	if (bDraw)
	{
		// 그린다
	}
	else
	{
		// 지운다
	}
	return;
}

void Plate::Move(UINT to, UINT row)
{
	// 현재 자리를 비우는 그림을 그린다.
	Draw(FALSE);

	mPosPeg = to;
	mPosRow = row;

	// 새로운 자리에 그림을 그린다.
	Draw(TRUE);
}

// Hanoi클래스의 생성자.
Hanoi::Hanoi(UINT num_plate)
{
	UINT index;

	// TODO: 대화상자의 Edit control에서 설정된 plate의 갯수를 가져온다.
	mNumPlates = 0;

	// mPlateStatus 초기화.
	UINT numPeg, numRow;
	for (numPeg = 0; numPeg < NUM_PEGS; numPeg++)
		for (numRow = 0; numRow < MAX_PLATE; numRow++)
			mPlateStatus[numPeg][numRow] = NO_PLATE;
	
	// TODO: Peg을 그린다.

	// 첫번째 Peg에 plate를 설정한다.
	for (index = 0; index < mNumPlates; index++)
	{
		pPlate[index] = new Plate(index);	// Plate객채의 동적생성. Plate의 index는 1부터 시작.
		pPlate[index]->mPosPeg = 0;			// 초기의 Peg번호는 0.
		pPlate[index]->mPosRow = (mNumPlates - 1) - index;	// Row: mNumPlates부터 Row: 0까지 설정

		pPlate[index]->Draw(TRUE);	// Plate를 그린다.

		mPlateStatus[0][pPlate[index]->mPosRow] = index;		// 첫번째 peg에 대한 plate상태를 기록한다.
	}	
}

Hanoi::~Hanoi(void)
{
	UINT index;
	
	for (index = 0; index < mNumPlates; index++)
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
	pPlate[id]->Move(to, row_to);
}
