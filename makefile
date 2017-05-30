# define the C compiler to use
CC = mpicc
# define any compile-time flags
CFLAGS = 
# define any directories containing header files other than /usr/include
INCLUDES = -I/home1/software/compiler/intel11.0/083/mkl/include
# define library paths in addition to /usr/lib
LFLAGS = -L/home1/software/compiler/intel11.0/083/mkl/lib/em64t/
# define any libraries to link into executable:
LIBS = -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread -lm
# define the C source files
SRCS = hw4.c
OBJS = hw4.o
# define the executable file 
MAIN = hw4
$(MAIN): $(OBJS) 
		$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)
clean:
		$(RM) *.o *~ $(MAIN)
