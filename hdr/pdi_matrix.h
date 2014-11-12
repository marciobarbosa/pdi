/*
Developed by Marcio Brito Barbosa;
Email: mbb2@cin.ufpe.br
Version: 1.1
**/

#ifndef PDI_MATRIX_H
#define PDI_MATRIX_H

#include <cstdio>
#include <memory.h>

#define PDI_MATRIX_SUCCESS	1
#define PDI_MATRIX_FAIL		0

class PdiMatrix {
public:
	PdiMatrix(void);
	PdiMatrix(int *codep);
	PdiMatrix(float **matrixp, int widthp, int heightp, int *codep);
	void init(int widthp, int heightp);
	float** getMatrix(void);
	void setMatrix(float **matrixp, int widthp, int heightp, int *codep);
	void add(float **matrixp, int widthp, int heightp, int *codep);
	void sub(float **matrixp, int widthp, int heightp, int *codep);
	void multConst(int widthp, int heightp, float value, int *codep);
	void cleanUp(int widthp, int heightp);
	void printMatrix(int widthp, int heightp);
private:
	float **matrix;
};

#endif