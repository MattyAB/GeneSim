#pragma once

#include <vector>
#include "globals.h"

#include "CImg.h"
using namespace cimg_library;

struct IndivDrawData {
	uint16_t x;
	uint16_t y;
	uint8_t col[3];
};

struct FrameData {
	std::vector<IndivDrawData> drawdata;
};

class Render {
private:
	cimg_library::CImgList<uint8_t> imageList;
public:
	Render();
	void DrawFrame(FrameData data);
	void SaveVideo();
};