#pragma once

#include <WinDef.h>

#define NUM_PEGS	3
#define MAX_PLATE	10
#define NO_PLATE	0xFFFFFFFF

// 원판 클래스
// 객체는 자신의 ID, 위치정보, 크기와 색을 갖는다.
// 객체는 자신을 움직일 수 있고, 그릴 수 있다.
class Plate
{
public:
	Plate(UINT id);	// 생성자

public:
	UINT mId;				// 몇번째 plate인지를 표시함
	UINT mPosPeg, mPosRow;	// 몇번째 Peg, Row에 위치하고 있는지 표시

	void Draw(CDC *pDC, BOOLEAN bDraw);	// 자신을 대화상자에 그리는 함수
	void Move(CDC *pDC, UINT to, UINT row);		// Plate의 위치를 옮기는 함수.

private:
	UINT		mWidth;		// 그림으로 표현될 때 plate의 넓이를 저장. mId에 의해 결정된다.
	COLORREF	mColor;		// 그림으로 표현될 때 plate의 색깔을 저장. mId에 의해 결정된다.
};

// 하노이의 탑 클래스
// 객체는 현재 세팅된 원판의 갯수, 각 기둥에 걸려있는 원판 객체를 갖는다.
// 하노이의 탑 동작을 수행하는 메소드와 원판 및 기둥을 그리는 메소드를 갖는다.
class Hanoi
{
public:
	Hanoi(UINT num_plate, void *pDlg);	// 생성자. num_plate만큼을 가진 Hanoi class를 생성.
	~Hanoi();	// 소멸자

public:
	UINT mNumPlates;	// 몇개의 plate를 가지고 있는지 저장함

	void InitPlateStatus(UINT numPlate);	// PlateStatus를 초기화 하는 함수.
	void DoHanoi(void);						// 하노이 타워를 실행하는 함수
	
	// 그림을 그리기 위한 메소드들.
	void DrawPeg(CDC *pDC);					// 화면에 Peg을 그리는 함수.
	void DrawPlate(CDC *pDC, UINT index);	// index에 해당하는 plate를 그리는 함수.

private:
	// Hanoi class의 인스턴스를 만든 Dialog class의 포인터. 
	// CPP파일에서 해당하는 대화상자 클래스의 헤더를 불러들이고,
	// 해당하는 이름의 클래스의 포인터로 캐스팅해야 한다.
	void *mpclsDialog;
	Plate *pPlate[MAX_PLATE];				// 생성자에 의해 만들어진 Hanoi class의 인스턴스가 갖고있는 plate갯수만큼의 Plate 인스턴스의 포인터를 갖는 배열.
	UINT mPlateStatus[NUM_PEGS][MAX_PLATE];	// 각 Peg/Row에 존재하는 Plate의 ID를 갖는 배열.

	void TowerOfHanoi(UINT from, UINT use, UINT to, UINT num_plate);	// 하노이 타워의 재귀 알고리즘을 담은 함수
	void Move(UINT from, UINT to);	// from의 맨 위에있는 원판한개를 to로 옮기는 함수
};
