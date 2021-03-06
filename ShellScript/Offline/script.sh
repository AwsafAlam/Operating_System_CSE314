chmod +x SubmissionsAll.zip
unzip -q -o SubmissionsAll.zip
mv -f SubmissionsAll.zip ../SubmissionsAll.zip  # Replace with mv at the end of assignment

## If present before
if [ -f Absents.txt ]
then 
    rm Absents.txt
    rm Marks.txt
fi


if [ -d Output/ ]
then 
    rm -fr Output/ 
fi

mkdir Output
cd Output

mkdir Extra
cd ..


find . -iname "*.zip" > filelist.txt
# find . -iname "*.rar" >> filelist.txt

filelist=`cut -d "_" -f5 -s filelist.txt | cut -d "." -f1`
Raster=`cut -c 1-7 CSE_322.csv`

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

    if [ $flag = 0 ] ## item in CSV to present in folder
    then
        echo $item >> Absents.txt
        echo "$item 0" >> Marks.txt
    fi
done

function checkAbsenteeList()
{
    if [ "$csvRoll" = "$foldername" ]
    then
        cp -fr "$foldername" ../Output
        rm -fr "$foldername"
        echo "$csvRoll 10" >> ../Marks.txt
    else
        # regex="[0-9][0-9]05[0-1][0-9][0-9]"
        echo "$foldername -> $roll"
        if [[ "$foldername" =~ $regex ]]
        then
            # echo "Dirname matches partially";

            mv "$foldername/" "$csvRoll/"
            cp -fr "$csvRoll" ../Output
            rm -fr "$csvRoll"
            echo "$csvRoll 5" >> ../Marks.txt
        else
            # echo "doesn't match! $foldername";
            # dirname doesnt match roll (but correst roll in zip)
            mv "$foldername/" "$csvRoll/"
            cp -fr "$csvRoll" ../Output/Extra/
            rm -fr "$csvRoll"
            echo "$csvRoll 0" >> ../Marks.txt
            
        fi

    fi
}

function populateMarksSheet()
{
    if [ "$roll" = "$foldername" ]
    then
        cp -fr "$foldername" ../Output
        rm -fr "$foldername"
        echo "$roll 10" >> ../Marks.txt
    else
        regex="[0-9][0-9]05[0-1][0-9][0-9]"
        echo "$foldername -> $roll"
        if [[ "$foldername" =~ $regex ]]
        then
            # echo "Dirname matches partially roll";

            mv "$foldername/" "$roll/"
            cp -fr "$roll" ../Output
            rm -fr "$roll"
            echo "$roll 5" >> ../Marks.txt
        else
            # echo "$foldername doesn't match roll";
            # dirname doesnt match roll (but correst roll in zip)
            mv "$foldername/" "$roll/"
            cp -fr "$roll" ../Output/
            rm -fr "$roll"
            echo "$roll 0" >> ../Marks.txt
            
        fi

    fi

}

find . -iname "*.zip" | while read zip
do

    roll=`echo "$zip" | cut -d "_" -f5 | cut -d "." -f1` # Getting roll from zip file foldername
    stdName=`echo "$zip" | cut -d "_" -f1 | cut -c 3-`
    
    unzip -q -o "$zip" -d temp/
    cd temp
    foldername=`ls` # foldername
    count=`ls -1 | wc -l` # No. of folders after unzip
    
    regex="[0-9][0-9]05[0-1][0-9][0-9]"
    if [[ "$roll" =~ $regex ]] ## Filename has correct roll format
    then
    
        if [ $((count)) -gt 1 ]; then
            # Student submitted more than 2 files
            
            mkdir "../Output/$roll" 
            mv * "../Output/$roll" 
            echo "$roll 0" >> ../Marks.txt #Gets 0 marks

        else
            populateMarksSheet
        fi
    else
        echo "filename in wrong format for $stdName"
        
        csvRoll=`grep "$stdName" ../CSE_322.csv | cut -c 1-7`
        lines=`grep "$stdName" ../CSE_322.csv | cut -c 1-7 | wc -l`
        if [ $((lines)) -gt 1 ] 
        then
            # More than 1 student with same name in csv
            # echo "$lines , $csvRoll"
            searchAbsente=`grep "$csvRoll" ../Absents.txt | wc -l`

            if [ $((searchAbsente)) -gt 1 ] 
            then # We so not know which absentee is the actual person
                mkdir "../Output/Extra/$stdName" 
                mv * "../Output/Extra/$stdName" 
                    
            elif [ $((searchAbsente)) = 0 ]
            then       
                echo "Not found in absentee list"
                mkdir "../Output/Extra/$stdName" 
                mv * "../Output/Extra/$stdName" 
                
            else
                abs=`grep "$csvRoll" ../Absents.txt`
                sed -i "/$abs/d" ../Absents.txt # Deleting from absentees list
                mkdir "../Output/$csvRoll" 
                mv * "../Output/$csvRoll" 
                    
            fi

        elif [ $((lines)) = 0 ]
        then
          ## No student with this name in CSV      
            mkdir "../Output/Extra/$stdName" 
            mv * "../Output/Extra/$stdName" 
            # echo "$csvRoll 0" >> ../Marks.txt
            # sed -i "/$csvRoll/d" ../Absents.txt
            
        else
            # Only one student with this foldername in csv
            sed -i "/$csvRoll/d" ../Absents.txt # Deleting from absentees list

            if [ $((count)) -gt 1 ]; then
                echo "Count: $count , $zip , roll: $csvRoll" ## Student submitted more than 2 files

                mkdir "../Output/$csvRoll" 
                mv * "../Output/$csvRoll" 
                echo "$csvRoll 0" >> ../Marks.txt
                sed -i "/$csvRoll/d" ../Absents.txt
            else
                checkAbsenteeList
            fi
        fi

    fi
    
    cd ..
    rm "$zip"
    echo "---------------"
done

rmdir temp

# Removing all .rar files.
## Assigning 0 marks in marks list
# find . -iname "*.rar" | while read rar
# do
#     rm "$rar"
# done
rm filelist.txt
mv -f ../SubmissionsAll.zip SubmissionsAll.zip  # bringing back test input file :p 
sort -n Marks.txt > Mark.txt
rm Marks.txt

sort -n Absents.txt > AbsenteeList.txt
rm Absents.txt
