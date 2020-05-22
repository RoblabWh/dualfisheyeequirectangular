# dualfisheyeequirectangular
Fast conversion of dual fisheye video to equirectangular video with a mapping table

g++ -O2  -o 2fish2equi-video 2fish2equi-video.cpp  `pkg-config --cflags opencv` `pkg-config --libs opencv`
// -O2 2x faster execution

TODO:
Write a cuda kernel.
Proof timeings via outputs
