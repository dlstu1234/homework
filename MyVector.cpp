// ConsoleApplication10.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <vector>
using std::endl;
using std::cout;

template<typename T>
class MyVector
{
	T* Buffer;
	int BufferSize = 0;
	int BufferLen = 0;

public:

public:
	MyVector() 
	{
		BufferSize = 0; BufferLen = 4;
		Buffer = new T[BufferLen];
	}

	size_t Size() 
	{
		return BufferSize;
	}

	bool Empty() 
	{
		return BufferSize == 0;
	}

	bool full() 
	{
		return BufferSize == BufferLen;
	}

	void Push_Back(T Data) 
	{
		if (full()) 
		{ // 배열에 공간이 없을때 크기 증가시키기, 가변배열 만들기
			BufferLen = BufferLen * 2;
			T *Temp = new T[BufferLen];
			for (int i = 0; i < BufferSize; ++i) 
			{
				Temp[i] = Buffer[i];
			}

			delete[] Buffer;
			Buffer = Temp;
		}
		Buffer[BufferSize] = Data;
		++BufferSize;
	}

	T Get(size_t Index) 
	{
		return Buffer[Index];
	}

	void clear() 
	{
		delete[] Buffer;
		BufferSize = 0; BufferLen = 4;
		Buffer = new T[BufferLen];
	}
};

int main()
{
	MyVector<bool> mv;

	cout << mv.Size() << endl;
	cout << mv.Get(mv.Size()) << endl;
	cout << mv.full() << endl;
	cout << mv.Empty() << endl;
	mv.Push_Back(true);
	mv.Push_Back(true);
	mv.Push_Back(false);
	mv.Push_Back(true);
	mv.Push_Back(true);
	mv.Push_Back(false);
	cout << mv.Size() << endl;
	cout << mv.Get(mv.Size()) << endl;
	cout << mv.full() << endl;
	cout << mv.Empty() << endl;
	mv.clear();
	cout << mv.Size() << endl;
	cout << mv.Get(mv.Size()) << endl;
	cout << mv.full() << endl;
	cout << mv.Empty() << endl;

}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
