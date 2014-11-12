/*
Developed by Marcio Brito Barbosa;
Email: mbb2@cin.ufpe.br
Version: 1.1
**/

#ifndef __MATRIX_PRODUCER_H__
#define __MATRIX_PRODUCER_H__

#include <systemc.h>

class MatrixProducer : public sc_module {
public:
	explicit MatrixProducer(sc_module_name name);
	void configMat(int lines, int columns);
	void setMat(float **mat_1, float **mat_2, float **mat_3);
	void cleanUp(void);
	sc_fifo_out<float> fifoOutPort_1;
	sc_fifo_out<float> fifoOutPort_2;
	sc_fifo_out<float> fifoOutPort_3;
	void run();
private:
	float lines, columns;
	float **mat_1, **mat_2, **mat_3;
};

#endif