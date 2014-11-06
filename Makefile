CC = g++
CFLAGS = -Wall -g
LDFLAGS = `pkg-config --cflags --libs opencv`

all : pdi_images.o pdi_matrix.o pdi_main.o pdi

pdi_images.o : ./src/pdi_images.cpp ./hdr/pdi_images.h
	${CC} ${CFLAGS} -c ./src/pdi_images.cpp

pdi_matrix.o : ./src/pdi_matrix.cpp ./hdr/pdi_matrix.h
	${CC} ${CFLAGS} -c ./src/pdi_matrix.cpp

pdi_main.o : ./src/pdi_main.cpp
	${CC} ${CFLAGS} -c ./src/pdi_main.cpp

pdi : pdi_main.o pdi_images.o
	${CC} ${CFLAGS} pdi_images.o pdi_matrix.o pdi_main.o ${LDFLAGS} -o pdi