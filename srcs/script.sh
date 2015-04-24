for file in *.c ; do
leftname=`basename $file c`
mv $file ${leftname}cpp
done