#pragma once

#include <WinDef.h>

#define NUM_PEGS	3
#define MAX_PLATE	10
#define NO_PLATE	0xFFFFFFFF

// ���� Ŭ����
// ��ü�� �ڽ��� ID, ��ġ����, ũ��� ���� ���´�.
// ��ü�� �ڽ��� ������ �� �ְ�, �׸� �� �ִ�.
class Plate
{
public:
	Plate(UINT id);	// ������

public:
	UINT mId;				// ���° plate������ ǥ����
	UINT mPosPeg, mPosRow;	// ���° Peg, Row�� ��ġ�ϰ� �ִ��� ǥ��

	void Draw(CDC *pDC, BOOLEAN bDraw);	// �ڽ��� ��ȭ���ڿ� �׸��� �Լ�
	void Move(CDC *pDC, UINT to, UINT row);		// Plate�� ��ġ�� �ű�� �Լ�.

private:
	UINT		mWidth;		// �׸����� ǥ���� �� plate�� ���̸� ����. mId�� ���� �����ȴ�.
	COLORREF	mColor;		// �׸����� ǥ���� �� plate�� ������ ����. mId�� ���� �����ȴ�.
};

// �ϳ����� ž Ŭ����
// ��ü�� ���� ���õ� ������ ����, �� ��տ� �ɷ��ִ� ���� ��ü�� ���´�.
// �ϳ����� ž ������ �����ϴ� �޼ҵ�� ���� �� ����� �׸��� �޼ҵ带 ���´�.
class Hanoi
{
public:
	Hanoi(UINT num_plate, void *pDlg);	// ������. num_plate��ŭ�� ���� Hanoi class�� ����.
	~Hanoi();	// �Ҹ���

public:
	UINT mNumPlates;	// ��� plate�� ������ �ִ��� ������

	void InitPlateStatus(UINT numPlate);	// PlateStatus�� �ʱ�ȭ �ϴ� �Լ�.
	void DoHanoi(void);						// �ϳ��� Ÿ���� �����ϴ� �Լ�
	
	// �׸��� �׸��� ���� �޼ҵ��.
	void DrawPeg(CDC *pDC);					// ȭ�鿡 Peg�� �׸��� �Լ�.
	void DrawPlate(CDC *pDC, UINT index);	// index�� �ش��ϴ� plate�� �׸��� �Լ�.

private:
	// Hanoi class�� �ν��Ͻ��� ���� Dialog class�� ������. 
	// CPP���Ͽ��� �ش��ϴ� ��ȭ���� Ŭ������ ����� �ҷ����̰�,
	// �ش��ϴ� �̸��� Ŭ������ �����ͷ� ĳ�����ؾ� �Ѵ�.
	void *mpclsDialog;
	Plate *pPlate[MAX_PLATE];				// �����ڿ� ���� ������� Hanoi class�� �ν��Ͻ��� �����ִ� plate������ŭ�� Plate �ν��Ͻ��� �����͸� ���� �迭.
	UINT mPlateStatus[NUM_PEGS][MAX_PLATE];	// �� Peg/Row�� �����ϴ� Plate�� ID�� ���� �迭.

	void TowerOfHanoi(UINT from, UINT use, UINT to, UINT num_plate);	// �ϳ��� Ÿ���� ��� �˰����� ���� �Լ�
	void Move(UINT from, UINT to);	// from�� �� �����ִ� �����Ѱ��� to�� �ű�� �Լ�
};
