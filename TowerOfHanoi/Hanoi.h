#pragma once

#include <WinDef.h>

#define NUM_PEGS	3
#define MAX_PLATE	10
#define NO_PLATE	0xFFFFFFFF

class Plate
{
public:
	Plate(UINT id);	// 생성자

public:
	UINT mId;				// 몇번째 plate인지를 표시함
	UINT mPosPeg, mPosRow;	// 몇번째 Peg, Row에 위치하고 있는지 표시

	void Draw(CDC *pDC, BOOLEAN bDraw);	// 자신을 대화상자에 그리는 함수
	void Move(UINT to, UINT row);	// Plate의 위치를 옮기는 함수.

private:
	UINT		mWidth;	// 그림으로 표현될 때 plate의 넓이를 저장
	COLORREF	mColor;	// 그림으로 표현될 때 plate의 색깔을 저장
};


class Hanoi
{
public:
	Hanoi(UINT num_plate, void *pDlg);	// 생성자. num_plate만큼을 가진 Hanoi class를 생성.
	~Hanoi();	// 소멸자

public:
	UINT mPlateStatus[NUM_PEGS][MAX_PLATE];
	UINT mNumPlates;			// 몇개의 plate를 가지고 있는지 저장함
	Plate *pPlate[MAX_PLATE];	// 생성자에 의해 만들어진 Hanoi class의 인스턴스가 갖고있는 plate갯수만큼의 Plate 인스턴스의 포인터를 갖는 배열.
	
	void InitPlateStatus(UINT numPlate);	// PlateStatus를 초기화 하는 함수.

	void DoHanoi(void);	// 하노이 타워를 실행하는 함수
	void *mpclsDialog; // Hanoi class의 인스턴스를 만든 Dialog class의 포인터

	void DrawPeg(CDC *pDC);	// 화면에 Peg을 그리는 함수.
	void DrawPlate(CDC *pDC, UINT index); // index에 해당하는 plate를 그리는 함수.

private:
	void TowerOfHanoi(UINT from, UINT use, UINT to, UINT num_plate);
	void Move(UINT from, UINT to);
};