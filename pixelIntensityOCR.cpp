#include <iostream>
#include <string>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <string>
#include <cstdio>
#include <vector>

using namespace std;
using namespace cv;


std::string folderpath="/media/hoh-6/Datos/David/U/ai/database/DataBase_Letras/";
std::stringstream path;
Mat frame;

FILE *fp;

int main(void)
{
	
	//if((fp=fopen("datosEntrenamientoLetras.data", "w+"))==NULL) { 
	if((fp=fopen("intensidadletras.data", "w+"))==NULL) {
		printf("Cannot open file.\n"); 
		exit(1); 
	} 
	namedWindow("window",1);

	for(int i=1; i<6;i++){
		for(int j=1; j<21;j++){
			std::stringstream path;
			path<<folderpath<<char(i+64)<<"_4_("<<j<<").jpg"; //i+1

			//load images
			frame= imread(path.str().c_str());
			//frame= imread("b.jpg");
			Mat frameGris;
			cvtColor(frame,frameGris,CV_BGR2GRAY);
			GaussianBlur(frameGris, frameGris, Size(3, 3), sqrt(2), sqrt(2), 0);
			threshold(frameGris,frameGris,128,255,CV_THRESH_OTSU);
			//frameGris= frameGris(Range(5,frameGris.rows-5), Range(5,frameGris.cols-5));
			frameGris= frameGris/255;
			fprintf(fp,"%c",char(i+64));
			for (int ii = 0; ii < frameGris.rows; ii++){
				for(int jj=0; jj<frameGris.cols; jj++){
					
					fprintf(fp,", %f",frameGris.at<double>(ii,jj));
				}
			}
			fprintf(fp,"\n");	
						
			/*IplImage IplimagenUmbral = frameGris;
			IplImage Iplimagen = frame;

			blobs = CBlobResult( &IplimagenUmbral,NULL,255);

			CBlob *currentBlob;	

			blobs.Filter( blobs, B_INCLUDE, CBlobGetArea(), B_GREATER,  200);

			int numBlobs=blobs.GetNumBlobs();

			Mat frameEsc;

			int cont=0;

			if(numBlobs==1){
				for (int ii = 0; ii < blobs.GetNumBlobs(); ii++ )
				{
					currentBlob = blobs.GetBlob(ii);
					currentBlob->FillBlob(&Iplimagen, CV_RGB( 0, 0, 255));
					
					Mat feature=momentosHu(frameGris);
					fprintf(fp,"%c",char(i+64)); 
					for(int jj=0; jj<feature.rows; jj++){
							fprintf(fp,", %f",feature.at<double>(jj,0)); 
					}
					fprintf(fp,"\n");
				imshow("window",frame);    
				waitKey(1000);
				}
			}*/


			/*imshow("window",frameGris);    
			waitKey(1000);*/
		}
	}
	
    return 0;
}