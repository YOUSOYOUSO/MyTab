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

int testBJC()
{
	Mat background;
	Mat temp;
	Mat result;
	int FrameCount = 0;

	const wchar_t* wstr = (LPCTSTR)file_address;     //一定得是unicode，否则这句话会错的
	char str[20] = { 0 };
	wcstombs(str, wstr, wcslen(wstr));
	//以上是完成了从CString 到 char* 的转换，将file_address的值传给str

	VideoCapture capture(str);
	int size;
	if (!capture.isOpened())
	{
		cout << "读取视频有误" << endl;
		return -1;
	}
	else
	{

		int fps = (int)capture.get(CAP_PROP_FPS);
		long totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);//获取视频的总帧数
		capture.read(background);
		resize(background, background, Size(300, 200));//resize为300*200的图像，原来是720*480
		cvtColor(background, background, CV_RGB2GRAY);//转为灰度图

		ofstream File;//ofstream类实现向文件写内容
		File.open("test.xls", ios::_Noreplace | fstream::trunc);//ios::_Noreplace 打开一个文件时，如果文件不存在，创建该文件
		vector<int>ivec(totalFrameNumber);//可变数组ivec，大小为总帧

		VideoWriter writer("QJ.avi", VideoWriter::fourcc('M', 'P', '4', '2'), fps, Size(300, 200), 0);

		while (capture.read(temp))
		{

			int PixelCount = 0;

			FrameCount++;
			resize(temp, temp, Size(300, 200));//resize为300*200的图像，原来是720*480
			cvtColor(temp, temp, CV_RGB2GRAY);//转为灰度图
			absdiff(background, temp, result);//和背景作差,输出result
			addWeighted(background, 0.98, temp, 1 - 0.98, 0, background);

			//遍历图像，二值化，阈值为50
			for (int i = 0; i < result.rows; i++) {
				for (int j = 0; j < result.cols; j++) {
					if (result.at<uchar>(i, j) < 50) {
						result.at<uchar>(i, j) = 0;
					}
					else {
						PixelCount++;
						result.at<uchar>(i, j) = 255;
					}
				}
			}
			result.convertTo(result, CV_8U);
			writer << result;
			File << PixelCount << endl;	//写入excel
		}

		File.close();//释放
	}
	return 0;
}