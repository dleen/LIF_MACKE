
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
 echo custom 20 LIF $LOOP_NUMBER_7) | parallel --dry-run --colsep ' ' /gscratch/riekesheabrown/dleen/cpp/LIF_MACKE/spike_macke_figures.out {}

