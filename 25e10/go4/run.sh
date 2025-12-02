#!/bin/bash

if [ -z ${GO4SYS+x} ]; then
	echo "GO4SYS is unset. Aborting.";
	exit;
else
	echo "GO4SYS is set to '$GO4SYS'";
fi

# =============================================================================

# Please specify the path to a directory which contains _ONLY_ the files you want to analyse
# You should not put the trailing slash sign (but actually if you will, it should not affect the result...)
# You need to have write access to this directory
INPUTLMDDIR=/home/LynxOS/mbsusr/mbsdaq/mbsrun/exp202003/data/clb

if [ ! -d "${INPUTLMDDIR}" ]; then
	echo -e "Directory ${INPUTLMDDIR} does not exist. Aborting."
	exit;
fi

# Please specify the path to the output directory where the resulting root files will be written
OUTPUTROOTDIR=/media/analysis_nas/exp202003/clb/root

# TODO check that ${OUTPUTROOTDIR} exists ???

# Please specify the input XML configuration file
SETUPFILE=/media/analysis_nas/exp202003/raw2/conversion/setupEXP2003.xml

# TODO check that ${SETUPFILE} exists

# Please specify how many threads do you want to occupy
NTHREADS=1

# Please specify the prefix for the generated lml files
# In principle, there are no constraints, but you may want to keep it the same as the directory name

PREFIX=crun_0

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

#NAMES=${FILES}-${INPUTLMDDIR}

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
  AUTOSAVEFILE=${OUTPUTROOTDIR}/autosave/${NAME}_asf.root

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

    go4analysis -file ${INPUTFILENAME} -store ${OUTPUTFILENAME} >> ${TEXTOUTFILE} 2> ${TEXTERRFILE} 

    let iFile++
  fi
done

echo -e "\e[1m\e[32m"`date` "Analysis finished.\e[0m"
