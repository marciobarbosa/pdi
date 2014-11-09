#ifndef __SC_MATRIX_CONSUMER_H__
#define __SC_MATRIX_CONSUMER_H__

#include <systemc.h>
#include "../hdr/pdi_matrix.h"

class MatrixConsumer : public sc_module {
public:
	explicit MatrixConsumer(sc_module_name name);
	void printMat();
	float value_1, value_2, value_3;
	sc_fifo_in<float> fifoInPort_1;
	sc_fifo_in<float> fifoInPort_2;
	sc_fifo_in<float> fifoInPort_3;
	void run();
	PdiMatrix *Y, *Cb, *Cr, *aux;
private:
	float lines, columns;
	float **mat_1, **mat_2, **mat_3;
};

#endif