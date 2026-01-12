echo "enter a string"
read $str1

$strrev =$(echo $str1 | rev)
if [$str1 -et $strrev]; then
echo "enter data is pallindrome"
else
echo "enter data is not a pallindrome"
fi
