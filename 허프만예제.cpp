#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <chrono>
#include <cstdio>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	// Declare the output variables
	Mat org = imread("11.bmp");
	Mat dst, cdst, cdstP;
	const char* default_file = "11.bmp";
	const char* filename = argc >= 2 ? argv[1] : default_file;
	// Loads an image
	Mat src = imread(samples::findFile(filename), IMREAD_GRAYSCALE);
	// Check if image is loaded fine
	if(src.empty())
	{
		printf(" Error opening image\n");
		printf(" Program Arguments: [image_name -- default %s] \n", default_file);
		return -1;
	}
	// Edge detection
// 	Canny(src, dst, 50, 200, 3);

	// Copy edges to the images that will display the results in BGR
	cvtColor(src, cdst, COLOR_GRAY2BGR);
	cdstP = cdst.clone();
	// Standard Hough Line Transform
	vector<Vec2f> lines; // will hold the results of the detection

	auto start = std::chrono::high_resolution_clock::now();

	HoughLines(src, lines, 1, CV_PI / 180, 150, 0, 0); // runs the actual detection

	auto end = std::chrono::high_resolution_clock::now();
	auto time_cnt = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	String strTimer;
	double f64Count;

	if(time_cnt.count() >= 1000)
	{
		f64Count = (double)time_cnt.count() / 1000.;
		printf("%.2f ms\n", f64Count);
	}
	else
	{
		f64Count = (double)time_cnt.count();
		printf(("%.0f us\n"), f64Count);
	}

	printf("Line Count : %zu\n", lines.size());

	// Draw the lines
	for(size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(cdst, pt1, pt2, Scalar(0, 0, 255), 1, LINE_4);
	}
	// Probabilistic Line Transform
	vector<Vec4i> linesP; // will hold the results of the detection

	start = std::chrono::high_resolution_clock::now();

	HoughLinesP(src, linesP, 2, CV_PI / 720, 2, 5, 200); // runs the actual detection

	end = std::chrono::high_resolution_clock::now();
	time_cnt = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	if(time_cnt.count() >= 1000)
	{
		f64Count = (double)time_cnt.count() / 1000.;
		printf("%.2f ms\n", f64Count);
	}
	else
	{
		f64Count = (double)time_cnt.count();
		printf(("%.0f us\n"), f64Count);
	}

	printf("Line Count : %zu\n", linesP.size());

	// Draw the lines
	for(size_t i = 0; i < linesP.size(); i++)
	{
		Vec4i l = linesP[i];
		line(cdstP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2, LINE_AA);
		line(org, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2, LINE_AA);
	}
	// Show results
	imshow("Source", src);
	imshow("Detected Lines (in red) - Standard Hough Line Transform", cdst);
	imshow("Detected Lines (in red) - Probabilistic Line Transform", cdstP);
	imshow("Org Image HoughlinesP", org);
	// Wait and Exit
	waitKey();
	return 0;
}
