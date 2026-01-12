echo "enter count of fibonacci series"
read $count

$a=0
$b=1

for(( i=0;i<count;i++)); do
echo -n "$a"
$c=$(a+b)
$a=$b 
$b = $c 
done