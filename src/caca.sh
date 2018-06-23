for arch in $(ls *.shame.log)
do
	nombre="${arch%.*}"
	nombre="${nombre%.*}"
	echo "arch $arch"
	mv $arch $nombre.ref.log
done
