#include "ImgAugment.h"


ImgAugment::ImgAugment()
{
}

ImgAugment::ImgAugment(vector<double>fangles, vector<double>scales, vector<int>flipcodes, vector<int>iKernels, bool bRatate, bool bFlip, bool bBulur)
{
	this->bRatate = bFlip;
	this->bFlip = bFlip;
	this->bBulur = bBulur;
	for (int iCount = 0; iCount < fangles.size(); iCount++)
	{
		this->fangles.push_back(fangles[iCount]);
		this->scales.push_back(scales[iCount]);
	}
	for (int iCount = 0; iCount < flipcodes.size(); iCount++)
	{
		this->flipcodes.push_back(flipcodes[iCount]);
	}
	for (int iCount = 0; iCount < iKernels.size(); iCount++)
		this->iKernels.push_back(iKernels[iCount]);

}

ImgAugment::~ImgAugment()
{
	vector<double>().swap(this->fangles);
	vector<double>().swap(this->scales);
	vector<int>().swap(this->flipcodes);
	vector<int>().swap(this->iKernels);
	this->bRatate = false;
	this->bFlip = false;
	this->bBulur = false;
}
Mat ImgAugment::BlurImg(const Mat& img, int iKernelSize)
{
	Mat mSrc = img.clone();
	Mat dstImg = img.clone();
	blur(mSrc, dstImg, Size(iKernelSize, iKernelSize));
	return dstImg;
}
Mat ImgAugment::RoateImg(const Mat& img, const double& angle, const double& scale)
{
	Mat mSrc = img.clone();
	Point center(mSrc.cols / 2, mSrc.rows / 2); //Ðý×ªÖÐÐÄ
	Mat rotMat = getRotationMatrix2D(center, angle, scale);
	Mat dstimg = mSrc.clone();
	warpAffine(mSrc, dstimg, rotMat, img.size());
	return dstimg;
}
Mat ImgAugment::FlipImg(const Mat& img, int flipCode)
{
	Mat mSrc = img.clone();
	Mat dstImg = mSrc.clone();
	flip(mSrc, dstImg, flipCode);
	return dstImg;
}
void ImgAugment::DataAugments(const string& ImgPath, const string& sLabeldir,string sOutfiledir)
{
	string soutImgDir = sOutfiledir + "src\\";
	string soutLabelDir = sOutfiledir + "lable\\";
	vector<string>filename;
	glob(ImgPath, filename, false);

	int ivecSize = filename.size();

	cout << "output img dir :" << soutImgDir << endl << "output label dir : " << soutLabelDir << endl;

	cout << "Total image size  : " << ivecSize << endl << "----------------------begin to Run-----------------" << endl << endl;


	for (int idx = 0; idx < ivecSize; idx++)
	{
		cout << "************************************************************" << endl;
		cout << "the current img is the " << idx << "  " << endl;
		int iterator = -1;
		string sCurFn = filename[idx];
		int ipos = sCurFn.find_last_of("\\") + 1;
		string simgName = sCurFn.substr(ipos, sCurFn.length());
		int ips = simgName.find_last_of(".");
		string sName = simgName.substr(0, ips);
		//label img name
		string sLabelImgName = sLabeldir + simgName;


		Mat mSrc = imread(sCurFn);
		Mat mLable = imread(sLabelImgName);


		//start Roate
		if (bRatate) {
			cout << "----------------------------- " << endl;
			cout << "print the Roate reuslt : " << endl;
			for (int m = 0; m < fangles.size(); m++)
			{
				iterator = iterator + 1;
				string soutImgName = soutImgDir + sName + "_" + to_string(iterator) + ".png";
				string soutLabelName = soutLabelDir + sName + "_" + to_string(iterator) + ".png";
				Mat imgRotate = RoateImg(mSrc, fangles[m], scales[m]);
				Mat labelRotate = RoateImg(mLable, fangles[m], scales[m]);
				imwrite(soutImgName, imgRotate);
				imwrite(soutLabelName, labelRotate);
				cout << soutImgName << endl << soutLabelName << endl;
				
			}
		}
		// Roate finished
		//start flip
		if (bFlip) {
			cout << "----------------------------- " << endl;
			cout << "print the Flip reuslt : " << endl;
			for (int n = 0; n < flipcodes.size(); n++) {

				iterator = iterator + 1;
				string soutImgName = soutImgDir + sName + "_" + to_string(iterator) + ".png";
				string soutLabelName = soutLabelDir + sName + "_" + to_string(iterator) + ".png";
				Mat imgFlip = FlipImg(mSrc, flipcodes[n]);
				Mat labelFlip = FlipImg(mLable, flipcodes[n]);
				imwrite(soutImgName, imgFlip);
				imwrite(soutLabelName, labelFlip);
				cout << soutImgName << endl << soutLabelName << endl;
			}

		}
		//end flip

		//start blur
		if (bBulur) {
			cout << "----------------------------- " << endl;
			cout << "print the Blur reuslt : " << endl;
			for (int n = 0; n < iKernels.size(); n++) {

				iterator = iterator + 1;
				string soutImgName = soutImgDir + sName + "_" + to_string(iterator) + ".png";
				string soutLabelName = soutLabelDir + sName + "_" + to_string(iterator) + ".png";
				Mat imgFlip = BlurImg(mSrc, iKernels[n]);
				Mat labelFlip = BlurImg(mLable, iKernels[n]);
				imwrite(soutImgName, imgFlip);
				imwrite(soutLabelName, labelFlip);
				cout << soutImgName << endl << soutLabelName << endl;
			}

		}
		//end blur

	}
	cout << "----------------------end to Run-----------------" << endl;
}