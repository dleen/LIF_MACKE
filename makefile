spike.out : main.cpp LIF_spike.cpp LIF_spike.h LIF_constants.h \
	    LIF_gen_spike_matrix.cpp \
	    EIF_gen_spike_matrix.cpp \
	    DG_gen_spike_matrix.cpp \
	    Macke_figures.cpp \
	    paper_figures.cpp
#	gcc -o spike.out main.cpp LIF_spike.cpp LIF_gen_spike_matrix.cpp Macke_figures.cpp -lgsl -lgslcblas -lm -O3 -ffast-math -funroll-loops -fomit-frame-pointer \
	# -msse -march=corei7
#	g++ -o spike.out main.cpp LIF_spike.cpp LIF_gen_spike_matrix.cpp Macke_figures.cpp -lgsl -lgslcblas -lm -Wall -pedantic
#	clang++ -o spike.out main.cpp LIF_spike.cpp LIF_gen_spike_matrix.cpp Macke_figures.cpp -lgsl -lgslcblas -lm -Wall -pedantic
#	/Users/dleen/my_gcc/bin/g++-4.6.2 -o spike.out main.cpp LIF_spike.cpp LIF_gen_spike_matrix.cpp Macke_figures.cpp -Ofast -march=corei7 -msse -ffast-math -lm -lgsl -lgslcblas
#	/Users/dleen/my_gcc/bin/g++-4.6.2 -o spike.out main.cpp LIF_spike.cpp LIF_gen_spike_matrix.cpp EIF_gen_spike_matrix.cpp QIF_gen_spike_matrix.cpp Macke_figures.cpp -Ofast -ffast-math -lm -lgsl -lgslcblas
	/Users/dleen/my_gcc/bin/g++-4.6.2 -o spike.out main.cpp LIF_spike.cpp LIF_spike.h LIF_constants.h \
	LIF_gen_spike_matrix.cpp \
	EIF_gen_spike_matrix.cpp \
	DG_gen_spike_matrix.cpp \
	Macke_figures.cpp \
	paper_figures.cpp \
	-lm -lgsl -lgslcblas
#	/Users/dleen/my_gcc/bin/g++-4.6.2 -o spike_struct.out main.cpp LIF_spike.cpp LIF_spike.h LIF_constants.h
#	/sw/intel/bin/icc -o spike_struct.out main.cpp LIF_spike.cpp LIF_spike.h LIF_constants.h
#	g++ -o spike_struct.out main.cpp LIF_spike.cpp LIF_spike.h LIF_constants.h
# /sw/intel/bin/icpc \
# -I/gscratch/riekesheabrown/local/include/boost_1_48_0 \
# -L/gscratch/riekesheabrown/lib \
# -o paper_figures.out main.cpp LIF_spike.cpp LIF_spike.h LIF_constants.h \
# LIF_gen_spike_matrix.cpp \
# EIF_gen_spike_matrix.cpp \
# DG_gen_spike_matrix.cpp \
# Macke_figures.cpp \
# paper_figures.cpp \
# -lm -lgsl -lgslcblas -fast -Os

clean:
	rm figure*.dat spike.out
