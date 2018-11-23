
find . -iname "*.cpp" > cppfiles.txt

find . -iname "*.cpp" | cut -c 3- | while read cppfile
do
    echo "$cppfile ->"
    g++ "$cppfile" -o "mycpp"
    # dir=`cd "$cppfile" | cut -s -d "/" -f3`    
    # echo "$dir"
done
