#include "stdafx.h"
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <cxcore.h>
#include <iostream>
#include <vector>
#include <fstream>//fstream供给了三个类，用来实现c++对文件的操纵
#include <iomanip>

extern CString file_address; //选择打开的文件地址
using namespace std;
using namespace cv;
extern float hang, lie;
extern float alpha , beta , gamma ;

int getFrameCount() {

	VideoCapture capture("QJ.avi");
	int aaa;
	if (!capture.isOpened())
	{
		cout << "读取视频有误" << endl;
		return -1;
	}
	else
	{
		aaa = capture.get(CV_CAP_PROP_FRAME_COUNT);//获取视频的总帧数
	}
	return aaa;
}

int getFps() {
	VideoCapture capture("QJ.avi");
	int fff;
	if (!capture.isOpened())
	{
		cout << "读取视频有误" << endl;
		return -1;
	}
	else
	{
		
		fff = capture.get(CAP_PROP_FPS);//获取视频的总帧数
	}
	return fff;
}

int testBJC()
{
	Mat background;
	Mat temp;
	Mat result;
	int FrameCount = 0;
	ofstream File;//ofstream类实现向文件写内容

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
		resize(background, background, Size(hang, lie));//resize为300*200的图像，原来是720*480
		cvtColor(background, background, CV_RGB2GRAY);//转为灰度图
		File.open("test.xls", ios::trunc | fstream::trunc);//ios::_Noreplace 打开一个文件时，如果文件不存在，创建该文件
		vector<int>ivec(totalFrameNumber);//可变数组ivec，大小为总帧

		VideoWriter writer("QJ.avi", VideoWriter::fourcc('M', 'P', '4', '2'), fps, Size(hang, lie), 0);

		while (capture.read(temp))
		{

			

			FrameCount++;
			resize(temp, temp, Size(hang, lie));//resize为300*200的图像，原来是720*480
			cvtColor(temp, temp, CV_RGB2GRAY);//转为灰度图
			absdiff(background, temp, result);//和背景作差,输出result
			addWeighted(background, alpha, temp, beta, gamma, background);

				Mat img = result;
				int c = 300; //图像列数
				int r = 200; //图像行数
				int T = 0; //阈值
				uchar* data = img.data; //数据指针
				int ftNum = 0; //前景像素个数
				int bgNum = 0; //背景像素个数
				int N = c * r; //总像素个数
				int ftSum = 0; //前景总灰度值
				int bgSum = 0; //背景总灰度值
				int graySum = 0;
				double w0 = 0; //前景像素个数占比
				double w1 = 0; //背景像素个数占比
				double u0 = 0; //前景平均灰度
				double u1 = 0; //背景平均灰度
				double Histogram[256] = { 0 }; //灰度直方图
				double temp1 = 0; //临时类间方差
				double g = 0; //类间方差

							  //灰度直方图
				for (int i = 0; i < r; i++) {
					for (int j = 0; j <c; j++) {
						Histogram[img.at<uchar>(i, j)]++;
					}
				}
				//求总灰度值
				for (int i = 0; i < 256; i++) {
					graySum += Histogram[i] * i;
				}

				for (int i = 0; i < 256; i++) {
					ftNum += Histogram[i];  //阈值为i时前景个数
					bgNum = N - ftNum;      //阈值为i时背景个数
					w0 = (double)ftNum / N; //前景像素占总数比
					w1 = (double)bgNum / N; //背景像素占总数比
					if (ftNum == 0) continue;
					if (bgNum == 0) break;
					//前景平均灰度
					ftSum += i * Histogram[i];
					u0 = ftSum / ftNum;

					//背景平均灰度
					bgSum = graySum - ftSum;
					u1 = bgSum / bgNum;

					g = w0 * w1*(u0 - u1)*(u0 - u1);
					if (g > temp1) {
						temp1 = g;
						T = i;
					}
				}
				int PixelCount = 0;

				for (int i = 0; i<img.rows; i++)
				{
					for (int j = 0; j<img.cols; j++)
					{
						if ((int)img.at<uchar>(i, j) > T) {
							img.at<uchar>(i, j) = 255;
							PixelCount++;
						}
						else
							img.at<uchar>(i, j) = 0;
					}
				}
			img.convertTo(img, CV_8U);
			writer << img;
			File << PixelCount << endl;	//写入excel
		}
	}
	File.close();//释放
	return 0;
}