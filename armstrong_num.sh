echo "enter a number"
read $num
$temp=$num
$sum=0
while $((num >=0)); do 
    $rem = $((num%10))
    $sum = $(sum + rem * rem * rem)
    $num =$((num/10))
done

if [$temp == $sum]; then
echo "enter $num is armstrong"
else
echo "enter $num is not a armstrong"
fi