//control.h

#pragma once
#include "CMyClient.h"

class CTestDlg;	//Ŭ���� ����!(��������)		//<===========

class Control
{
	//�̱��� ���� ���� ---------------------------------------------
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
	
	//Form-> Controlȣ���ϴ� �޼���
public:
	
	void Draw(CPoint p);
};

