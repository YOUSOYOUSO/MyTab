#include "stdafx.h"
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <cxcore.h>
#include <iostream>
#include <vector>
#include <fstream>//fstream�����������࣬����ʵ��c++���ļ��Ĳ���
#include <iomanip>

extern CString file_address; //ѡ��򿪵��ļ���ַ
using namespace std;
using namespace cv;
extern float hang, lie;
extern float alpha , beta , gamma ;

int getFrameCount() {

	VideoCapture capture("QJ.avi");
	int aaa;
	if (!capture.isOpened())
	{
		cout << "��ȡ��Ƶ����" << endl;
		return -1;
	}
	else
	{
		aaa = capture.get(CV_CAP_PROP_FRAME_COUNT);//��ȡ��Ƶ����֡��
	}
	return aaa;
}

int getFps() {
	VideoCapture capture("QJ.avi");
	int fff;
	if (!capture.isOpened())
	{
		cout << "��ȡ��Ƶ����" << endl;
		return -1;
	}
	else
	{
		
		fff = capture.get(CAP_PROP_FPS);//��ȡ��Ƶ����֡��
	}
	return fff;
}

int testBJC()
{
	Mat background;
	Mat temp;
	Mat result;
	int FrameCount = 0;
	ofstream File;//ofstream��ʵ�����ļ�д����

	const wchar_t* wstr = (LPCTSTR)file_address;     //һ������unicode��������仰����
	char str[20] = { 0 };
	wcstombs(str, wstr, wcslen(wstr));
	//����������˴�CString �� char* ��ת������file_address��ֵ����str

	VideoCapture capture(str);
	int size;
	if (!capture.isOpened())
	{
		cout << "��ȡ��Ƶ����" << endl;
		return -1;
	}
	else
	{

		int fps = (int)capture.get(CAP_PROP_FPS);
		long totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);//��ȡ��Ƶ����֡��
		capture.read(background);
		resize(background, background, Size(hang, lie));//resizeΪ300*200��ͼ��ԭ����720*480
		cvtColor(background, background, CV_RGB2GRAY);//תΪ�Ҷ�ͼ
		File.open("test.xls", ios::trunc | fstream::trunc);//ios::_Noreplace ��һ���ļ�ʱ������ļ������ڣ��������ļ�
		vector<int>ivec(totalFrameNumber);//�ɱ�����ivec����СΪ��֡

		VideoWriter writer("QJ.avi", VideoWriter::fourcc('M', 'P', '4', '2'), fps, Size(hang, lie), 0);

		while (capture.read(temp))
		{

			

			FrameCount++;
			resize(temp, temp, Size(hang, lie));//resizeΪ300*200��ͼ��ԭ����720*480
			cvtColor(temp, temp, CV_RGB2GRAY);//תΪ�Ҷ�ͼ
			absdiff(background, temp, result);//�ͱ�������,���result
			addWeighted(background, alpha, temp, beta, gamma, background);

				Mat img = result;
				int c = 300; //ͼ������
				int r = 200; //ͼ������
				int T = 0; //��ֵ
				uchar* data = img.data; //����ָ��
				int ftNum = 0; //ǰ�����ظ���
				int bgNum = 0; //�������ظ���
				int N = c * r; //�����ظ���
				int ftSum = 0; //ǰ���ܻҶ�ֵ
				int bgSum = 0; //�����ܻҶ�ֵ
				int graySum = 0;
				double w0 = 0; //ǰ�����ظ���ռ��
				double w1 = 0; //�������ظ���ռ��
				double u0 = 0; //ǰ��ƽ���Ҷ�
				double u1 = 0; //����ƽ���Ҷ�
				double Histogram[256] = { 0 }; //�Ҷ�ֱ��ͼ
				double temp1 = 0; //��ʱ��䷽��
				double g = 0; //��䷽��

							  //�Ҷ�ֱ��ͼ
				for (int i = 0; i < r; i++) {
					for (int j = 0; j <c; j++) {
						Histogram[img.at<uchar>(i, j)]++;
					}
				}
				//���ܻҶ�ֵ
				for (int i = 0; i < 256; i++) {
					graySum += Histogram[i] * i;
				}

				for (int i = 0; i < 256; i++) {
					ftNum += Histogram[i];  //��ֵΪiʱǰ������
					bgNum = N - ftNum;      //��ֵΪiʱ��������
					w0 = (double)ftNum / N; //ǰ������ռ������
					w1 = (double)bgNum / N; //��������ռ������
					if (ftNum == 0) continue;
					if (bgNum == 0) break;
					//ǰ��ƽ���Ҷ�
					ftSum += i * Histogram[i];
					u0 = ftSum / ftNum;

					//����ƽ���Ҷ�
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
			File << PixelCount << endl;	//д��excel
		}
	}
	File.close();//�ͷ�
	return 0;
}