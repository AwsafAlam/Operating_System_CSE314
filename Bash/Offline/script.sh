# man unzip
chmod +x submissionsAll.zip
unzip -q -o submissionsAll.zip
mv -f submissionsAll.zip ../submissionsAll.zip  # Replace with mv at the end of assignment

## If present before
rm Absents.txt
rm Marks.txt

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


find . -iname "*.zip" > filelist.txt
# find . -iname "*.rar" >> filelist.txt

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
    for file in $filelist 
    do
        if [ $item = $file ] 
        then
            flag=1
            # echo "$file 10" >> Marks.txt
            break
        fi
    done

    if [ $flag = 0 ] 
    then
        echo $item >> Absents.txt
        echo "$item 0" >> Marks.txt
    fi
done

function checkAbsenteeList()
{
    echo "checking .."
    if [ "$csvRoll" = "$name" ]
    then
        cp -fr "$name" ../Output
        rm -fr "$name"
        echo "$csvRoll 10" >> ../Marks.txt
    else
        # regex="[0-9][0-9]05[0-1][0-9][0-9]"
        echo "$name -> $roll"
        if [[ "$name" =~ $regex ]]
        then
            # echo "Dirname matches partially";

            mv "$name/" "$csvRoll/"
            cp -fr "$csvRoll" ../Output
            rm -fr "$csvRoll"
            echo "$csvRoll 5" >> ../Marks.txt
        else
            # echo "doesn't match! $name";
            # dirname doesnt match roll (but correst roll in zip)
            mv "$name/" "$csvRoll/"
            cp -fr "$csvRoll" ../Output/Extra/
            rm -fr "$csvRoll"
            echo "$csvRoll 0" >> ../Marks.txt
            
        fi

    fi
}

function populateMarksSheet()
{
    if [ "$roll" = "$name" ]
    then
        cp -fr "$name" ../Output
        rm -fr "$name"
        echo "$roll 10" >> ../Marks.txt
    else
        # regex="[0-9][0-9]05[0-1][0-9][0-9]"
        echo "$name -> $roll"
        if [[ "$name" =~ $regex ]]
        then
            # echo "Dirname matches partially";

            mv "$name/" "$roll/"
            cp -fr "$roll" ../Output
            rm -fr "$roll"
            echo "$roll 5" >> ../Marks.txt
        else
            # echo "doesn't match! $name";
            # dirname doesnt match roll (but correst roll in zip)
            mv "$name/" "$roll/"
            cp -fr "$roll" ../Output/Extra/
            rm -fr "$roll"
            echo "$roll 0" >> ../Marks.txt
            
        fi

    fi

}

find . -iname "*.zip" | while read zip
do

    roll=`echo "$zip" | cut -d "_" -f5 | cut -d "." -f1` # Getting roll from zip file name
    stdName=`echo "$zip" | cut -d "_" -f1` 
    unzip -q -o "$zip" -d temp/
    cd temp
    name=`ls`
    count=`ls -1 | wc -l`
    
    regex="[0-9][0-9]05[0-1][0-9][0-9]"
    if [[ "$roll" =~ $regex ]] ## Filename has correct roll
    then
    
        if [ $((count)) -gt 1 ]; then
            echo "Count: $count , $zip" ## Student submitted more than 2 files
            
            mkdir "../Output/Extra/$roll" 
            mv * "../Output/Extra/$roll" 
            echo "$roll 0" >> ../Marks.txt

        else
            populateMarksSheet
    
        fi
    else
        echo "filename in wrong format"
        csvRoll=`grep "$stdName" CSE_322.csv | cut -c 3-9`
        lines=`grep "$stdName" CSE_322.csv | cut -c 3-9 | wc -l`
        if [ $((lines)) -gt 1 ] 
        then
            ## More than 1 student with same name in csv
            echo "$lines"
            for $std in $csvRoll
            do
                echo $std
                found=`grep "$std" ../Absents.txt | wc -l` #found in absentee list

                ## if found = 1; student found. delete from absentee list, and rename folder
            done
            

        else
            # Only one student with this name in csv
            sed -i "/$csvRoll/d" ../Absents.txt # Deleting from absentees list

            if [ $((count)) -gt 1 ]; then
                echo "Count: $count , $zip" ## Student submitted more than 2 files

                mkdir "../Output/Extra/$csvRoll" 
                mv * "../Output/Extra/$csvRoll" 
                echo "$csvRoll 0" >> ../Marks.txt
                sed -i "/$csvRoll/d" ../Absents.txt
            else
                checkAbsenteeList
            fi
        fi

    fi
    
    cd ..
    rm "$zip"
done

rmdir temp

# Removing all .rar files.
## Assigning 0 marks inmarks list TODO
find . -iname "*.rar" | while read rar
do
    rm "$rar"
done

mv -f ../submissionsAll.zip submissionsAll.zip  # bringing back test input file :p 
