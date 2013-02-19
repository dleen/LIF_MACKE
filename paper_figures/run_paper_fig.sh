for((i=2; i<101; i=i+2))
do
	export LOOP_NUMBER=0
	export SUBPLOT=0.1
	export MODEL=EIF
	export FIGNAME=paper2rho
	export NUM_NEURONS=$i
	qsub -v LOOP_NUMBER,MODEL,SUBPLOT,FIGNAME,NUM_NEURONS /gscratch/riekesheabrown/dleen/cpp/LIF_MACKE/paper_figures/paper_fig_2mu.sh
done
