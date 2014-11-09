#include "../hdr/sc_matrixproducer.h"
#include "../hdr/sc_matrixconsumer.h"
#include <cstdlib>

int sc_main(int argc, char *argv[])
{
	sc_fifo<float> myFifo_1(1), myFifo_2(1), myFifo_3(1);
	MatrixProducer prod("Producer");
	MatrixConsumer cons("Consumer");
	float **mat_1, **mat_2, **mat_3;

	mat_1 = new float*[5];
	mat_2 = new float*[5];
	mat_3 = new float*[5];

	for (int i = 0; i < 5; i++) {
		mat_1[i] = new float[5];
		mat_2[i] = new float[5];
		mat_3[i] = new float[5];
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			mat_1[i][j] = 1;
			mat_2[i][j] = 2;
			mat_3[i][j] = 3;
		}
	}

	prod.configMat(5, 5);
	prod.setMat(mat_1, mat_2, mat_3);

  	prod.fifoOutPort_1(myFifo_1);
  	prod.fifoOutPort_2(myFifo_2);
  	prod.fifoOutPort_3(myFifo_3);

  	cons.fifoInPort_1(myFifo_1);
  	cons.fifoInPort_2(myFifo_2);
  	cons.fifoInPort_3(myFifo_3);

  	sc_start();

  	for (int i = 0; i < 5; i++) {
  		delete [] mat_1[i];
  		delete [] mat_2[i];
  		delete [] mat_3[i];
  	}
  	delete [] mat_1;
  	delete [] mat_2;
  	delete [] mat_3;

	return EXIT_SUCCESS;
}