#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
		// получаем любую подключённую камеру
		CvCapture* capture = cvCreateCameraCapture(0); //cvCaptureFromCAM( 0 );
        assert( capture );
        IplImage* frame=0;
		IplImage* gray = 0;
		IplImage* dst = 0;

        cvNamedWindow("capture", CV_WINDOW_AUTOSIZE);
		cvNamedWindow("gray",CV_WINDOW_AUTOSIZE);
        cvNamedWindow("cvCanny",CV_WINDOW_AUTOSIZE);

        while(true){
                // получаем кадр
                frame = cvQueryFrame( capture );

                // показываем
                cvShowImage("capture", frame);
        
                char c = cvWaitKey(33);
                if (c == 27) { // нажата ESC
                        break;
                }
				gray = cvCreateImage( cvGetSize(frame), IPL_DEPTH_8U, 1 );
				dst = cvCreateImage( cvGetSize(frame), IPL_DEPTH_8U, 1 );
				cvCvtColor(frame, gray, CV_RGB2GRAY);
				cvCanny(gray, dst, 10, 90, 5);

				cvShowImage("capture",frame);
				cvShowImage("gray",gray);
				cvShowImage("cvCanny", dst );
                
        }
        // освобождаем ресурсы
        cvReleaseCapture(&capture );
		cvReleaseImage(&frame);
        cvReleaseImage(&gray);
        cvReleaseImage(&dst);
        cvDestroyAllWindows();
        return 0;
}
