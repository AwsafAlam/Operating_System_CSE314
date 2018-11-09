# man unzip
chmod +x SubmissionsAll.zip
unzip -q -o SubmissionsAll.zip
mv -f SubmissionsAll.zip ../SubmissionsAll.zip  # Replace with mv at the end of assignment

if [ -d Output/ ]
then 
rm -fr Output/ 
fi

mkdir Output
cd Output

if [ -d Extra/ ]
then
rm -fr Extra/ 
fi

mkdir Extra
cd ..


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


find . -iname "*.zip" | while read zip
do
    # echo $zip
    s=`echo "$zip" | cut -d "_" -f5 | cut -d "." -f1`
    unzip -q -o "$zip" -d temp/
    cd temp
    name=`ls`
    count=`ls -1 | wc -l`
    
    if [ $((count)) -gt 1 ]; then
        echo "Count: $count , $zip" ## Student submitted more than 2 files
        ls
        # cd ..
        # mkdir "$s"
        # cd temp
        mkdir "../Output/Extra/$s" 
        mv * "../Output/Extra/$s" 
    else

        if [ "$s" = "$name" ]
        then
            cp -fr "$name" ../Output
            rm -fr "$name"
        else
            cp -fr "$name" ../Output/Extra/
            rm -fr "$name"
        fi
    fi
    cd ..
    rm "$zip"
done

# unzip -o "Aaiyeesha Mostak_2998885_assignsubmission_file_1405011.zip" -d temp/
# cd temp
# name=`ls`

mv -f ../SubmissionsAll.zip SubmissionsAll.zip  # bringing back test input file :p 

# rm "*.rar"