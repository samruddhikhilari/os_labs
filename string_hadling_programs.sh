echo "enter first string"
read ${str1}
echo "enter second string"
read ${str2}

if["$str1" == "$str2"];then
    echo "both strings are equal"
else
    echo "both strings are not equal"
fi

$len1 =${#str1}
$len2 =${#str2}

echo "length of $str1 is $len1"
echo "length of $str2 is $len2"

concat=$str1$str2
echo "concat string is $concat"

revstr =$(echo $str1 | rev )
echo "reverse string is $revstr"