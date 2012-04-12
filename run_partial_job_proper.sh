for((i=0; i<12; i++))
do
	export LOOP_NUMBER=$i
	export SUBPLOT=20
	qsub -v LOOP_NUMBER,SUBPLOT /gscratch/riekesheabrown/dleen/cpp/LIF_MACKE/run_fig_custom.sh
done
