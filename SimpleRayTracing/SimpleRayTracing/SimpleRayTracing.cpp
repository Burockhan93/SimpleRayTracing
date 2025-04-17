// SimpleRayTracing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <thread>
#include "Math/Matrix4.h"
#include "Math/Transform.h"
#include "pnglib/pngwriter.h"
#include "Light/Light.h"
#include "Light/PointLight.h"
#include "Object/Object.h"
#include <iostream>
#include "Math/Vec2.h"
#include "Builder\World.h"
#include "Math/Constants.h"
#include "Utils/RayTracer.h"
#include "oidn/include/OpenImageDenoise/oidn.h"
#include "oidn/include/OpenImageDenoise/oidn.hpp"
#include "ObjectHandler/OBJHandler.h"
#include "Utils/WorldSettings.h"


Vec3 mul_render(int x, int y, Camera& camera, World& world, int width_offset = 0, int height_offset = 0) {
	RayTracer tr;
	//construct a ray for through this pixel.
	Vec3 color;
	for (int n = 0; n < Constants::NUM_SAMPLES; n++) {
		Ray ray = camera.construct_ray(y, x);
		color = color + tr.trace_ray(ray, world, 0);//+ t.trace(ray, world, 3);
	}
	//pixels[width * (y - height_offset) + (x - width_offset)] = color / (double)(Constants::NUM_SAMPLES);
	return color / (double)(Constants::NUM_SAMPLES); 
}
void thread_task(size_t start, size_t end, size_t height, size_t width, Camera& camera, World& world, Vec3* pixels) {
	for (size_t i = start; i < end; i++) {
		for (size_t j = 0; j < width; j++) {
			Vec3 color = mul_render(i, j, camera, world, 0, 0);
			
			//rotate 90
			int w = j;
			int h = height - 1 - i;
			int new_index = w * height + h;

			pixels[new_index] = color;
		}
	}
}

void render_with_threads( size_t height, size_t width, Camera& camera, World& world, Vec3* pixels, size_t thread_number) {
	std::vector<std::thread> threads;
	size_t chunk_size = height / thread_number;
	for (size_t t = 0; t < thread_number; t++)
	{
		size_t start = t * chunk_size;
		size_t end = (t == thread_number - 1) ? height : (t + 1) * chunk_size;
		threads.emplace_back(thread_task, start, end,  height, width, std::ref(camera), std::ref(world), pixels);
	}
	for (auto& t : threads)
		t.join();
}
void denoise_image(Vec3* pixels, int height, int width) {
	std::cout << "Before Denoising: "
		<< pixels[0].x << ", " << pixels[0].y << ", " << pixels[0].z << std::endl;

	// Create OpenImageDenoise device
	oidn::DeviceRef device = oidn::newDevice();
	device.commit();

	// Convert Vec3 pixel data into a flat float buffer (RGB format)
	std::vector<float> colorBuffer(width * height * 3);
	for (int i = 0; i < width * height; i++) {
		colorBuffer[i * 3 + 0] = pixels[i].x;
		colorBuffer[i * 3 + 1] = pixels[i].y;
		colorBuffer[i * 3 + 2] = pixels[i].z;
	}

	// Allocate buffers using Storage::Host for proper alignment
	oidn::BufferRef inputBuf = device.newBuffer(colorBuffer.size() * sizeof(float), oidn::Storage::Host);
	oidn::BufferRef outputBuf = device.newBuffer(colorBuffer.size() * sizeof(float), oidn::Storage::Host);

	// Copy data to input buffer
	memcpy(inputBuf.getData(), colorBuffer.data(), colorBuffer.size() * sizeof(float));

	// Create and configure the denoising filter
	oidn::FilterRef filter = device.newFilter("RT"); // "RT" = optimized for ray tracing images
	filter.setImage("color", inputBuf, oidn::Format::Float3, width, height);
	filter.setImage("output", outputBuf, oidn::Format::Float3, width, height);
	filter.set("hdr", false);  // Set to true if using HDR images
	filter.commit();
	
	filter.execute();

	
	// Check for errors
	const char* errorMessage;
	if (device.getError(errorMessage) != oidn::Error::None) {
		std::cerr << "OIDN Error: " << errorMessage << std::endl;
		return;
	}

	// Retrieve denoised image data
	std::vector<float> outputBuffer(width * height * 3);
	memcpy(outputBuffer.data(), outputBuf.getData(), outputBuffer.size() * sizeof(float));

	// Convert back to Vec3 format
	for (int i = 0; i < width * height; i++) {
		pixels[i] = Vec3(outputBuffer[i * 3 + 0], outputBuffer[i * 3 + 1], outputBuffer[i * 3 + 2]);
	}
	std::cout << "after Denoising: "
		<< pixels[0].x << ", " << pixels[0].y << ", " << pixels[0].z << std::endl;

	std::cout << "Denoising complete!" << std::endl;
}
int main()
{
	std::cout << "Hello World!!2!\n";
	
	World world;
	world.build_world();
	int height = WorldSettings::height;
	int width = WorldSettings::width;
	Vec3* pixels = new Vec3[height*width];
	/*for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			pixels[i*height+j]= mul_render(i, j, world.m_camera, world, 0, 0);
		}
	}*/
	render_with_threads(height, width, world.m_camera, world, pixels, 20);
	//denoise_image(pixels, height, width);

	std::vector<unsigned char> image;
	image.resize(width * height * 4);

	for (unsigned i = 0; i < height * width; i++) {
		image[i * 4 + 0] = pow(std::min(std::max(pixels[i].x, 0.0), 1.0), 1.0) * 255;
		image[i * 4 + 1] = pow(std::min(std::max(pixels[i].y, 0.0), 1.0), 1.0) * 255;
		image[i * 4 + 2] = pow(std::min(std::max(pixels[i].z, 0.0), 1.0), 1.0) * 255;
		image[i * 4 + 3] = 255;
	}
	lodepng::encode("F:\\Programming\\Projects\\SimpleRayTracing\\SimpleRayTracing\\SimpleRayTracing\\Mathtestname.png", image, width, height);

}

