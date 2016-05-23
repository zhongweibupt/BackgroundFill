/*
* Edge.cpp
* class Edge
* Description: Extract edge feature of picture(Canny)
* public:
*	int setEdgeThresh(int edgeThresh)
*	int extractEdge(char* fileName)
*	int cEdgeShow(void)
*	int edgeShow(void)
*	IplImage* getCEdge(void)
*	IplImage* getEdge(void)
*
* private:
*	int edgeThresh
*	char* fileName
*	IplImage* image
*	IplImage* grayImage
*	IplImage* cEdge
*	IplImage* edge
*/
#ifndef CEDGE_H
#define CEDGE_H

#include "cv.h"


class CEdge
{
private:
	int edgeThresh = 100;
	char* fileName;
	IplImage* image = 0;
	IplImage* gray = 0;
	IplImage* cEdge = 0;
	IplImage* edge = 0;

public:
	int setEdgeThresh(int thresh);
	int extractEdge(char* str);
	int cEdgeShow(void);
	int edgeShow(void);
	IplImage* getCEdge(void);
	IplImage* getEdge(void);
	int releaseImage(void);
};


#endif