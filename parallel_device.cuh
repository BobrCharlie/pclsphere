#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

class ParallelDevice
{

int devId;
	int width, height, size, defaultHeight=480, defaultWidth=640;
	int err;
public:
	ParallelDevice();
	~ParallelDevice();
	 void process(uchar* inLeft, uchar* inRight, void* out);
private:

};


