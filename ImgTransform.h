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
class ImgTransform
{
public:
	ImgTransform();
	~ImgTransform();

private:


	/***
	* @brief img ---> [0,1]
	* @param img - input image
	*/
	Mat Transform(const Mat& img);

public:

	/***
	* @brief batch process
	* @param sInputPath - input image dir
	* * @param sOutPath - sOut image dir
	*/
	void RunTranform(const string& sInputPath, const string sOutPath);
};

