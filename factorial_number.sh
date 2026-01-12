echo "enter a number"
read $num
$fact=1
for ((i=1;i<=$num;i++)); do 
    $fact =$fact * i
done

if (($fact !=1)); then
echo "factorial of enter $num is $fact"
else
echo "error occured "
fi