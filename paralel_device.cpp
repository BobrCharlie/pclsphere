#include "paralel_device.h"
ParalelDevice::ParalelDevice(){
	kernelFile = defaultKernelFile;
	width = defaultWidth;
	height = defaultHeight;
	init();
}

ParalelDevice::ParalelDevice(std::string _kernelFile, int _width, int _height){
	kernelFile = _kernelFile;
	width = _width;
	height = _height;
	init();
}

void ParalelDevice::init(){
	printInfo();
	size = width*height;
	std::ifstream file(kernelFile);
	cl::string programCode(std::istreambuf_iterator<char>(file), (std::istreambuf_iterator<char>()));
	cl::Program program(programCode);
	program.build();
	cl_int buildErr;
	auto buildInfo = program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(&buildErr);
	std::cout << buildInfo[0].second;
	cl::DeviceCommandQueue defaultDeviceQueue = cl::DeviceCommandQueue::makeDefault(cl::Context::getDefault(), cl::Device::getDefault());
	
	processor = new cl::KernelFunctor<cl::Buffer, cl::Buffer, cl::Buffer>(program, "gradient");
}
void ParalelDevice::printInfo(){
	std::cout << "work group"<<cl::Device::getDefault().getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>()<<std::endl;
	std::cout << "compute units"<<cl::Device::getDefault().getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>() << std::endl;
	auto sizes = cl::Device::getDefault().getInfo<CL_DEVICE_MAX_WORK_ITEM_SIZES >();
	std::cout << "compute units" << sizes[0]<<":"<<sizes[1]<<":"<<sizes[2] << std::endl;
}
void ParalelDevice::process(cl_uchar* inLeft, cl_uchar* inRight, void* out){

	
	
	
	/*std::vector<cl_uchar> left(inLeft, inLeft + size);
	std::vector<cl_uchar> right(inRight, inRight + size);*/
	//std::vector<cl_uchar> outv(out, out + size);
	//std::vector<int> outv(size);
	/*cl::Buffer leftBuffer(begin(left), end(left), false);
	cl::Buffer rightBuffer(begin(right), end(right), false);*/
	/*copy(outBuffer, begin(outv), end(outv));
	cv::Mat s = cv::Mat(480, 640, CV_8UC1);
	s.data = &outv[0];
	imshow("s", s);*/
	cl::Buffer leftBuffer(CL_MEM_READ_WRITE, size);
	cl::Buffer rightBuffer(CL_MEM_READ_WRITE, size);
	cl::enqueueWriteBuffer(leftBuffer, CL_TRUE, 0, size, inLeft);
	cl::enqueueWriteBuffer(rightBuffer, CL_TRUE, 0, size, inRight);
	
	cl::Buffer outBuffer(CL_MEM_READ_WRITE, size*20);
	

	processor->operator()(cl::EnqueueArgs(cl::NDRange(640, 480), cl::NDRange(8, 8)), leftBuffer, rightBuffer, outBuffer, err);
	
	enqueueReadBuffer(outBuffer, CL_TRUE, 0, size*20, out);
	
	
}
