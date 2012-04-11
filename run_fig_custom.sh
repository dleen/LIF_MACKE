#!/bin/bash
## RENAME FOR YOUR JOB
#PBS -N MACKE_fig_Eric

## EDIT FOR YOUR JOB
## For 8 core nodes
#PBS -l nodes=1:ppn=8,feature=8core

## WALLTIME DEFAULTS TO ONE HOUR - ALWAYS SPECIFY FOR LONGER JOBS
## If the job doesn't finish in 10 minutes, cancel it
#PBS -l walltime=00:33:00

## EDIT FOR YOUR JOB
## Put the STDOUT and STDERR from jobs into the below directory
#PBS -o /gscratch/riekesheabrown/dleen/cpp/LIF_MACKE/joblogs
## Put both the stderr and stdout into a single file
#PBS -j oe

## EDIT FOR YOUR JOB
## Sepcify the working directory for this job bundle
#PBS -d /gscratch/riekesheabrown/dleen/cpp/LIF_MACKE/data

HYAK_SLOTS=`wc -l < $PBS_NODEFILE`

## jobargs is a file with the arguments you want to pass to your application
##  
cat jobargs_fig2a_par_8 | parallel -j $HYAK_SLOTS /gscratch/riekesheabrown/dleen/cpp/LIF_MACKE/spike_macke_figures.out {}
exit 0
