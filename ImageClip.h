#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<iostream>
#include<string.h>
#include<math.h>
#include <fstream>
#include"sstream"
#include <stdint.h>

using namespace cv;
using namespace std;
class ImageClip
{
public:
	ImageClip();

	ImageClip(string soutDir, int  iWidth,int iHeight, int iStride, bool bshowClipResult);

	~ImageClip();

private:

	string soutDir;

	int iWidth;

	int iHeight;

	int iStride;

	bool bshowClipResult;

private:

	/***
	* @brief clip the input img by iWidth ,iHeight iStride
	* @param sFileName - input image filename 
	* @param sLabeldir - input label dirpath
	* @param imgdir - output roiImg dirpath
	* @param labeldir - output labelRoi dirpath
	*/
	void ClipImg(const string& sFileName,const string &sLabeldir,const string&imgdir,const string &labeldir);

public:
	/***
	* @brief Run this function to get Roi
	* @param sImgPath - input image dirpath
	* @param sLablePath - input label dirpath
	*/
	void RunClipImg(const string& sImgPath, const string& sLablePath);



};

