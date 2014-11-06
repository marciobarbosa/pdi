/*
Developed by Marcio Brito Barbosa;
Email: mbb2@cin.ufpe.br
Version: 1.0
**/

#include <iostream>
#include <cstdlib>
#include "../hdr/pdi_images.h"
#include "../hdr/pdi_matrix.h"

using namespace std;

int main(int argc, char *argv[])
{
	int code;
	PdiImage img(&code);
	float **raw_img_red, **raw_img_green, **raw_img_blue;
	PdiMatrix Y(&code), Cb(&code), Cr(&code), aux(&code);

	if (argc != 3) {
		printf("usage: ./pdi image_path output_name\n");
		return EXIT_FAILURE;
	}

	img.setImage(argv[1], &code);

	if (!code) {
		printf("Could not open the image!\n");
		return EXIT_FAILURE;
	}

	raw_img_red = new float*[img.getHeight()];
	raw_img_green = new float*[img.getHeight()];
	raw_img_blue = new float*[img.getHeight()];

	for (int i = 0; i < img.getHeight(); i++) {
		raw_img_red[i] = new float[img.getWidth()];
		raw_img_green[i] = new float[img.getWidth()];
		raw_img_blue[i] = new float[img.getWidth()];
	}

	code = img.getImageColor(raw_img_red, PDI_RED, img.getWidth(), img.getHeight());
	code &= img.getImageColor(raw_img_green, PDI_GREEN, img.getWidth(), img.getHeight());
	code &= img.getImageColor(raw_img_blue, PDI_BLUE, img.getWidth(), img.getHeight());

	if (!code) {
		printf("Could not get the image!\n");
		return EXIT_FAILURE;
	}

	Y.setMatrix(raw_img_red, img.getWidth(), img.getHeight(), &code);
	Y.sub(raw_img_green, img.getWidth(), img.getHeight(), &code);
	Y.multConst(img.getWidth(), img.getHeight(), 0.299, &code);
	Y.add(raw_img_green, img.getWidth(), img.getHeight(), &code);
	aux.setMatrix(raw_img_blue, img.getWidth(), img.getHeight(), &code);
	aux.sub(raw_img_green, img.getWidth(), img.getHeight(), &code);
	aux.multConst(img.getWidth(), img.getHeight(), 0.114, &code);
	Y.add(aux.getMatrix(), img.getWidth(), img.getHeight(), &code);

	Cb.setMatrix(raw_img_blue, img.getWidth(), img.getHeight(), &code);
	Cb.sub(Y.getMatrix(), img.getWidth(), img.getHeight(), &code);
	Cb.multConst(img.getWidth(), img.getHeight(), 0.564, &code);

	Cr.setMatrix(raw_img_red, img.getWidth(), img.getHeight(), &code);
	Cr.sub(Y.getMatrix(), img.getWidth(), img.getHeight(), &code);
	Cr.multConst(img.getWidth(), img.getHeight(), 0.713, &code);

	if (!img.thresholdImage(argv[2], Y.getMatrix(), Cb.getMatrix(), Cr.getMatrix(), img.getWidth(), img.getHeight()))
		printf("Could not save the image!\n");

	for (int i = 0; i < img.getHeight(); i++) {
    	delete [] raw_img_red[i];
    	delete [] raw_img_green[i];
    	delete [] raw_img_blue[i];
    }

	delete [] raw_img_red;
	delete [] raw_img_green;
	delete [] raw_img_blue;

	Y.cleanUp(img.getWidth(), img.getHeight());
	Cb.cleanUp(img.getWidth(), img.getHeight());
	Cr.cleanUp(img.getWidth(), img.getHeight());
	aux.cleanUp(img.getWidth(), img.getHeight());

	return EXIT_SUCCESS;
}