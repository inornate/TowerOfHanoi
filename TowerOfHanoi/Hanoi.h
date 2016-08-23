#pragma once

#include <WinDef.h>

#define NUM_PEGS	3
#define MAX_PLATE	10
#define NO_PLATE	0xFFFFFFFF

class Plate
{
public:
	Plate(UINT id);	// ������

public:
	UINT mId;				// ���° plate������ ǥ����
	UINT mPosPeg, mPosRow;	// ���° Peg, Row�� ��ġ�ϰ� �ִ��� ǥ��

	void Draw(CDC *pDC, BOOLEAN bDraw);	// �ڽ��� ��ȭ���ڿ� �׸��� �Լ�
	void Move(UINT to, UINT row);	// Plate�� ��ġ�� �ű�� �Լ�.

private:
	UINT		mWidth;	// �׸����� ǥ���� �� plate�� ���̸� ����
	COLORREF	mColor;	// �׸����� ǥ���� �� plate�� ������ ����
};


class Hanoi
{
public:
	Hanoi(UINT num_plate, void *pDlg);	// ������. num_plate��ŭ�� ���� Hanoi class�� ����.
	~Hanoi();	// �Ҹ���

public:
	UINT mPlateStatus[NUM_PEGS][MAX_PLATE];
	UINT mNumPlates;			// ��� plate�� ������ �ִ��� ������
	Plate *pPlate[MAX_PLATE];	// �����ڿ� ���� ������� Hanoi class�� �ν��Ͻ��� �����ִ� plate������ŭ�� Plate �ν��Ͻ��� �����͸� ���� �迭.
	
	void InitPlateStatus(UINT numPlate);	// PlateStatus�� �ʱ�ȭ �ϴ� �Լ�.

	void DoHanoi(void);	// �ϳ��� Ÿ���� �����ϴ� �Լ�
	void *mpclsDialog; // Hanoi class�� �ν��Ͻ��� ���� Dialog class�� ������

	void DrawPeg(CDC *pDC);	// ȭ�鿡 Peg�� �׸��� �Լ�.
	void DrawPlate(CDC *pDC, UINT index); // index�� �ش��ϴ� plate�� �׸��� �Լ�.

private:
	void TowerOfHanoi(UINT from, UINT use, UINT to, UINT num_plate);
	void Move(UINT from, UINT to);
};