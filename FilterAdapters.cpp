#include "FilterAdapters.h"
#include "CudaProcessor.h"
#include "GPUFilters.h"
#include <iostream>

void CPUFilterAdapter::apply(cv::Mat& img)
{
	int kernelSize{ 3u };
	cv::Mat  kernel{ cv::Mat::ones(kernelSize, kernelSize, CV_32F) / (float)(kernelSize * kernelSize) };

	cv::filter2D(img, img, -1, kernel);
}

void GPUFilterAdapter::apply(cv::Mat& img)
{
	WarpGPUFilter filter{ img };

	CudaExecutor(img, filter).apply();
}

void FFTGPUFilterAdapter::apply(cv::Mat& img)
{
	FFTGPUFilter filter{ img };

	CudaExecutor(img, filter).apply();
}
