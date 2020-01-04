#include <iostream>
#include <ctime>
#include <cmath>

#include "opencv2/opencv.hpp"

#define WIDTH 640
#define HEIGHT 480

using namespace std;
using namespace cv;

int main () {
	VideoCapture cap(0);
	if (!cap.isOpened()){
		cout << "Error opening video stream or file" << endl;
		return -1;
	}
	cap.set(CAP_PROP_FRAME_WIDTH, WIDTH);
    cap.set(CAP_PROP_FRAME_HEIGHT, HEIGHT);

	clock_t frame_start;
	int fps = 0;

	Mat frame;
	bool quit = false;
	while (!quit){
		frame_start = clock();

		cap >> frame;
		if (frame.empty()) {
			break;
		}


		for (int i = 0; i < frame.rows; i++) {
			for (int j = 0; j < frame.cols * frame.channels(); j += 3) {
				// frame.ptr<uchar>(i)[j] = 0;
				// frame.ptr<uchar>(i)[j + 1] = 0;
				// frame.ptr<uchar>(i)[j + 2] = 255;

				uchar r = frame.ptr<uchar>(i)[j + 2];
				uchar g = frame.ptr<uchar>(i)[j + 1];
				uchar b = frame.ptr<uchar>(i)[j];
				uchar g_b_diff;

				if (g > b) {
					g_b_diff = g - b;
				} else {
					g_b_diff = b - g;
				}


				if (r > g && r > b && g_b_diff < 20) {
					uchar r_g_diff = r - g;
					uchar r_b_diff = r - b;
					uchar diff;

					if (r_g_diff > r_b_diff) {
						diff = g;
					} else {
						diff = b;
					}

					if (diff * 2.5 <= r) {
						frame.ptr<uchar>(i)[j] = 0;
						frame.ptr<uchar>(i)[j + 1] = 0;
						frame.ptr<uchar>(i)[j + 2] = 0;
					}

				}
			}
		}
		putText(frame, "FPS: " + to_string(fps), Point(0, 30), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 255), 2);

		imshow("Frame", frame);

		fps = (int) ((float) CLOCKS_PER_SEC / (float) (clock() - frame_start));

		int key = waitKey(5);
		switch (key) {
			// Key 27 is the escape key.
			case 27:
				quit = true;
				break;
			default:
				break;
		}
	}

	cap.release();
	destroyAllWindows();

	return 0;
}
