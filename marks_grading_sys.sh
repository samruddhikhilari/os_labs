echo "enter your marks out of 100"
read ${marks}

if (($marks >=95)); then
grade="A+"
elif (($marks >=85));then
grade="A"
elif ((marks >=75));then
grade="B"
elif ((marks >=65));then
grade="C"
else 
grade="D"
fi

echo "you obtained this $grade grade"
