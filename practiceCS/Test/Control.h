//control.h

#pragma once
#include "CMyClient.h"

class CTestDlg;	//클래스 선언!(전방참조)		//<===========

class Control
{
	//싱글톤 패턴 적용 ---------------------------------------------
private:
	Control();
	static Control* instance;
public:
	static Control* getInsatnce()
	{
		if (instance == NULL)
		{
			instance = new Control();
		}
		return instance;
	}
	//------------------------------------------------------------
	CMyClient client;
	CTestDlg* pForm = NULL;		//<====================
	

public:
	void RecvData(const char* msg, int size);
	void ParentForm(CTestDlg* pDlg);	//<====================
	
	//Form-> Control호출하는 메서드
public:
	
	void Draw(CPoint p);
};

