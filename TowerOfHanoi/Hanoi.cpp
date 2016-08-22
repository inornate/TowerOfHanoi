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
	mWidth = 130 - 10 * (9 - mId);	// mId�� 0�϶� 40px, 9�϶� 130px.
	mColor = gColorTable[id];
}


void Plate::Draw(BOOLEAN bDraw)
{
	if (bDraw)
	{
		// �׸���
	}
	else
	{
		// �����
	}
	return;
}

void Plate::Move(UINT to, UINT row)
{
	// ���� �ڸ��� ���� �׸��� �׸���.
	Draw(FALSE);

	mPosPeg = to;
	mPosRow = row;

	// ���ο� �ڸ��� �׸��� �׸���.
	Draw(TRUE);
}

// HanoiŬ������ ������.
Hanoi::Hanoi(UINT num_plate)
{
	UINT index;

	// TODO: ��ȭ������ Edit control���� ������ plate�� ������ �����´�.
	mNumPlates = 0;

	// mPlateStatus �ʱ�ȭ.
	UINT numPeg, numRow;
	for (numPeg = 0; numPeg < NUM_PEGS; numPeg++)
		for (numRow = 0; numRow < MAX_PLATE; numRow++)
			mPlateStatus[numPeg][numRow] = NO_PLATE;
	
	// TODO: Peg�� �׸���.

	// ù��° Peg�� plate�� �����Ѵ�.
	for (index = 0; index < mNumPlates; index++)
	{
		pPlate[index] = new Plate(index);	// Plate��ä�� ��������. Plate�� index�� 1���� ����.
		pPlate[index]->mPosPeg = 0;			// �ʱ��� Peg��ȣ�� 0.
		pPlate[index]->mPosRow = (mNumPlates - 1) - index;	// Row: mNumPlates���� Row: 0���� ����

		pPlate[index]->Draw(TRUE);	// Plate�� �׸���.

		mPlateStatus[0][pPlate[index]->mPosRow] = index;		// ù��° peg�� ���� plate���¸� ����Ѵ�.
	}	
}

Hanoi::~Hanoi(void)
{
	UINT index;
	
	for (index = 0; index < mNumPlates; index++)
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

	// Plate �ν��Ͻ��� ���� �ٲ۴�.
	pPlate[id]->Move(to, row_to);
}
