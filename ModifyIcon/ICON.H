
/*
	定义ICON文件需要的结构信息
*/

#pragma once

#include<iostream>
#include<stdio.h>

//ICON文件存储格式
typedef struct
{
	byte        bwidth;          // width, in pixels, of the image
	byte        bheight;         // height, in pixels, of the image
	byte        bcolorcount;     // number of colors in image (0 if >=8bpp)
	byte        breserved;       // reserved ( must be 0)
	WORD        wplanes;         // color planes
	WORD        wbitcount;       // bits per pixel
	DWORD       dwbytesinres;    // how many bytes in this resource?
	DWORD       dwimageoffset;   // where in the file is this image?
} ICONDIRENTRY, *LPICONDIRENTRY;

//ICON文件目录
typedef struct 
{
	WORD			idReserved;   // Reserved
	WORD			idType;       // resource type (1 for icons)
	WORD			idCount;      // how many images?
	ICONDIRENTRY	idEntries[1]; // the entries for each image
} ICONDIR, *LPICONDIR;


//ICON文件数据存储格式
typedef struct
{
	BITMAPINFOHEADER    icheader;      // dib header
	RGBQUAD				iccolors[1];   // color table
	byte                icxor[1];      // dib bits for xor mask
	byte                icand[1];      // dib bits for and mask
} iconimage, *lpiconimage;

//===========================程序中使用的格式

//图像数据存储
struct stImageData
{
	BITMAPINFOHEADER   icheader;              // ptr to header
	byte*          icxor ;
	byte*          icand ;

	stImageData()
	{
		icand = NULL ;
		icxor = NULL ;
	}
};

//ICON图像整体组成
struct  stIconData
{
	int num ;
	stImageData data[1];
	stIconData()
	{
		num = 0 ; 
	}
};

struct stIcon
{
	ICONDIR *dir ;
	stIconData *icon ;

	stIcon()
	{
		dir = NULL ;
		icon = NULL ;
	}
};