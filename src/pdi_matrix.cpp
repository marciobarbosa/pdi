/*
Developed by Marcio Brito Barbosa;
Email: mbb2@cin.ufpe.br
Version: 1.0
**/

#include "../hdr/pdi_matrix.h"

PdiMatrix::PdiMatrix(void) {
	this->matrix = NULL;
}

PdiMatrix::PdiMatrix(int *codep) {
	this->matrix = NULL;
	*codep = PDI_MATRIX_FAIL;
}

PdiMatrix::PdiMatrix(float **matrixp, int widthp, int heightp, int *codep) {
	this->matrix = new float*[heightp];

	for (int i = 0; i < heightp; i++) {
		this->matrix[i] = new float[widthp];
	}

	if (matrixp == NULL) {
		this->cleanUp(widthp, heightp);
		*codep = PDI_MATRIX_FAIL;
	} else {
		for (int i = 0; i < heightp; i++) {
			for (int j = 0; j < widthp; j++)
				this->matrix[i][j] = matrixp[i][j];
		}
		*codep = PDI_MATRIX_SUCCESS;
	}
}

void PdiMatrix::init(int widthp, int heightp) {
	if (this->matrix != NULL)
		this->cleanUp(widthp, heightp);

	this->matrix = new float*[heightp];

	for (int i = 0; i < heightp; i++)
		this->matrix[i] = new float[widthp];

	for (int i = 0; i < heightp; i++) {
		for (int j = 0; j < widthp; j++)
			this->matrix[i][j] = 0;
	}
}

float** PdiMatrix::getMatrix(void) {
	return this->matrix;
}

void PdiMatrix::setMatrix(float **matrixp, int widthp, int heightp, int *codep) {
	if (this->matrix != NULL)
		this->cleanUp(widthp, heightp);

	this->matrix = new float*[heightp];

	for (int i = 0; i < heightp; i++) {
		this->matrix[i] = new float[widthp];
	}

	if (matrixp == NULL) {
		this->cleanUp(widthp, heightp);
		*codep = PDI_MATRIX_FAIL;
	} else {
		for (int i = 0; i < heightp; i++) {
			for (int j = 0; j < widthp; j++)
				this->matrix[i][j] = matrixp[i][j];
		}
		*codep = PDI_MATRIX_SUCCESS;
	}
}

void PdiMatrix::add(float **matrixp, int widthp, int heightp, int *codep) {
	if (matrixp != NULL && this->matrix != NULL) {
		for (int i = 0; i < heightp; i++) {
			for (int j = 0; j < widthp; j++)
				this->matrix[i][j] += matrixp[i][j];
		}
		*codep = PDI_MATRIX_SUCCESS;
	} else {
		*codep = PDI_MATRIX_FAIL;
	}
}

void PdiMatrix::sub(float **matrixp, int widthp, int heightp, int *codep) {
	if (matrixp != NULL && this->matrix != NULL) {
		for (int i = 0; i < heightp; i++) {
			for (int j = 0; j < widthp; j++)
				this->matrix[i][j] -= matrixp[i][j];
		}
		*codep = PDI_MATRIX_SUCCESS;
	} else {
		*codep = PDI_MATRIX_FAIL;
	}
}

void PdiMatrix::multConst(int widthp, int heightp, float value, int *codep) {
	if (this->matrix != NULL) {
		for (int i = 0; i < heightp; i++) {
			for (int j = 0; j < widthp; j++)
				this->matrix[i][j] *= value;
		}
		*codep = PDI_MATRIX_SUCCESS;
	} else {
		*codep = PDI_MATRIX_FAIL;
	}
}

void PdiMatrix::cleanUp(int widthp, int heightp) {
	for (int i = 0; i < heightp; i++)
		delete [] this->matrix[i];
	delete [] this->matrix;
}

void PdiMatrix::printMatrix(int widthp, int heightp) {
	for (int i = 0; i < heightp; i++) {
		for (int j = 0; j < widthp; j++)
			printf("%.2f ", this->matrix[i][j]);
		printf("\n");
	}
}