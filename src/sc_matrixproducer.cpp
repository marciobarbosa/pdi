#include "../hdr/sc_matrixproducer.h"

MatrixProducer::MatrixProducer(sc_module_name name) : sc_module(name) {
	this->lines = 0;
	this->columns = 0;
	this->mat_1 = this->mat_2 = this->mat_3 = NULL;

	SC_HAS_PROCESS(MatrixProducer);
  	SC_THREAD(run);
}

void MatrixProducer::configMat(int lines, int columns) {
	this->lines = lines;
	this->columns = columns;
}

void MatrixProducer::setMat(float **mat_1, float **mat_2, float **mat_3) {
	this->mat_1 = new float*[(int)this->lines];
	this->mat_2 = new float*[(int)this->lines];
	this->mat_3 = new float*[(int)this->lines];

	for (int i = 0; i < this->lines; i++) {
		this->mat_1[i] = new float[(int)this->columns];
		this->mat_2[i] = new float[(int)this->columns];
		this->mat_3[i] = new float[(int)this->columns];
	}

	for (int i = 0; i < this->lines; i++) {
		for (int j = 0; j < this->columns; j++) {
			this->mat_1[i][j] = mat_1[i][j];
			this->mat_2[i][j] = mat_2[i][j];
			this->mat_3[i][j] = mat_3[i][j];
		}
	}
}

void MatrixProducer::cleanUp(void) {
	for (int i = 0; i < this->lines; i++) {
		delete [] this->mat_1[i];
		delete [] this->mat_2[i];
		delete [] this->mat_3[i];
	}
	delete [] this->mat_1;
	delete [] this->mat_2;
	delete [] this->mat_3;

	this->mat_1 = NULL;
	this->mat_2 = NULL;
	this->mat_3 = NULL;
}

void MatrixProducer::run(void) {
	bool first = true, second = true;
	int count = 0, size = this->lines * this->columns;
	int lines_l = 0, columns_l = 0;

	while (1) {
		if (first) {
			first = false;
			fifoOutPort_1.write(this->lines);
			fifoOutPort_2.write(this->lines);
			fifoOutPort_3.write(this->lines);
		} else if (second) {
			second = false;
			fifoOutPort_1.write(this->columns);
			fifoOutPort_2.write(this->columns);
			fifoOutPort_3.write(this->columns);
		} else {
			count++;

			fifoOutPort_1.write(this->mat_1[lines_l][columns_l]);
			fifoOutPort_2.write(this->mat_2[lines_l][columns_l]);
			fifoOutPort_3.write(this->mat_3[lines_l][columns_l]);
			columns_l++;

			if (columns_l == this->columns) {
				columns_l = 0;
				lines_l++;
			}

			if (count == size)
				break;
		}

		wait(rand() % 10, SC_NS);
	}

	this->cleanUp();
}