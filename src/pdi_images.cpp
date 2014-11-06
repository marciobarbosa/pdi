/*
Developed by Marcio Brito Barbosa;
Email: mbb2@cin.ufpe.br
Version: 1.0
**/

#include "../hdr/pdi_images.h"

PdiImage::PdiImage(int *codep) {
	this->img = NULL;
	*codep = PDI_FAIL;
}

PdiImage::PdiImage(char *pathp, int *codep) {
	if ((this->img = cvLoadImage(pathp, CV_LOAD_IMAGE_COLOR))) {
		*codep = PDI_SUCCESS;
	} else {
		*codep = PDI_FAIL;
	}
}

int PdiImage::getWidth(void) {
	return this->img->width;
}

int PdiImage::getHeight(void) {
	return this->img->height;
}

int PdiImage::getImageColor(float **imgp, int color, int widthp, int heightp) {
	uchar *pImg = (uchar *)this->img->imageData;

	if (widthp < this->getWidth() || heightp < this->getHeight())
		return PDI_FAIL;

	if (color > 2 || color < 0)
		return PDI_FAIL;

	for (int i = 0; i < this->getHeight(); i++) {
		for (int j = 0; j < this->getWidth(); j++) {
			imgp[i][j] = pImg[i * this->img->widthStep + j * this->img->nChannels + color];
		}
	}

	return PDI_SUCCESS;
}

void PdiImage::setImage(char *pathp, int *codep) {
	if ((this->img = cvLoadImage(pathp, CV_LOAD_IMAGE_COLOR))) {
		*codep = PDI_SUCCESS;
	} else {
		*codep = PDI_FAIL;
	}
}

int PdiImage::thresholdImage(char *namep, float **Y, float **Cb, float **Cr, int widthp, int heightp) {
	IplImage *img_out = cvCreateImage(cvSize(this->img->width, this->img->height), IPL_DEPTH_8U, 1);
	uchar *raw_img = (uchar *)img_out->imageData;

	if (widthp != this->getWidth() || heightp != this->getHeight() || !img_out) {
		return PDI_FAIL;
	}

	for (int i = 0; i < heightp; i++) {
		for (int j = 0; j < widthp; j++) {
			if (Y[i][j] < 50 || (Cr[i][j] > 115 && Cr[i][j] < 180) || (Cb[i][j] > 85 && Cb[i][j] < 135))
				raw_img[i * img_out->widthStep + j] = 255;
			else
				raw_img[i * img_out->widthStep + j] = 0;
		}
	}

	cvSaveImage(namep, img_out);

	return PDI_SUCCESS;
}

int PdiImage::saveImageMerge(char *namep, float **redp, float **greenp, float **bluep, int widthp, int heightp) {
	IplImage *img_out = cvCreateImage(cvSize(this->img->width, this->img->height), this->img->depth, this->img->nChannels);
	uchar *raw_img = (uchar *)img_out->imageData;

	if (widthp != this->getWidth() || heightp != this->getHeight() || !img_out) {
		return PDI_FAIL;
	}

	for (int i = 0; i < heightp; i++) {
		for (int j = 0; j < widthp; j++) {
			raw_img[i * this->img->widthStep + j * this->img->nChannels + PDI_RED] = redp[i][j];
			raw_img[i * this->img->widthStep + j * this->img->nChannels + PDI_GREEN] = greenp[i][j];
			raw_img[i * this->img->widthStep + j * this->img->nChannels + PDI_BLUE] = bluep[i][j];
		}
	}

	cvSaveImage(namep, img_out);

	return PDI_SUCCESS;
}











