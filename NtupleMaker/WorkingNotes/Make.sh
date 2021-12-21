#!/bin/sh
if [ ! $1 ] ; then 
    echo "Please specify the code you want to compile by typing :"
    echo "./Make <Your-Code.C>"
    exit 1
fi

filename=`echo $1 | awk -F"." '{print $1}'`
exefilename=${filename}.exe
rm -f $exefilename
g++ $1 -o $exefilename `root-config --cflags --glibs`
echo ""
echo " :: Compile $1 ::"
if [ -e $exefilename ]; then 
    echo "  Created exe file ... "
    echo `ls -lrt $exefilename`
    echo "                                                                   DONE!"
else
    echo "  >> Did not create the exe file!"
fi
echo ""
	
