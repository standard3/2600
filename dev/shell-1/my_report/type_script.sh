#!/usr/bin/bash

input=$1

for path in $(find $input -type f -executable -print | sort -z)
do
    shebang=$(grep -m1 "" $path)

    if [[ $shebang == *"perl"* ]];
    then
        echo "Perl $path"

    elif [[ $shebang == *"python"* ]];
    then
        echo "Python $path"

    elif [[ $shebang =~ *'(sh|bash)'* ]];
    then
        echo "Shell $path"
    fi    
done