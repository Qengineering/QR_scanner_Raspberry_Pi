#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
#include <zbar.h>
#include <lccv.hpp>
#include <opencv2/opencv.hpp>

using namespace std;

// Create zbar scanner
zbar::ImageScanner scanner;

struct decodedObject
{
    string type;
    string data;
    vector <cv::Point> location;
};

// Display barcode and QR code location
void display(cv::Mat &im, vector<decodedObject>&decodedObjects)
{
    // Loop over all decoded objects
    for(size_t i = 0; i<decodedObjects.size(); i++){
        vector<cv::Point> points = decodedObjects[i].location;
        vector<cv::Point> hull;

        // If the points do not form a quad, find convex hull
        if(points.size() > 4) cv::convexHull(points, hull);
        else                  hull = points;

        // Number of points in the convex hull
        size_t n = hull.size();

        for(size_t j=0; j<n; j++){
            cv::line(im, hull[j], hull[ (j+1) % n], cv::Scalar(255,0,0), 3);
        }
    }
}

void decode(cv::Mat &im, vector<decodedObject>&decodedObjects, int nb_frames)
{
    // Convert image to grayscale
    cv::Mat imGray;

    cv::cvtColor(im, imGray, cv::COLOR_BGR2GRAY);

    // Wrap image data in a zbar image
    zbar::Image image(im.cols, im.rows, "Y800", (uchar*)imGray.data, im.cols*im.rows);

    // Scan the image for barcodes and QRCodes
    int res = scanner.scan(image);

    if (res > 0) {
        // Print results
        for(zbar::Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol){
            decodedObject obj;

            obj.type = symbol->get_type_name();
            obj.data = symbol->get_data();
            // Obtain location

            for(int i = 0; i< symbol->get_location_size(); i++){
                obj.location.push_back(cv::Point(symbol->get_location_x(i),symbol->get_location_y(i)));
            }
            decodedObjects.push_back(obj);

            // debug - print type and data
            cout << nb_frames << endl;
            cout << "Type : " << obj.type << endl;
            cout << "Data : " << obj.data << endl << endl;

        }
        display(im, decodedObjects);
    }
}

int main()
{
    int ch=0;
    int nb_frames=0;
    cv::Mat image;
    lccv::PiCamera cam;
    float f;
    float FPS[16];
    int i, Fcnt=0;
    chrono::steady_clock::time_point Tbegin, Tend;

    for(i=0;i<16;i++) FPS[i]=0.0;

    cam.options->video_width= 1024;     //keep this resolution!!!
    cam.options->video_height= 768;     //it will be cropped to 720x720
    cam.options->framerate=15;
    cam.options->verbose=true;
    cam.startVideo();

    // Configure scanner
    // see: http://zbar.sourceforge.net/api/zbar_8h.html#f7818ad6458f9f40362eecda97acdcb0
    scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 0);
    scanner.set_config(zbar::ZBAR_QRCODE, zbar::ZBAR_CFG_ENABLE, 1);

    std::cout<<"Sample program for scanning QR codes"<<std::endl;
    std::cout<<"Press ESC to stop."<<std::endl;

    while(ch!=27){
        if(!cam.getVideoFrame(image,1000)){
            std::cout<<"Timeout error"<<std::endl;
        }
        else{
            //capture
            cv::Mat crop_img = image(cv::Range(24,744), cv::Range(152,872));

            // Find and decode barcodes and QR codes
            vector<decodedObject> decodedObjects;
            decode(image, decodedObjects, nb_frames++);

            //calculate frame rate (just for your convenience)
            Tend = chrono::steady_clock::now();
            f = chrono::duration_cast <chrono::milliseconds> (Tend - Tbegin).count();
            Tbegin = Tend;
            if(f>0.0) FPS[((Fcnt++)&0x0F)]=1000.0/f;
            for(f=0.0, i=0;i<16;i++){ f+=FPS[i]; }
            putText(image, cv::format("FPS %0.2f", f/16),cv::Point(10,20),cv::FONT_HERSHEY_SIMPLEX,0.6, cv::Scalar(0, 0, 255));

            //show result
            cv::imshow("Video",image);
            ch=cv::waitKey(10);
        }
    }
    cam.stopVideo();
    cv::destroyWindow("Video");
    return 0;
}
