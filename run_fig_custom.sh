#!/bin/bash
## RENAME FOR YOUR JOB
#PBS -N MACKE_fig_custom

## EDIT FOR YOUR JOB
## For 8 core nodes
#PBS -l nodes=1:ppn=8,feature=8core

## WALLTIME DEFAULTS TO ONE HOUR - ALWAYS SPECIFY FOR LONGER JOBS
## If the job doesn't finish in 10 minutes, cancel it
#PBS -l walltime=01:05:00

## EDIT FOR YOUR JOB
## Put the STDOUT and STDERR from jobs into the below directory
#PBS -o /gscratch/riekesheabrown/dleen/cpp/LIF_MACKE/joblogs
## Put both the stderr and stdout into a single file
#PBS -j oe

#PBS -m a -M dleen@u.washington.edu

## EDIT FOR YOUR JOB
## Sepcify the working directory for this job bundle
#PBS -d /gscratch/riekesheabrown/dleen/cpp/LIF_MACKE/data

##PBS -q bf

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
(echo custom 20 LIF $LOOP_NUMBER_0;
 echo custom 20 LIF $LOOP_NUMBER_1;
 echo custom 20 LIF $LOOP_NUMBER_2;
 echo custom 20 LIF $LOOP_NUMBER_3;
 echo custom 20 LIF $LOOP_NUMBER_4;
 echo custom 20 LIF $LOOP_NUMBER_5;
 echo custom 20 LIF $LOOP_NUMBER_6;
 echo custom 20 LIF $LOOP_NUMBER_7) | parallel --dry-run --colsep ' ' -j $HYAK_SLOTS /gscratch/riekesheabrown/dleen/cpp/LIF_MACKE/spike_macke_figures.out {}
# echo fig1b 0.2 EIF $LOOP_NUMBER_2) | parallel --dry-run --colsep ' ' -j $HYAK_SLOTS /gscratch/riekesheabrown/dleen/cpp/LIF_MACKE/spike_macke_figures.out {}

