/*
Developed by Marcio Brito Barbosa;
Email: mbb2@cin.ufpe.br
Version: 1.0
**/

#ifndef PDI_IMAGES_H
#define PDI_IMAGES_H

#include <iostream>
#include <cstdlib>
#include "/usr/local/include/opencv/cv.h"
#include "/usr/local/include/opencv/highgui.h"

#define PDI_SUCCESS			1
#define PDI_FAIL			0
#define PDI_RED				2
#define PDI_GREEN 			1
#define PDI_BLUE 			0

class PdiImage {
public:
	PdiImage(int *codep);
	PdiImage(char *pathp, int *codep);
	int getWidth(void);
	int getHeight(void);
	int getImageColor(float **imgp, int color, int widthp, int heightp);
	void setImage(char *pathp, int *codep);
	int thresholdImage(char *namep, float **Y, float **Cb, float **Cr, int widthp, int heightp);
	int saveImageMerge(char *namep, float **redp, float **greenp, float **bluep, int widthp, int heightp);
private:
	IplImage *img;
};

#endif