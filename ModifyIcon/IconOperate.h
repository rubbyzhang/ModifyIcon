
#pragma once
#include <iostream>
#include <stdio.h>
#include <shlobj.h>
#include "icon.h"
using namespace std;


//ֻ����24λ���ϣ�����Ҫ��ɫ���ICON�ļ�
class CIconOperate
{
public:
	CIconOperate(void);
	~CIconOperate(void);

	//������
	bool ReadIcon(const string _str);

	//��������
	bool SaveIcon(const string _str);
	
	//�޸�ICON�ļ�����
	bool  Modefiy();

	//��������ͼ��
	bool GenerateTestIcon(const string _str);

private:
	stIconData* m_IconData ;
	ICONDIR*    m_IconDir ;
	stIcon m_Icon ;


	//����ƫ����
	DWORD  CIconOperate::CalculateImageOffset(const int& index );

	//��ͼ
	void SetPointColor(int x, int y , DWORD color);
	void _draw_circle_8(int xc, int yc, int x, int y, DWORD c); 
	void DrawCircle(int cx , int cy, int radio ,bool isfill , DWORD color);

};

