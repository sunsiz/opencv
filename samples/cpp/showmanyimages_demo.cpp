#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int showManyImages( const String winName, const vector<Mat> images );

int main( int argc, char** argv )
{
    vector<Mat> images;

    for ( int i = 0; i < 150; i++ )
    {
        Mat image( 240 + (rand()&200),320 + (rand()&200),CV_8UC3, Scalar( (rand()&255), (rand()&255), (rand()&255) ));
        circle( image, Point( image.cols / 2, image.rows / 2 ), image.cols / 3, Scalar( (rand()&255), (rand()&255), (rand()&255) ) );
        images.push_back( image );
        showManyImages("showManyImages test", images);
        waitKey();
    }
    return 0;
}

int showManyImages( const String winName, const vector<Mat> images )
{
    int nImg = images.size() > 150 ? 150 : (int)images.size();

    int x, y;

    // w - Maximum number of images in a row
    // h - Maximum number of images in a column
    int w = images.size() == 2 ? 2 : cvCeil( sqrt( images.size() ));
    int h = cvRound( sqrt( images.size() ));
    int size = images.size() <= 2 ? 300 : 300 / w * 2;
    // scale - How much we have to resize the image
    float scale;
    int max;

    if (nImg <= 0)
    {
        return -1;
    }

    Mat dispayImage = Mat::zeros( Size( size * w, size * h ), CV_8UC3);

    for (int i= 0, m = 0, n = 0; i < nImg; i++, m += size )
    {
        x = images[i].cols;
        y = images[i].rows;

        max = ( x > y ) ? x : y;
        scale = (float) ( (float) max / size );

        if ( i % w == 0 && m > 0 )
        {
            m = 0;
            n += size;
        }

        Mat imageROI = dispayImage( Rect( m, n, (int)( x / scale ), (int)( y / scale )));
        resize( images[i], imageROI, Size((int)( x / scale ), (int)( y / scale )));
    }

    imshow( winName, dispayImage );
    return 0;
}
