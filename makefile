spike.out : main.cpp LIF_spike.cpp LIF_gen_spike_matrix.cpp Macke_figures.cpp LIF_spike.h LIF_constants.h
#	gcc -o spike.out main.cpp LIF_spike.cpp LIF_gen_spike_matrix.cpp Macke_figures.cpp -lgsl -lgslcblas -lm -O3 -ffast-math -funroll-loops -fomit-frame-pointer \
	-msse -march=corei7
#	g++ -o spike.out main.cpp LIF_spike.cpp LIF_gen_spike_matrix.cpp Macke_figures.cpp -lgsl -lgslcblas -lm -Wall -pedantic 
#	clang++ -o spike.out main.cpp LIF_spike.cpp LIF_gen_spike_matrix.cpp Macke_figures.cpp -lgsl -lgslcblas -lm -Wall -pedantic
	/Users/dleen/my_gcc/bin/g++-4.6.2 -o spike.out main.cpp LIF_spike.cpp LIF_gen_spike_matrix.cpp Macke_figures.cpp -Ofast -march=corei7 -msse -ffast-math -lm -lgsl -lgslcblas

clean:
	rm figure*.dat spike.out
