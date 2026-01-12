echo "enter a numbers"
read $num

$flag=0
for((i=0;i<=$num/2;i=i+1)); do
if (($num%i == 0)); then
$flag=1
fi
done

if ((flag==0)); then
echo "enter number is a pallindrome"
else 
echo "enter number is not a pallindrome"

fi
