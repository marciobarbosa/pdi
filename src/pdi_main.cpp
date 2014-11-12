/*
Developed by Marcio Brito Barbosa;
Email: mbb2@cin.ufpe.br
Version: 1.1
**/

#include <cstdio>
#include <cstdlib>
#include "../hdr/pdi_images.h"
#include "../hdr/pdi_matrix.h"
#include "../hdr/sc_matrixproducer.h"
#include "../hdr/sc_matrixconsumer.h"

int sc_main(int argc, char *argv[])
{
	int code;
	PdiImage img(&code);
	float **raw_img_red, **raw_img_green, **raw_img_blue;
	sc_fifo<float> myFifo_1(1), myFifo_2(1), myFifo_3(1);
	MatrixProducer prod("Producer");
	MatrixConsumer cons("Consumer");

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

	prod.configMat(img.getHeight(), img.getWidth());
	prod.setMat(raw_img_red, raw_img_green, raw_img_blue);

	prod.fifoOutPort_1(myFifo_1);
  	prod.fifoOutPort_2(myFifo_2);
  	prod.fifoOutPort_3(myFifo_3);

  	cons.fifoInPort_1(myFifo_1);
  	cons.fifoInPort_2(myFifo_2);
  	cons.fifoInPort_3(myFifo_3);

  	sc_start();

  	if (!img.thresholdImage(argv[2], cons.Y->getMatrix(), cons.Cb->getMatrix(), cons.Cr->getMatrix(), img.getWidth(), img.getHeight()))
		printf("Could not save the image!\n");
	else
		printf("Image received!\n");

	for (int i = 0; i < img.getHeight(); i++) {
    	delete [] raw_img_red[i];
    	delete [] raw_img_green[i];
    	delete [] raw_img_blue[i];
    }

	delete [] raw_img_red;
	delete [] raw_img_green;
	delete [] raw_img_blue;

	cons.Y->cleanUp(img.getWidth(), img.getHeight());
	cons.Cb->cleanUp(img.getWidth(), img.getHeight());
	cons.Cr->cleanUp(img.getWidth(), img.getHeight());
	cons.aux->cleanUp(img.getWidth(), img.getHeight());

	delete [] cons.Y;
	delete [] cons.Cb;
	delete [] cons.Cr;
	delete [] cons.aux;

	return EXIT_SUCCESS;
}