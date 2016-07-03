#include "gmm.h"
using namespace cv;
using namespace std;

int main()
{
	bool flag;
	Vec3b intensity;
	int r, c;
	
	int i = 0;
	char s[11];
	char n2s[6];
	Mat img0, fgmask, fgimg;
	Mat img(120, 160, CV_8UC1);

	strcpy(s, "b");
	sprintf_s(n2s, "%05d", i);
	strcat_s(s, n2s);
	strcat_s(s, ".bmp");
	img0 = imread(s, CV_LOAD_IMAGE_COLOR);
	const int row_n = img0.rows;
	const int col_n = img0.cols;
	gmm_c **p1 = new gmm_c*[row_n];												//create gmm buffer
	for(i = 0; i < row_n; i++)
		p1[i] = new gmm_c[col_n];

	for (i = 0; i < frame_s; i++)
	{
		strcpy(s, "b");
		sprintf_s(n2s, "%05d", i);
		strcat_s(s, n2s);
		strcat_s(s, ".bmp");
		img0 = imread(s, CV_LOAD_IMAGE_COLOR);   // Read the file
		//cvtColor(img0, img0, CV_BGR2GRAY);
		if (!img0.data)                              // Check for invalid input
		{
			cout << "Could not open or find the image" << std::endl;
			return -1;
		}
		for (r = 0; r < img0.rows; r++)
		{
			for (c = 0; c < img0.cols; c++)
			{
				flag = p1[r][c].gmm_bgs(&p1[r][c], intensity);
				intensity = img0.at<Vec3b>(r, c);
				if (0 == flag)											//0 == flag means foreground
				{
					img.at<uchar>(r, c) = 255;
				}
				if (1 == flag)											//background
				{
					img.at<uchar>(r, c) = 0;
				}
			}
		}
		imshow("original",img0);						//show original frame
		imshow("foreground", img);						//show binary foreground frame
		waitKey(30);
	}
	
	namedWindow(s, WINDOW_AUTOSIZE);// Create a window for display.
	imshow(s, img);                  
	waitKey(6000);
	for (i = 0; i < row_n; i++)
		delete[] p1[i];

	delete p1;
	return 0;
}
