#include "ImgTransform.h"

ImgTransform::ImgTransform()
{

}
ImgTransform::~ImgTransform()
{

}
Mat ImgTransform::Transform(const Mat& img)
{
	Mat mSrc = img.clone();
	Mat Gray = mSrc.clone();
	if (mSrc.channels() != 1)
		cvtColor(mSrc, Gray, COLOR_BGR2GRAY);
	Mat dst = Gray.clone();
	int iTotalNum = mSrc.rows * mSrc.cols;
	for (int idx = 0; idx < iTotalNum; idx++)
	{
		if (Gray.data[idx] != 0)
			dst.data[idx] = 1;
	}
	return dst;
}
void ImgTransform::RunTranform(const string& sInputPath, const string sOutPath)
{
	vector<string>fn;
	glob(sInputPath, fn, false);
	for (int idx = 0; idx < fn.size(); idx++)
	{
		string sCurImg = fn[idx];
		int ipos = sCurImg.find_last_of("\\") + 1;
		string simgName = sCurImg.substr(ipos, sCurImg.length());
		Mat img = imread(sCurImg);
		Mat dst = Transform(img);
		string sOutPath = sOutPath + simgName;
		imwrite(sOutPath, dst);

	}
}