for((i=0; i<100; i++))
do
	#LOOP_NUMBER=$i
	export LOOP_NUMBER=$i
	qsub -v LOOP_NUMBER /gscratch/riekesheabrown/dleen/cpp/LIF_MACKE/run_fig1b_partial.sh
	#/gscratch/riekesheabrown/dleen/cpp/LIF_MACKE/run_fig1b_partial.sh
done
