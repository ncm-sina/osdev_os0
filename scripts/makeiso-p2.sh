echo "will create iso from os files"
oscdimg -n -d -m -b../docker/shared/isodir/boot/isolinux/isolinux.bin -yo./src/config/orderfile.txt ../docker/shared/isodir ./dist/myosp2.iso
# echo "will create iso from os files"
# oscdimg -n -d -m -b./dist/isodir/boot/myos.bin -yo./scripts/orderfile.txt ./dist/isodir ./dist/myos-0.iso

