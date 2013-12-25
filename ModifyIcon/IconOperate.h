
#pragma once
#include <iostream>
#include <stdio.h>
#include <shlobj.h>
#include "icon.h"
using namespace std;


//只操作24位以上，不需要调色板的ICON文件
class CIconOperate
{
public:
	CIconOperate(void);
	~CIconOperate(void);

	//读数据
	bool ReadIcon(const string _str);

	//保存数据
	bool SaveIcon(const string _str);
	
	//修改ICON文件数据
	bool  Modefiy();

	//产生测试图标
	bool GenerateTestIcon(const string _str);

private:
	stIconData* m_IconData ;
	ICONDIR*    m_IconDir ;
	stIcon m_Icon ;


	//计算偏移量
	DWORD  CIconOperate::CalculateImageOffset(const int& index );

	//画图
	void SetPointColor(int x, int y , DWORD color);
	void _draw_circle_8(int xc, int yc, int x, int y, DWORD c); 
	void DrawCircle(int cx , int cy, int radio ,bool isfill , DWORD color);

};

