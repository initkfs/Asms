#!/usr/bin/env bash

__dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

buildDir="$__dir/build"

if [[ ! -e $buildDir ]]; then
mkdir "$buildDir"
fi

osDir="$buildDir/os"
if [[ ! -e $osDir ]]; then
mkdir "$osDir"
fi

objectDir=$buildDir/o
if [[ ! -e $objectDir ]]; then
mkdir "$objectDir"
fi

loaderName=bootloader
loaderBinFile=$objectDir/${loaderName}.bin
# -g Option: Enabling Debug Information.
nasm -g -f bin -l "${loaderName}.list" -o "$loaderBinFile" "$__dir/${loaderName}.asm"
if [[ ! $? == 0 ]]; then
echo "Error. Compile bootloader failed. Exit"
exit 1
fi

osImage=$buildDir/os.img
dd if=/dev/zero of="$osImage" bs=1024 count=4040
dd if="$loaderBinFile" of="$osImage" conv=notrunc

kernelName=kernel
kernelFile=$objectDir/$kernelName
nasm -g -f bin -l "${kernelName}.list" -o "$kernelFile" "$__dir/${kernelName}.asm"
if [[ ! $? == 0 ]]; then
echo "Error. Compile kernel failed. Exit"
exit 1
fi

#ld --oformat binary -o "$osDir/$kernelName" "$kernelFile" 

dd if="$kernelFile" of="$osImage" bs=512 seek=1 conv=notrunc
#dd if="$osDir/$kernelName" of="$osImage" bs=512 seek=1 conv=notrunc

#genisoimage -o "$buildDir/os.iso" "$osDir"
#https://stackoverflow.com/questions/6142925/how-can-i-use-bochs-to-run-assembly-code
#https://stackoverflow.com/questions/43786251/int-13h-42h-doesnt-load-anything-in-bochs
bochs -qf /dev/null -rc "$__dir/bochs_debug.rc" 'clock: sync=realtime, time0=local' ' display_library: x, options="gui_debug' 'megs: 128' 'boot: c' "ata0-master: type=disk, path=$osImage, mode=flat, cylinders=0, heads=0, spt=0, model=\"Generic 1234\", biosdetect=auto, translation=auto"

#qemu-system-x86_64 -net none -usbdevice tablet -fda "$osImage"
#mkisofs -o "${flpFile}.iso" -b "flpFile" cdiso/
echo "Return code: $?"

