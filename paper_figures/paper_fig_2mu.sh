#!/bin/bash
## RENAME FOR YOUR JOB
#PBS -N paper_figures_2rho

## EDIT FOR YOUR JOB
## For 8 core nodes
#PBS -l nodes=1:ppn=8,feature=8core

## WALLTIME DEFAULTS TO ONE HOUR - ALWAYS SPECIFY FOR LONGER JOBS
## If the job doesn't finish in 10 minutes, cancel it
#PBS -l walltime=00:20:00

## EDIT FOR YOUR JOB
## Put the STDOUT and STDERR from jobs into the below directory
#PBS -o /gscratch/riekesheabrown/dleen/cpp/LIF_MACKE/joblogs
## Put both the stderr and stdout into a single file
#PBS -j oe

#PBS -m a -M dleen@u.washington.edu

## EDIT FOR YOUR JOB
## Sepcify the working directory for this job bundle
#PBS -d /gscratch/riekesheabrown/dleen/cpp/LIF_MACKE/data/paper_figures/fig2rho

#PBS -q bf

HYAK_SLOTS=`wc -l < $PBS_NODEFILE`

LOOP_NUMBER_0=`expr 8 \\* $LOOP_NUMBER + 0`
LOOP_NUMBER_1=`expr 8 \\* $LOOP_NUMBER + 1`
LOOP_NUMBER_2=`expr 8 \\* $LOOP_NUMBER + 2`
LOOP_NUMBER_3=`expr 8 \\* $LOOP_NUMBER + 3`
LOOP_NUMBER_4=`expr 8 \\* $LOOP_NUMBER + 4`
LOOP_NUMBER_5=`expr 8 \\* $LOOP_NUMBER + 5`
LOOP_NUMBER_6=`expr 8 \\* $LOOP_NUMBER + 6`
LOOP_NUMBER_7=`expr 8 \\* $LOOP_NUMBER + 7`

## jobargs is a file with the arguments you want to pass to your application
##  
(echo $FIGNAME $SUBPLOT $MODEL $LOOP_NUMBER_0 $NUM_NEURONS;
 echo $FIGNAME $SUBPLOT $MODEL $LOOP_NUMBER_1 $NUM_NEURONS;
 echo $FIGNAME $SUBPLOT $MODEL $LOOP_NUMBER_2 $NUM_NEURONS;
 echo $FIGNAME $SUBPLOT $MODEL $LOOP_NUMBER_3 $NUM_NEURONS;
 echo $FIGNAME $SUBPLOT $MODEL $LOOP_NUMBER_4 $NUM_NEURONS;
 echo $FIGNAME $SUBPLOT $MODEL $LOOP_NUMBER_5 $NUM_NEURONS;
 echo $FIGNAME $SUBPLOT $MODEL $LOOP_NUMBER_6 $NUM_NEURONS;
 echo $FIGNAME $SUBPLOT $MODEL $LOOP_NUMBER_7 $NUM_NEURONS) | parallel --colsep ' ' -j $HYAK_SLOTS /gscratch/riekesheabrown/dleen/cpp/LIF_MACKE/paper_figures.out {}
