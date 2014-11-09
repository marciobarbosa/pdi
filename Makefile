SYSTEMC = $(SYSTEMC_HOME)
OS = linux64
CC = g++
LIBS = $(SYSTEMC)/lib-$(OS)/
INCLUDE = $(SYSTEMC)/include
CFLAGS = -I$(INCLUDE) -L$(LIBS) -lsystemc
LDFLAGS = `pkg-config --cflags --libs opencv`
SOURCES = ./src/pdi_images.cpp ./src/pdi_matrix.cpp ./src/sc_matrixproducer.cpp ./src/sc_matrixconsumer.cpp ./src/pdi_main.cpp

all : pdi_images.o pdi_matrix.o sc_matrixproducer.o sc_matrixconsumer.o pdi_main.o pdi.x

pdi_images.o : ./src/pdi_images.cpp ./hdr/pdi_images.h
	${CC} ${CFLAGS} -c ./src/pdi_images.cpp

pdi_matrix.o : ./src/pdi_matrix.cpp ./hdr/pdi_matrix.h
	${CC} ${CFLAGS} -c ./src/pdi_matrix.cpp

sc_matrixproducer.o : ./src/sc_matrixproducer.cpp ./hdr/sc_matrixproducer.h
	${CC} ${CFLAGS} -c ./src/sc_matrixproducer.cpp

sc_matrixconsumer.o : ./src/sc_matrixconsumer.cpp ./hdr/sc_matrixconsumer.h
	${CC} ${CFLAGS} -c ./src/sc_matrixconsumer.cpp

pdi_main.o : ./src/pdi_main.cpp
	${CC} ${CFLAGS} -c ./src/pdi_main.cpp

pdi.x : pdi_main.o pdi_images.o
	${CC} ${CFLAGS} pdi_images.o pdi_matrix.o sc_matrixproducer.o sc_matrixconsumer.o pdi_main.o ${LDFLAGS} -o pdi.x

clean :
	@rm -f *~ *.o *.x