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
		IplImage* framex2=0;
		IplImage* gray = 0;
		IplImage* dst = 0;

        cvNamedWindow("capture", CV_WINDOW_AUTOSIZE);
		//cvNamedWindow("capture2", CV_WINDOW_AUTOSIZE);
		cvNamedWindow("gray",CV_WINDOW_AUTOSIZE);
        cvNamedWindow("cvCanny",CV_WINDOW_AUTOSIZE);

		int x = (int) (cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH) / 4);
		int y = (int) (cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT) / 4);

		frame = cvQueryFrame( capture );
		cvSetImageROI(frame, cvRect(x,y,320,240));
		framex2 = cvCreateImage(cvSize(frame->width, frame->height),IPL_DEPTH_8U, 1 );


        while(true){
 
				frame = cvQueryFrame( capture );

                char c = cvWaitKey(33);
                if (c == 27) { // нажата ESC
                        break;
                }
				gray = cvCreateImage( cvGetSize(frame), IPL_DEPTH_8U, 1 );
				dst = cvCreateImage( cvGetSize(frame), IPL_DEPTH_8U, 1 );
				cvCvtColor(frame, gray, CV_RGB2GRAY);
				cvCanny(gray, dst, 10, 120, 3);
				//cvResize
				cvShowImage("capture",frame);
				cvShowImage("gray",gray);
				cvShowImage("cvCanny", dst );

				cvResize(dst, framex2, 3);
                cvShowImage("capture2", framex2);
				
				cvReleaseImage(&gray);
				cvReleaseImage(&dst);
        }
        // освобождаем ресурсы
        cvReleaseCapture(&capture );
		cvReleaseImage(&frame);
        cvReleaseImage(&gray);
        cvReleaseImage(&dst);
        cvDestroyAllWindows();
        return 0;
}
