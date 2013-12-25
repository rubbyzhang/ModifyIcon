#include "StdAfx.h"
#include "IconOperate.h"
#include <fstream>

#define WIDTHBYTES(bits,ppxs)    (  ((((bits) + 31)>>5)<<5) * ppxs / 8 )
CIconOperate::CIconOperate(void)
{
	m_IconData = NULL ;
	m_IconDir = NULL ;
}


CIconOperate::~CIconOperate(void)
{

}

//读操作
bool CIconOperate::ReadIcon(const string _str)
{
	fstream fin ;
	fin.open(_str.c_str(),ios_base::binary | ios_base::in);
	if (!fin.is_open())
	{
		return false ;
	}

	ICONDIR dirTemp ;
	//reserved
	fin.read((char*)(&dirTemp.idReserved),sizeof(WORD));
	//type
	fin.read((char*)(&dirTemp.idType),sizeof(WORD));
	//num
	fin.read((char*)(&dirTemp.idCount),sizeof(WORD));

	//image data header
	byte *pBuffer = new byte[3 * sizeof(WORD) + dirTemp.idCount * sizeof(ICONDIRENTRY)] ;
	m_IconDir = (ICONDIR *)(pBuffer);
	m_IconDir->idCount = dirTemp.idCount ;
	m_IconDir->idReserved = dirTemp.idReserved ;
	m_IconDir->idType = dirTemp.idType ;
	for (int i = 0 ; i < dirTemp.idCount ; ++i)
	{
		fin.read((char*)(&m_IconDir->idEntries[i]),sizeof(ICONDIRENTRY));
	}

	//img data 
	byte *pBufferData = new byte[sizeof(int) + dirTemp.idCount * sizeof(stImageData)];
	m_IconData = (stIconData*)pBufferData ;
	m_IconData->num = m_IconDir->idCount ;
	for (int i = 0 ; i < m_IconDir->idCount ; ++ i)
	{
		//SEEK
		fin.seekg(m_IconDir->idEntries[i].dwimageoffset,ios_base::beg) ;

		//READ BITMAPINFOHEADER
		fin.read((char*)(&m_IconData->data[i].icheader),sizeof(BITMAPINFOHEADER));

		//READ XOR DATA
		int xornum = WIDTHBYTES(m_IconDir->idEntries[i].bwidth,m_IconDir->idEntries[i].wbitcount)
						* m_IconDir->idEntries[i].bheight; 
		int andnum = WIDTHBYTES(m_IconDir->idEntries[i].bwidth,1)
			* m_IconDir->idEntries[i].bheight;

		m_IconData->data[i].icxor = new byte[xornum];
		fin.read((char*)(m_IconData->data[i].icxor),xornum);

		//READ AND DATA
		m_IconData->data[i].icand = new byte[andnum];
		fin.read((char*)(m_IconData->data[i].icand),andnum);
	}

	fin.close();

	return true ;
}


DWORD  CIconOperate::CalculateImageOffset(const int& index )
{
	DWORD temp = 0 ;
	temp = 3 * sizeof(WORD) + sizeof(ICONDIRENTRY)* m_IconDir->idCount;

	for (int i = 0 ; i < index ; i ++)
	{
		temp += m_IconDir->idEntries[i].dwbytesinres ;
	}

	return temp ;
}
//写数据
#define _using_stream
bool CIconOperate::SaveIcon(const string _str)
{
	if (m_IconDir == NULL || m_IconData == NULL)
		return false ;

	//int  width  = 64 ;
	//int  heigth = 64 ;
	//int  ppx = 32 ;

	fstream fout;
	fout.open(_str.c_str(),ios_base::out | ios_base::binary);  

	//reserved 
	WORD wData = 0 ;
	fout.write((char*)(&wData),sizeof(WORD));
	//type
    wData = 1 ;
	fout.write((char*)(&wData),sizeof(WORD));
	//num
	wData = m_IconDir->idCount ;
    fout.write((char*)(&wData),sizeof(WORD));

	//write ICONDIRENTRY数据
	for (int i = 0 ; i < m_IconDir->idCount ; ++i)
	{
		//ICONDIRENTRY结构
		ICONDIRENTRY iconData ;
		iconData.bwidth  = m_IconDir->idEntries[i].bwidth ;
		iconData.bheight = m_IconDir->idEntries[i].bheight ;
		iconData.bcolorcount  =  0;
		iconData.breserved    =  0 ;
		iconData.wplanes      =  1 ;
		iconData.wbitcount    =  m_IconDir->idEntries[i].wbitcount ;
		iconData.dwbytesinres = sizeof(BITMAPINFOHEADER) 
			+  iconData.bheight * WIDTHBYTES(iconData.bwidth,iconData.wbitcount) 
			+  iconData.bheight * WIDTHBYTES(iconData.bwidth,1);
		iconData.dwimageoffset =  CalculateImageOffset(i) ; 

		fout.write((char*)(&iconData),sizeof(ICONDIRENTRY));
	}


	for (int i = 0 ; i < m_IconDir->idCount ; ++i)
	{
		//BITMAPINFOHEADER结构
		BITMAPINFOHEADER tBitHeader;
		tBitHeader.biSize          = sizeof(BITMAPINFOHEADER);
		tBitHeader.biWidth         = m_IconDir->idEntries[i].bwidth ;
		tBitHeader.biHeight        = m_IconDir->idEntries[i].bheight*2 ;
		tBitHeader.biPlanes        = 1 ;
		tBitHeader.biBitCount      = m_IconDir->idEntries[i].wbitcount ;
		tBitHeader.biCompression   = 0 ;
		tBitHeader.biSizeImage     = 0;
		tBitHeader.biXPelsPerMeter = 0 ;
		tBitHeader.biYPelsPerMeter = 0 ;
		tBitHeader.biClrUsed       = 0 ;
		tBitHeader.biClrImportant  = 0 ;

		fout.write((char*)(&tBitHeader),sizeof(BITMAPINFOHEADER));

		fout.write((char*)m_IconData->data[i].icxor,tBitHeader.biHeight/2 * WIDTHBYTES(tBitHeader.biWidth,tBitHeader.biBitCount));

		fout.write((char*)m_IconData->data[i].icand,tBitHeader.biHeight/2 * WIDTHBYTES(tBitHeader.biWidth,1));

	}

	fout.close();
	
	return true ;
}

//产生测试图标
bool CIconOperate::GenerateTestIcon(const string _str)
{
		int  width  = 128 ;
		int  heigth = 128 ;
		int  ppx = 32 ;

		fstream fout;
		fout.open(_str.c_str(),ios_base::out | ios_base::binary);  


		//reserved 
		WORD wData = 0 ;
		fout.write((char*)(&wData),sizeof(WORD));


		//type
		wData = 1 ;
		fout.write((char*)(&wData),sizeof(WORD));

		//num
		wData = 1 ;
		fout.write((char*)(&wData),sizeof(WORD));

		//ICONDIRENTRY结构
		ICONDIRENTRY iconData ;
		iconData.bwidth  = width ;
		iconData.bheight = heigth ;
		iconData.bcolorcount  =  0;
		iconData.breserved    =  0 ;
		iconData.wplanes      =  1 ;
		iconData.wbitcount    =  ppx;
		iconData.dwbytesinres = sizeof(BITMAPINFOHEADER) 
			+  heigth * WIDTHBYTES(width,ppx) 
			+  heigth * WIDTHBYTES(width,1);
		iconData.dwimageoffset = 3 * sizeof(WORD) + sizeof(ICONDIRENTRY) ;  ; 

		fout.write((char*)(&iconData),sizeof(ICONDIRENTRY));

		//BITMAPINFOHEADER结构
		BITMAPINFOHEADER tBitHeader;
		tBitHeader.biSize          = sizeof(BITMAPINFOHEADER);
		tBitHeader.biWidth         = width ;
		tBitHeader.biHeight        = heigth*2 ;
		tBitHeader.biPlanes        = 1 ;
		tBitHeader.biBitCount      = ppx ;
		tBitHeader.biCompression   = 0 ;
		tBitHeader.biSizeImage     = 0;
		tBitHeader.biXPelsPerMeter = 0 ;
		tBitHeader.biYPelsPerMeter = 0 ;
		tBitHeader.biClrUsed       = 0 ;
		tBitHeader.biClrImportant  = 0 ;

		fout.write((char*)(&tBitHeader),sizeof(BITMAPINFOHEADER));

		//写入xor数据
		byte *imgdata = new byte[heigth * WIDTHBYTES(width,ppx)];
		for (int h= 0 ; h < heigth ; h ++)
		{
			for (int w =0 ; w < width ; w ++)
			{
				int index = (h * WIDTHBYTES(width,ppx) + w*4);
				imgdata[index]   = 255;
				imgdata[index+1] = 0 ;
				imgdata[index+2] = 0 ; 
				imgdata[index+3] = 200 ; 
			}
		}

		fout.write((char*)imgdata,heigth * WIDTHBYTES(width,ppx));
		delete []imgdata ;

		//写入and数据
		byte  *anddata= new byte[heigth * WIDTHBYTES(width,1)];
		for (int i = 0 ; i < heigth * WIDTHBYTES(width,1) ; i ++)
		{
			anddata[i] = 0 ;
		}

		fout.write((char*)imgdata,heigth * WIDTHBYTES(width,1));

		delete []anddata ;

		fout.close();

		return true ;
}
//修改ICON文件数据---
bool  CIconOperate::Modefiy()
{
	if(m_IconData == NULL || m_IconDir == NULL)
		return false ;

	DrawCircle(m_IconDir->idEntries[0].bwidth*3/4,m_IconDir->idEntries[0].bheight*3/4,20,1,0x80ff0000);
	return true ;
}

//在固定位置将点变为红色
void CIconOperate::SetPointColor(int x, int y, DWORD color)
{
	if(m_IconData == NULL || m_IconDir == NULL)
		return  ;

	if (x < 0 || x >= m_IconDir->idEntries[0].bwidth || y < 0 || y >= m_IconDir->idEntries[0].bheight )
		return ;

	int index = (y * WIDTHBYTES(m_IconDir->idEntries[0].bwidth,m_IconDir->idEntries[0].wbitcount) + x*4);
	*(DWORD*)(&m_IconData->data[0].icxor[index]) = color ;
}

// 八对称性
 void CIconOperate::_draw_circle_8(int xc, int yc, int x, int y,DWORD c) 
 {
	SetPointColor(xc + x, yc + y, c);
	SetPointColor(xc - x, yc + y, c);
	SetPointColor(xc + x, yc - y, c);
	SetPointColor(xc - x, yc - y, c);
	SetPointColor(xc + y, yc + x, c);
	SetPointColor(xc - y, yc + x, c);
	SetPointColor(xc + y, yc - x, c);
	SetPointColor(xc - y, yc - x, c);
}

//在内存中画圆形
void CIconOperate::DrawCircle(int xc , int yc, int r ,bool isfill , DWORD c)
{
	if(m_IconData == NULL || m_IconDir == NULL)
		return  ;

	if (xc + r < 0 || xc - r >= m_IconDir->idEntries[0].bwidth ||
		yc + r < 0 || yc - r >= m_IconDir->idEntries[0].bheight)
		return;

	int x = 0, y = r, yi, d;
	d = 3 - 2 * r;

	if (isfill)
	{
		// 如果填充（画实心圆）
		while (x <= y) 
		{
			for (yi = x; yi <= y; yi ++)
				_draw_circle_8(xc, yc, x, yi, c);

			if (d < 0) 
			{
				d = d + 4 * x + 6;
			} 
			else
			{
				d = d + 4 * (x - y) + 10;
				y --;
			}
			x++;
		}
	}
	else 
	{
		// 如果不填充（画空心圆）
		while (x <= y) 
		{
			_draw_circle_8(xc, yc, x, y, c);

			if (d < 0) 
			{
				d = d + 4 * x + 6;
			} 
			else 
			{
				d = d + 4 * (x - y) + 10;
				y --;
			}
			x ++;
		}
	}
}
