#!/usr/bin/env bash

__dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

buildDir="$__dir/build"

if [[ ! -e $buildDir ]]; then
mkdir "$buildDir"
fi

if [[ ! -z $1 ]]; then
asmFiles=$1
else
asmFiles=$(find "$__dir" -maxdepth 1 -type f -name "*.asm" )
fi

backupIFS=IFS
IFS=$'\n'
for asmFile in $asmFiles
do

if [[ ! -e $asmFile ]]; then
echo "$asmFile does not exist, continue"
continue
else
echo "$asmFile found"
fi

ext=${asmFile##*.}

if [[ $ext == "asm" ]]; then

filename=$(basename "$asmFile")
filename="${filename%%.*}"

targetFile="$buildDir/$filename"
generatedFile="${targetFile}.o"

nasm -g -f elf64  -l "${asmFile}.list" -o "$generatedFile" "$asmFile"
echo "Generated: $generatedFile from $asmFile"

#for 64x: -m elf_i386
#ld "$generatedFile"  -o "$targetFile"
#gcc -static
gcc "$generatedFile" -o "$targetFile"

"$targetFile"
echo "Return code: $?"
fi
done
IFS=backupIFS

