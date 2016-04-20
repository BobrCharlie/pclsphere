#include "parallel_device.cuh"

ParalelDevice::ParalelDevice()
{
	kernelFile = defaultKernelFile;
	width = defaultWidth;
	height = defaultHeight;
	init();
}


ParallelDevice(std::string _kernelFile, int _width, int _height)
{
	kernelFile = _kernelFile;
	width = _width;
	height = _height;
	init();
}

ParallelDevice::~ParallelDevice()
{

}

ParallelDevice::void process(cl_uchar* inLeft, cl_uchar* inRight, void* out);
{
	
}