#include "../hdr/sc_matrixconsumer.h"
#include <cstdio>

MatrixConsumer::MatrixConsumer(sc_module_name name) : sc_module(name) {
	this->value_1 = this->value_2 = this->value_3 = 0;
	this->lines = 0;
	this->columns = 0;
	this->mat_1 = this->mat_2 = this->mat_3 = NULL;

	SC_HAS_PROCESS(MatrixConsumer);
	SC_THREAD(run);
}

void MatrixConsumer::run() {
	bool first = true, second = true;
	int count = 0, size = 0;
	int lines_l = 0, columns_l = 0;
	int code;

	this->Y = new PdiMatrix[1];
	this->Cb = new PdiMatrix[1];
	this->Cr = new PdiMatrix[1];
	this->aux = new PdiMatrix[1];

	while (1) {
		this->value_1 = fifoInPort_1.read();
		this->value_2 = fifoInPort_2.read();
		this->value_3 = fifoInPort_3.read();

		if (first) {
			first = false;
			this->columns = this->value_1;
		} else if (second) {
			second = false;
			this->lines = this->value_1;
			size = (int)(this->lines * this->columns);

			this->mat_1 = new float*[(int)this->lines];
			this->mat_2 = new float*[(int)this->lines];
			this->mat_3 = new float*[(int)this->lines];

			for (int i = 0; i < this->lines; i++) {
				this->mat_1[i] = new float[(int)this->columns];
				this->mat_2[i] = new float[(int)this->columns];
				this->mat_3[i] = new float[(int)this->columns];
			}
		} else {
			count++;

			this->mat_1[lines_l][columns_l] = this->value_1;
			this->mat_2[lines_l][columns_l] = this->value_2;
			this->mat_3[lines_l][columns_l] = this->value_3;
			columns_l++;

			if (columns_l == this->columns) {
				columns_l = 0;
				lines_l++;
			}

			if (count == size) {
				Y->setMatrix(this->mat_1, this->columns, this->lines, &code);
				Y->sub(this->mat_2, this->columns, this->lines, &code);
				Y->multConst(this->columns, this->lines, 0.299, &code);
				Y->add(this->mat_2, this->columns, this->lines, &code);
				aux->setMatrix(this->mat_3, this->columns, this->lines, &code);
				aux->sub(this->mat_2, this->columns, this->lines, &code);
				aux->multConst(this->columns, this->lines, 0.114, &code);
				Y->add(aux->getMatrix(), this->columns, this->lines, &code);

				Cb->setMatrix(this->mat_3, this->columns, this->lines, &code);
				Cb->sub(Y->getMatrix(), this->columns, this->lines, &code);
				Cb->multConst(this->columns, this->lines, 0.564, &code);

				Cr->setMatrix(this->mat_1, this->columns, this->lines, &code);
				Cr->sub(Y->getMatrix(), this->columns, this->lines, &code);
				Cr->multConst(this->columns, this->lines, 0.713, &code);

				first = true;
				second = true;

				this->lines = 0;
				this->columns = 0;
				size = 0;
				lines_l = 0;
				columns_l = 0;

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
		}

		wait(rand() % 10, SC_NS);
	}
}

void MatrixConsumer::printMat() {
	for (int i = 0; i < this->lines; i++) {
		for (int j = 0; j < this->columns; j++)
			printf("%.2f ", this->mat_1[i][j]);
		printf("\n");
	}
	printf("\n");

	for (int i = 0; i < this->lines; i++) {
		for (int j = 0; j < this->columns; j++)
			printf("%.2f ", this->mat_2[i][j]);
		printf("\n");
	}
	printf("\n");

	for (int i = 0; i < this->lines; i++) {
		for (int j = 0; j < this->columns; j++)
			printf("%.2f ", this->mat_3[i][j]);
		printf("\n");
	}
	printf("\n");
}