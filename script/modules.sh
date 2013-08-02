ALL_MODULES=`net-snmp-config --default-mibs`

i=2

while [ 1 ]
do
   MOD=`echo $ALL_MODULES | cut -d: -f$i`
   if [ -z $MOD ]
   then
      break
   fi
   echo $MOD
   i=$[$i+1]
done

echo "$[$i-2] modules has been found"

exit 0
