for((i=2; i<100; i++))
do
	LOOP_NUMBER=$i
	qsub -v LOOP_NUMBER /gscratch/riekesheabrown/dleen/cpp/LIF_MACKE/run_fig1a.sh
	qsub -v LOOP_NUMBER /gscratch/riekesheabrown/dleen/cpp/LIF_MACKE/run_fig1b.sh
	qsub -v LOOP_NUMBER /gscratch/riekesheabrown/dleen/cpp/LIF_MACKE/run_fig2a.sh
	qsub -v LOOP_NUMBER /gscratch/riekesheabrown/dleen/cpp/LIF_MACKE/run_fig_rem.sh
done
