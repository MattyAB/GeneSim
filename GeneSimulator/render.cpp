#include "render.h"

#include "CImg.h"
using namespace cimg_library;

Render::Render()
{

}

void Render::DrawFrame(FrameData data)
{
	// Initialise a CImg with size and initial pixel value 0xff
	CImg<uint8_t> image(_boardsize_ * _renderscale_, _boardsize_ * _renderscale_, 1, 3);

	std::string filename = "frame.bmp";

	for (IndivDrawData draw : data.drawdata)
	{
		image.draw_rectangle(draw.x * _renderscale_ + 1, draw.y * _renderscale_ + 1, (1 + draw.x) * _renderscale_, (1 + draw.y) * _renderscale_, draw.col, 1.0);
	}

	// For some reason it takes issue with png. Let's use bmp for now
	//image.save_png(filename.c_str(), 3);
	image.save(filename.c_str());
}