spike.out : main.cpp LIF_spike.cpp LIF_gen_spike_matrix.cpp Macke_figures.cpp LIF_spike.h LIF_constants.h
#	g++ -o spike.out main.cpp LIF_spike.cpp LIF_gen_spike_matrix.cpp Macke_figures.cpp -lgsl -lgslcblas -lm -Wall -pedantic
	clang++ -o spike.out main.cpp LIF_spike.cpp LIF_gen_spike_matrix.cpp Macke_figures.cpp -lgsl -lgslcblas -lm -Wall -pedantic

clean:
	rm figure*.dat spike.out
