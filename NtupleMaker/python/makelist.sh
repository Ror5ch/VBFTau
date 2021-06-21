END=1671
for ((i=1;i<=END;i++));
do
if (($i == $END));
then	
  echo -n $i
else
  echo -n $i,
fi
done
