echo "copy isodir to docker iso maker shared volume"
rm ../docker/shared/isodir -r
cp ./dist/isodir ../docker/shared/ -fr

/bin/sh ../docker/docker-make-iso.sh
cp ../docker/shared/os0.iso ./dist/os0.iso
