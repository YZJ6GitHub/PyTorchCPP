#pragma once
#include"ImgAugment.h"
#include"ImageClip.h"

using namespace cv;
using namespace std;



int data_augment_Test(string path, string sLabelDir, string sout)
{
    vector<String> fn;
    bool bRotate = true;
    bool bFlip = true;
    vector<double>angles;
    angles.push_back(90);
    angles.push_back(180);
    vector<double>scales(2, 1);
    vector<int>flipcodes;
    flipcodes.push_back(0);
    flipcodes.push_back(1);
    flipcodes.push_back(-1);
    vector<int>iKernel;
    iKernel.push_back(3);
    bool bBlur = true;
    ImgAugment pObj(angles, scales, flipcodes, iKernel, bRotate, bFlip, bBlur);
    pObj.DataAugments(path, sLabelDir, sout);
    return 0;
}


void Clip_Test(const string &path, const string &sLabelDir,const string &sout)
{
    ImageClip cObj(sout, 70, 80, 80, true);
    cObj.RunClipImg(path, sLabelDir);
}
int main()
{
    string path = "D:\\vscode\\PyTorch\\Pytorch-UNet-master\\Pytorch-UNet-master\\data\\input_Src\\*.png";
    //±êÇ©Â·¾¶
    string sLabelDir = "D:\\vscode\\PyTorch\\Pytorch-UNet-master\\Pytorch-UNet-master\\data\\input_Label\\";
    string sout = ".\\outs\\";
    bool bAugment = false;
    if (bAugment)
        data_augment_Test(path, sLabelDir, sout);
    else
        Clip_Test(path, sLabelDir, sout);





}
