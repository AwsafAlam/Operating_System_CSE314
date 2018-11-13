cd Australia/Allrounder/

find . -iname "*.txt" | while read player
do
    echo "$player"
    cat "$player"
done

cd ..
cd ..