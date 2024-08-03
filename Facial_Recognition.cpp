#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void faceDetect(Mat img, CascadeClassifier faceCascade) {
    if (faceCascade.empty()) {
        cout << "XML file not loaded" << endl;
        return;
    }
    
    vector<Rect> faces;
    faceCascade.detectMultiScale(img, faces, 1.1, 10);

    int faceCount = 0;
    for (const Rect& face : faces) {
        rectangle(img, face.tl(), face.br(), Scalar(255, 0, 255), 3);
        faceCount++;
    }

    string temp = to_string(faceCount);
    putText(img, "No of faces:  " + temp, Point(25, 30), FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(255, 255, 255), 1);
    imshow("Picture Detection", img);
    waitKey(0);
}

void motionDetect(CascadeClassifier motionCascade) {
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << "Failed to open camera" << endl;
        return;
    }
    
    if (motionCascade.empty()) {
        cout << "XML file not loaded" << endl;
        return;
    }
    
    while (true) {
        Mat frame;
        cap.read(frame);
        if (frame.empty()) {
            cout << "Empty frame" << endl;
            break;
        }

        vector<Rect> faces;
        motionCascade.detectMultiScale(frame, faces, 1.1, 8);

        int faceCount = 0;
        for (const Rect& face : faces) {
            rectangle(frame, face.tl(), face.br(), Scalar(0, 255, 0), 3);
            faceCount++;
        }

        string temp = to_string(faceCount);
        putText(frame, "No of faces:  " + temp, Point(30, 45), FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(255, 255, 255), 1);
        imshow("Motion Detection", frame);
        if (waitKey(1) == 27) break;
    }
}

int main() {
    CascadeClassifier faceCascade, motionCascade;
    faceCascade.load("haarcascade_frontalface_default.xml");
    motionCascade.load("haarcascade_frontalface_default.xml");

    cout << "Welcome to Real-Time Face Recognition System !!" << endl;

    cout << "\n 1. Multiple Face-Recognition\n 2. Live Face-Recongition (Inbuilt-Camera)\n";
    cout << "\nSelect an option to continue.....\n";

    int option;
    cin >> option;

    switch (option) {
        case 1: {
            cout << "Enter File name & extension (.jpg/.png):\n";
            string path;
            cin >> path;
            Mat img = imread(path);
            if (img.empty()) {
                cout << "Failed to load image" << endl;
                return 1;
            }
            faceDetect(img, faceCascade);
            break;
        }
        case 2:
            cout << "Opening Camera....." << endl;
            motionDetect(motionCascade);
            break;
        default:
            cout << "Invalid Input\n";
            break;
    }

    return 0;
}
