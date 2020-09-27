#include "ImageClip.h"

using namespace cv;

ImageClip::ImageClip()
{

}

ImageClip::ImageClip(string soutDir, int  iWidth, int iHeight, int iStride, bool bshowClipResult)
{
	this->soutDir = soutDir;
	this->iWidth = iWidth;
	this->iHeight = iHeight;
	this->iStride = iStride;
	this->bshowClipResult = bshowClipResult;

}
ImageClip::~ImageClip()
{

}
void ImageClip::ClipImg(const string& sFileName, const string& sLabeldir,const string& imgdir, const string& labeldir)
{

	int ipos = sFileName.find_last_of("\\") + 1;
	string simgName = sFileName.substr(ipos, sFileName.length());
	int ips = simgName.find_last_of(".");
	string sName = simgName.substr(0, ips);
	int iCount = -1;
	//读取原始图像和标签图像
	Mat img = imread(sFileName);
	Mat showImg = img.clone();
	string sLablePath = sLabeldir + simgName;
	Mat lableImg = imread(sLablePath);
	Mat labelshow = lableImg.clone();

	//计算分割的行列号
	int iRows = img.rows;
	int iCols = img.cols;
	int iColNum = (iCols - iWidth)/iStride + 1;
	int iRowNum = (iRows - iHeight) / iStride + 1;

	if ((iCols - iWidth) % iStride > iWidth * 0.1)
		iColNum += 1;
	if ((iRows - iHeight) % iStride > iHeight * 0.1)
		iRowNum += 1;

	for (int iRow = 0; iRow < iRowNum; iRow++)
	{
		for (int iCol = 0; iCol < iColNum; iCol++)
		{
			iCount++;
			int x = iCol * iStride;
			int y = iRow * iStride;
			Rect rect;
			rect.width = iWidth;
			rect.height = iHeight;
			if (x + iWidth <= iCols)
				rect.x = x;
			else
				rect.x = x - (x + iWidth - iCols);

			if (y + iHeight <= iRows)
				rect.y = y;
			else
				rect.y = y - 1 - (y + iHeight - iRows);
			//cout << rect.x << "  " << rect.y << endl;
			if (iCount % 2 == 0)
			{
				cv::rectangle(showImg, rect, Scalar(255, 0, 0), 1, 8, 0);
				cv::rectangle(labelshow, rect, Scalar(255, 0, 0), 1, 8, 0);
			}
			else
			{
				cv::rectangle(showImg, rect, Scalar(0, 0, 255), 1, 8, 0);
				cv::rectangle(labelshow, rect, Scalar(0, 0, 255), 1, 8, 0);
			}
				
			Mat img_roi = img(rect);
			Mat label_Roi = lableImg(rect);


			string soutImg = imgdir + sName + "_" + to_string(iCount) + ".png";
			string soutLabel = labeldir + sName + "_" + to_string(iCount) + ".png";

			imwrite(soutImg, img_roi);
			imwrite(soutLabel, label_Roi);
			/*namedWindow("showImg", 0);
			cout << roi.cols << "   " << roi.rows << endl;
			imshow("showImg", showImg);
			waitKey(200);*/

		}
	}
	if (bshowClipResult)
	{
		string sImgShow = sName + "_Img.png";
		string sLableShow = sName + "_Lable.png";
		imwrite(sImgShow, showImg);
		imwrite(sLableShow, labelshow);
	}

}

void ImageClip::RunClipImg(const string& sImgPath, const string& sLablePath)
{
	vector<string>fn;
	glob(sImgPath, fn, false);
	string imgdir = soutDir + "src\\";
	string labeldir = soutDir + "lable\\";
	for (int idx = 0; idx < fn.size(); idx++)
	{
		string sCurFileName = fn[idx];
		ClipImg(sCurFileName, sLablePath, imgdir, labeldir);
	}
}
