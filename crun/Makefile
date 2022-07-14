CC = gcc

SRC_DIR = src

LINKER_FLAGS = -lgsl -lgslcblas
OBJ_C_FLAGS = -c -fpic
OBJ_SO_FLAGS = -shared -o

all: libsvm.so libfpt.so

#
# SHARED OBJECTS
#
libsvm.so: svm.o scale.o
	${CC} ${OBJ_SO_FLAGS} libsvm.so svm.o scale.o ${LINKER_FLAGS}

libfpt.so: fpt.o scale.o
	${CC} ${OBJ_SO_FLAGS} libfpt.so fpt.o scale.o ${LINKER_FLAGS}

#
# COMPONENT OBJECTS
#
svm.o: ${SRC_DIR}/svm.c ${SRC_DIR}/svm.h
	${CC} ${OBJ_C_FLAGS} ${SRC_DIR}/svm.c ${LINKER_FLAGS}

fpt.o: ${SRC_DIR}/fpt.c ${SRC_DIR}/fpt.h
	${CC} ${OBJ_C_FLAGS} ${SRC_DIR}/fpt.c ${LINKER_FLAGS}

scale.o: ${SRC_DIR}/scale.c ${SRC_DIR}/scale.h
	${CC} ${OBJ_C_FLAGS} ${SRC_DIR}/scale.c ${LINKER_FLAGS}

#
# GENERAL CMDS
#
clean:
	rm *.o

# vim: set noexpandtab tabstop=4 shiftwidth=4 softtabstop=-1:
