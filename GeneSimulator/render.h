#pragma once

#include <vector>
#include "globals.h"

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
	
public:
	Render();
	void DrawFrame(FrameData data);
};