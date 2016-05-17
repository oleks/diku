#!/bin/sh
#
# Copyright (C) 2015 Oleksandr Shturmov
#
# Sandstone Basic License - Version 3 - March 15, 2015.
#
# Permission is hereby granted, free of charge, to any legal person obtaining
# these artefacts, to deal in the artefacts as they please, including, without
# limitation, the rights to use, copy, modify, distribute, sublicense, and/or
# sell these artefacts, and to permit legal persons, to whom the artefacts are
# furnished, to do so as well, subject to the following conditions: 
#
# The creators of these artefacts are properly attributed for their original
# work, e.g. by including the above copyright notice and the below notice of no
# warranty in any copy or derivation of the artefacts.
#
# THE ARTEFACTS ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHENTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE, TITLE OR NON-INFRINGEMENT. IN NO EVENT
# SHALL THE CREATORS OF THE ARTEFACTS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES, OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
# ARISING FROM, OUT OF, OR IN CONNECTION WITH THE ARTEFACTS, THE USE, OR OTHER
# DEALINGS IN THE ARTEFACTS.
#
#
#
# This script allows you to quickly run pdflatex to build your sources. You can
# run the script without arguments, in which case the script assumes that a
# file named root.tex exists and is the root tex file. The script creates (if
# it doesn't already exist) a subdirectory ./output/ and directs all output
# from pdflatex there. The name of the produced file is left at "root", unless
# otherwise specified in this script.
#
# You can try it out:
# ./weave.sh
# ./weave.sh root.tex
# ./weave.sh standalone.tex math.tex

# Optional, the name of the root tex file.
BASENAME="master"

# Optional, the name of the output file.
JOBNAME="$(basename $(dirname $(pwd)))"

if [ -z $BASENAME ]; then BASENAME="${1%.*}"; fi
if [ -z $BASENAME ]; then BASENAME="root"; fi
if [ -z $JOBNAME ]; then JOBNAME=$BASENAME; fi

OUTDIR="./output/"

mkdir -p $OUTDIR

if [ "$BASENAME" = "standalone" ]
then
  COMMAND="\\newcommand\\content[0]{\\input{$2}}\\input{$BASENAME}"
  JOBNAME="$JOBNAME-$(echo ${2%.*} | sed -e 's/\//-/g')"
# Optional, other else-ifs.
else
  COMMAND="\\input{$BASENAME}"
fi

(cd $OUTDIR && makeindex $JOBNAME)
pdflatex -output-directory=$OUTDIR -file-line-error \
  -jobname $JOBNAME \
  $COMMAND

