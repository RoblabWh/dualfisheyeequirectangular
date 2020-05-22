#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <opencv2/opencv.hpp>

// g++ -O2  -o 2fish2equi-video 2fish2equi-video.cpp  `pkg-config --cflags opencv` `pkg-config --libs opencv`
// -O2 2x faster execution

using namespace cv;

int main(int argc, char** argv) {
  FILE *fptr;
  int **mapx = NULL, **mapy = NULL;
  int height, width;
  int i,j;
  
    if ( argc != 3 )
    {
      printf("usage: %s <video> <mapping table>\n",argv[0]);
      printf("usage: %s VID_20200512_150448_848.mp4 mapping-table.txt\n",argv[0]);      
      return -1;
    }
    printf("Processing video %s with mapping table %s \n",argv[1], argv[2]);      
    // read map table
    fptr = fopen(argv[2],"r");
    if(fptr != NULL)       {
      if (fscanf(fptr," %d %d \n",&height, &width) < 1 )
	printf("Mapping file read error\n");
      printf("Open mapping file: h: %d w: %d\n",height,width);
      mapx = (int **)malloc(height * sizeof(int *));
      mapy = (int **)malloc(height * sizeof(int *));
      for (i = 0; i < height; i++) {
	mapx[i] = (int *) malloc(width * sizeof(int));
	mapy[i] = (int *) malloc(width * sizeof(int));
      }
      for (i = 0; i < height; i++) {
	for (j = 0; j < width; j++) {
	  if (fscanf(fptr,"%d %d\n",&(mapx[i][j]),&(mapy[i][j])) < 1)
	    	printf("Mapping file read error\n");;
	  //printf("%d %d %d %d\n",i,j,mapx[i][j],mapy[i][j]);
	}
      }
      fclose(fptr);    
      printf("Mapping file %s readed.\n",argv[2]);
    } //if      
    else printf("Error opening mapping file");

    // now read video
    VideoCapture cap(argv[1]); //.mp/ open the default camera
    if(!cap.isOpened()) {  // check if we succeeded
        return -1;
	printf("Could not open video file %s\n",argv[1]);
    }

    namedWindow("frame",1);
    int nrframes = 0;
    time_t now = time(NULL);
    printf("%d %s\n",nrframes,ctime(&now));
    Mat frame;
    Mat equiframe;
    for(;;)
    {
	
        cap >> frame; // get a new frame from camera
	if (nrframes == 0) equiframe = frame.clone();

        //map to equirectangular
	for (i = 0; i < height; i++) {
	  for (j = 0; j < width; j++) {
	    //printf("%d %d\n",i,j);
	    equiframe.at<Vec3b>(i,j) = frame.at<Vec3b>(mapy[i][j],mapx[i][j]);
	  }
	  }
	// Auf den Schirm Spoki
        imshow("frame", equiframe);
	nrframes++;
	// check time
	if ((nrframes % 300) == 0) {
	  time(&now);
	  printf("%d %s\n",nrframes,ctime(&now));
	}
        if(waitKey(1) == 27) break;
    }
    
    return 0;
      

}
