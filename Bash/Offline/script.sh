# man unzip
chmod +x SubmissionsAll.zip
unzip -o SubmissionsAll.zip
cp -r SubmissionsAll.zip ../SubmissionsAll.zip  # Replace with mv at the end of assignment

var=`ls`
clear
echo "" > filelist.txt
for variable in $var
do
    echo "$variable" >> filelist.txt
done
# grep -wE "[0-9]*" filelist.txt
# grep -w -E "0-9" CSE_322.csv
# grep -P "\d{7}" CSE_322.csv > output.csv

# cut -d"," -f1 CSE_322.csv | cut -d"\"" -f2
# cut -d "\"" -f2 CSE_322.csv

# cut -d "_" -f5 -s filelist.txt | cut -d "." -f1  ## Getting list of roll numbers from the extracted files

filelist=`cut -d "_" -f5 -s filelist.txt | cut -d "." -f1`
Raster=`cut -c 3-9 CSE_322.csv`

for item in $Raster
do
flag=0
    # echo $item
    for file in $filelist 
    do
        if [ $item = $file ] 
        then
            flag=1
            echo "$file 10" >> Marks.txt
            break
        fi
    done

    if [ $flag = 0 ] 
    then
        echo $item >> Absents.txt
        echo "$item 0" >> Marks.txt
    fi
done

if [ -d Output/ ]
then 
rm -r Output/ 
fi

mkdir Output
cd Output

if [ -d Extra/ ]
then
 rm -r Extra/ 
fi

mkdir Extra
cd ..

# for zip in `ls`
# do
#     echo $zip
    
# done

find . -iname "*.zip" | while read zip
do
    # ... loop body
    echo $f
    # unzip -o $zip -d temp/
    # rm $zip
done