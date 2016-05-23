#include <cv.h>
#include <opencv2/core.hpp> 
#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc/imgproc.hpp> 
#include <highgui.h>
#include <math.h>
#include "CEdge.h"

using namespace std;
using namespace cv;

void FillInternalContours(IplImage *pBinary);

int main(int argc, char* argv[])
{
	char srcName[] = "src.jpg";
	IplImage * src = cvLoadImage(srcName, 0);
	IplImage * img = cvLoadImage(srcName, 0);
	IplImage * imgSrc = img;
	CvSize sizeSrc = cvGetSize(imgSrc);

	CvScalar mean = 0;
	CvScalar std = 0;
	double minValue = 0, maxValue = 0;
	cvAvgSdv(imgSrc, &mean, &std);
	cvMinMaxLoc(imgSrc, &minValue, &maxValue);

	Rect ccomp;

	CEdge edgeTemp;
	edgeTemp.extractEdge(srcName);
	imgSrc = edgeTemp.getEdge();

	FillInternalContours(imgSrc);
	for (int i = 0; i < sizeSrc.width; i+=5)
	{
		for (int j = 0; j < sizeSrc.height; j+=5)
		{
			float tmp = CV_IMAGE_ELEM(src, float, j, i);
			if (tmp > mean.val[0] + std.val[0])
			{
				cvFloodFill(src, Point(i, j), CV_RGB(255, 255, 255), Scalar(20, 20, 20), Scalar(50, 50, 50));
			}
		}
	}
	cvNamedWindow("Result1", CV_WINDOW_AUTOSIZE);
	cvShowImage("Result1", imgSrc);

	cvMax(img, imgSrc, imgSrc);
	for (int i = 0; i < sizeSrc.width; i += 5)
	{
		for (int j = 0; j < sizeSrc.height; j += 5)
		{
			float tmp = CV_IMAGE_ELEM(imgSrc, float, j, i);
			if (tmp > mean.val[0] + std.val[0])
			{
				cvFloodFill(imgSrc, Point(i, j), CV_RGB(255, 255, 255), Scalar(20, 20, 20), Scalar(50, 50, 50));
			}
		}
	}
	cvMin(src, imgSrc, imgSrc);

	cvNamedWindow("Result2", CV_WINDOW_AUTOSIZE);
	cvShowImage("Result2", imgSrc);

	waitKey(0);

	cvDestroyWindow("Result1");
	cvDestroyWindow("Result2");
	cvReleaseImage(&src);
	cvReleaseImage(&img);
	cvReleaseImage(&imgSrc);

	return 0;
}

void FillInternalContours(IplImage *pBinary)
{
	double dConArea;
	CvSeq *pContour = NULL;
	CvSeq *pConInner = NULL;
	CvMemStorage *pStorage = NULL;
   
	if (pBinary)
	{  
		pStorage = cvCreateMemStorage(0);
		cvFindContours(pBinary, pStorage, &pContour, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
		cvDrawContours(pBinary, pContour, 0, 0, 2, 1, 8, cvPoint(0, 0));
		for (; pContour != NULL; pContour = pContour->h_next)
		{ 
			for (pConInner = pContour->v_next; pConInner != NULL; pConInner = pConInner->h_next)
			{
				cvDrawContours(pBinary, pConInner, 0, 255, 0, 1, 8, cvPoint(0, 0));
			}
		}
		cvReleaseMemStorage(&pStorage);
		pStorage = NULL;
	}
}