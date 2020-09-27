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

class ImgAugment
{
public:

	ImgAugment();

	ImgAugment(vector<double>fangles, vector<double>scales, vector<int>flipcodes, vector<int>iKernels, bool bRatate, bool bFlip, bool bBulur);

	~ImgAugment();
private:

	vector<double>fangles;  //Rotate angle arr

	vector<double>scales;  //Rotate angle arr

	//-X轴翻转，flipcode = 0   - Y轴翻转, flipcode = 1  - XY轴翻转, flipcode = -1

	vector<int>flipcodes;  //反转code 

	bool bRatate;

	bool bFlip;

	bool bBulur;

	vector<int>iKernels;
	

private:

	/***
	* @brief blur the img
	* @param img - input image
	* @param iKernelSize - kernel Size
	*/
	Mat BlurImg(const Mat& img, int iKernelSize);

	/***
	* @brief Rotate the img
	* @param img - input image 
	* @param fAngle - Rotate angle 
	* @param scale - scale 
	*/
	Mat RoateImg(const Mat& img, const double& fAngle,const double&scale);

	/***
	* @brief flip the img
	* @param img - input image
	* @param flipCode - flipCode 
	*/
	Mat FlipImg(const Mat& img, int flipCode);

public:
	/***
	* @brief expand the dataset 
	* @param filename - the filename of img 
	* @param sLabeldir - the dir of label img
	* @param sOutfiledir - output dir
	*/
	void DataAugments(const string& ImgPath,const string &sLabeldir, string sOutfiledir);

};

