# dualfisheyeequirectangular
Fast conversion of a dual fisheye video to equirectangular video with a mapping table

git clone https://github.com/RoblabWh/dualfisheyeequirectangular
cd dualfisheyeequirectangular
g++ -O2  -o 2fish2equi-video 2fish2equi-video.cpp  `pkg-config --cflags opencv` `pkg-config --libs opencv`
// -O2 2x faster execution
(or cmake . ; make)

./2fish2equi-video example.mp4 mapping-table-960-1920.txt

TODO:
Write a cuda kernel.
Proof timeing via outputs
