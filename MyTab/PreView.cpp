#include "stdafx.h"
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
#include<vector>
#include <fstream>//fstream供给了三个类，用来实现c++对文件的操纵
#include <iomanip>

extern CString file_address; //选择打开的文件地址
using namespace std;
using namespace cv;

extern float hang, lie;
extern float alpha, beta, gamma;
extern float boundary;

int PView()
{
	Mat background;
	Mat temp;
	Mat result;

	return 0;
}