# man unzip
chmod +x SubmissionsAll.zip
unzip -o SubmissionsAll.zip
cp -r SubmissionsAll.zip ../SubmissionsAll.zip  # Replace with mv at the end of assignment

var=`ls`
clear
echo "" > filelist.txt
for variable in $var
do
    echo "-- $variable --">>filelist.txt
done
grep -E "[0-9]*" CSE_322.csv
# grep -v "^#" CSE_322.csv > output.csv