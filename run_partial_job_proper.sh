for((i=0; i<100; i++))
do
	export LOOP_NUMBER=$i
	export SUBPLOT=0.1
	export MODEL=EIF
	export FIGNAME=fig1b
	qsub -v LOOP_NUMBER,MODEL,SUBPLOT,FIGNAME /gscratch/riekesheabrown/dleen/cpp/LIF_MACKE/run_fig_custom.sh
done
