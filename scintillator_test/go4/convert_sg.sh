#!/bin/bash

if [ -z ${GO4SYS+x} ]; then
	echo "GO4SYS is unset. Aborting.";
	exit;
else
	echo "GO4SYS is set to '$GO4SYS'";
fi

# =============================================================================
INPUTLMDDIR=/media/data_nas/25e10/data/clb

if [ ! -d "${INPUTLMDDIR}" ]; then
	echo -e "Directory ${INPUTLMDDIR} does not exist. Aborting."
	exit;
fi

OUTPUTROOTDIR=/media/analysis_nas/exp2510/old_raw/clb

NTHREADS=2

PREFIX=

FILES=${INPUTLMDDIR}/${PREFIX}*.lmd

# Remove textual output if it already exists from previous analysis runs
if [ -d ${OUTPUTROOTDIR}/textoutput/ ]; then
  rm -fv ${OUTPUTROOTDIR}/textoutput/*.txt
else
  mkdir ${OUTPUTROOTDIR}/textoutput
fi

# Remove asf output if it already exists from previous analysis runs
if ! [ -d ${OUTPUTROOTDIR}/autosave/ ]; then
  mkdir ${OUTPUTROOTDIR}/autosave
fi
# =============================================================================

# Count input data files
NFILES=`ls -1q ${FILES} | wc -l`

echo "nFiles=${NFILES}"
echo "nThreads=${NTHREADS}"

  #let IBATCH=1
let iFile=0

for INPUTFILENAME in ${FILES}
do
  NAME=$(basename "$INPUTFILENAME")
  OUTPUTFILENAME=${NAME//lmd/root}
  OUTPUTFILENAME=${OUTPUTROOTDIR}/${OUTPUTFILENAME}

  TEXTERRFILE=${OUTPUTROOTDIR}/textoutput/${NAME}_err.txt  # Default: textoutput/err.txt
  TEXTOUTFILE=${OUTPUTROOTDIR}/textoutput/${NAME}_out.txt  # Default: textoutput/out.txt # No reason to suppres

  # Remove output file if it already exists from previous analysis runs
  if [ -f $OUTPUTFILENAME ]; then
    rm ${OUTPUTFILENAME}
  fi
  # Remove autosave file if it already exists from previous analysis runs
  if [ -f $AUTOSAVEFILE ]; then
    rm ${AUTOSAVEFILE}
  fi

  if [ $iFile -eq $NTHREADS ]; then
    echo -e "\e[1;32;1mWaiting for all threads to finish\e[0m"
    wait
    let iFile=0
  fi
	
  if [ $iFile -lt $NTHREADS ]; then

    ANARUNINFO="========================== ANALYSIS RUN INFO ===================================
    Current date and time                      ${DATETIME}
    Processing input file                      ${INPUTFILENAME}
    into output file                           ${OUTPUTFILENAME}
    Text output file:                          ${TEXTOUTFILE}
    Text error file:                           ${TEXTERRFILE}
    ============================================================================================"

# Starting outoutfile with ANARUNINFO 
cat > ${TEXTOUTFILE} << EOF
${ANARUNINFO}
EOF

    echo -e "\e[1m\e[34m${ANARUNINFO}\e[0m"

    echo -e "\e[1m\e[32m"`date` "Analysis started.\e[0m"

    go4analysis -file ${INPUTFILENAME} -store ${OUTPUTFILENAME} >> ${TEXTOUTFILE} 2> ${TEXTERRFILE} &

    let iFile++
  fi
done

echo -e "\e[1m\e[32m"`date` "Analysis finished.\e[0m"
