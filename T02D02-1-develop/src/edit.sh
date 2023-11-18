#!/bin/zsh
if [[ $# -lt 3 ]]; then
 echo "ERROR:\t\tWrong arguments"
 echo "Message:\tNot enough arguments. Exactly 3 arguments required"
 exit 1
elif [[ $# -gt 3 ]]; then
 echo "ERROR:\t\tWrong arguments"
 echo "Message:\tToo many arguments. Exactly 3 arguments required"
 exit 1
fi

rel_filepath=$1
old_line=$2
new_line=$3

git_root=$(git rev-parse --show-toplevel)
current_dir_prefix=$(git rev-parse --show-prefix)
abs_filepath=${git_root}/${current_dir_prefix}/${rel_filepath}

if [[ $rel_filepath = /* ]]; then
 echo "ERROR:\t\tWrong arguments"
    echo "Message:\t1st filepath argument must be a relative path and start from root of this repository"
 exit 1
elif [ -d $abs_filepath ]; then
 echo "ERROR:\t\tWrong arguments"
 echo "Message:\t'${rel_filepath}' is a directory, but must be a file!"
 exit 1
elif ! [ -f $abs_filepath ]; then
 echo "ERROR:\t\tWrong arguments"
 echo "Message:\t'${rel_filepath}' doesn't exist. Check if you enter relative part starting from root of the repository"
 exit 1
fi

sed -i '' "${line_number} s/${old_line}/${new_line}/g" "$abs_filepath"

new_file_size=$(wc -c $abs_filepath | awk '{printf $1}')
new_file_moddate=$(date -r $abs_filepath '+%Y-%m-%d %H:%M')
new_file_sha256=$(shasum -a 256 $abs_filepath | awk '{printf $1}')

trimmed_rel_filepath=$(python -c "import os.path; print os.path.relpath('$rel_filepath', '$(git rev-parse --show-toplevel)')")

echo "${trimmed_rel_filepath} - ${new_file_size} - ${new_file_moddate} - ${new_file_sha256} - sha256" >> ${git_root}/src/files.log
