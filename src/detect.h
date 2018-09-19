#pragma once

#include <string>
#include <vector>
#include <fstream>

#include <opencv/cv.h>
#include <QJsonObject>

#include "molluscoid.h"
#include "common.h"

class moldec {
	const cv::Mat origin;
	std::vector<contour> contours;
	cv::Mat thresholded;
	std::vector<molluscoid> molluscoids;

	void find_contours();
	void extract_molluscoids();
	static bool decide(const contour& cont);
	double determine_threshold(const cv::Mat&) const;
	void threshold(const cv::Mat&);

	std::string get_color(const cv::Mat& img) const;
public:
	moldec(const cv::Mat& img);
	~moldec();

	std::vector<contour> get_contours() const;

	void write_images(QJsonObject &meta, const std::string& imageName, const std::string& dest) const;
};

