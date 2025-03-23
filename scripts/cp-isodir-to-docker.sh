echo "copy isodir to docker iso maker shared volume"
rm ../docker/shared/isodir -r
cp ./dist/isodir ../docker/shared/ -fr


# echo "will create iso from os files"
# oscdimg -n -d -m -b./dist/isodir/boot/myos.bin -yo./scripts/orderfile.txt ./dist/isodir ./dist/myos-0.iso

