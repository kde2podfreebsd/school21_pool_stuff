#!/bin/zsh
if [[ $# -lt 1 ]]; then
 echo "ERROR:\t\tWrong arguments"
    echo "Message:\tNot enough arguments. Exactly 1 argument required"
 exit 1
elif [[ $# -gt 1 ]]; then
 echo "ERROR:\t\tWrong arguments"
    echo "Message:\tToo many arguments. Exactly 1 argument required"
 exit 1
fi

rel_filepath=$1
git_root=$(git rev-parse --show-toplevel)
current_dir_prefix=$(git rev-parse --show-prefix)
abs_filepath=${git_root}/${current_dir_prefix}/${rel_filepath}

if [[ $rel_filepath = /* ]]; then
 echo "ERROR:\t\tWrong arguments"
    echo "Message:\tFilepath argument must be a relative path and start from root of this repository"
 exit 1
elif [[ -d $abs_filepath ]]; then
    echo "ERROR:\t\tWrong arguments"
 echo "Message:\t'${rel_filepath}' is a directory, but must be a file!"
 exit 1
elif ! [[ -f $abs_filepath ]]; then
    echo "ERROR:\t\tWrong arguments"
 echo "Message:\t'${rel_filepath}' doesn't exist. Check if you enter relative part starting from root of the repository"
 exit 1
fi

current_line=0
declare -A unique_files_modifications
declare -A current_line_values

LINE_REGEX_FORMAT='^.+ - [0-9]+ - [0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2} - .+ - (sha|md)+.+$'

while IFS='' read -r line; do
    current_line=$(($current_line + 1))

    if [[ $line =~ $LINE_REGEX_FORMAT ]]; then

        logpath=$(echo $line | awk -F ' - ' '{print $1}')
        hash=$(echo $line | awk -F ' - ' '{print $4}')

        if [[ "${unique_files_modifications[$logpath]+_}" ]]; then

            if [[ $current_line_values[$logpath] != $hash ]]; then
                current_line_values[$logpath]=$hash
                ((unique_files_modifications[$logpath]++))
            fi
            
        else
            unique_files_modifications[$logpath]=0
            current_line_values[$logpath]=$hash
        fi

    else
        echo "ERROR:\t\tInvalid data in log file reading"
        echo "Message:\tWrong data format in line ${current_line}.\n
        Log file ${rel_filepath} valid format is '<relative/filepath> - <filesize in bytes> - <modification time: 2023-10-25 00:00> - <hash sum> - <algorithm, e.g. sha256>'"
        exit 1
    fi
done < $abs_filepath

sum_changes=0
for key in "${(@k)unique_files_modifications}"
do
    sum_changes=$((sum_changes + unique_files_modifications[$key]))
done

echo "${current_line} ${#unique_files_modifications[@]} ${sum_changes}"
