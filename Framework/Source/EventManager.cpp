//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#include "EventManager.h"
#include "Renderer.h"
#include "Sound.h"
#include "ParticleSystem.h"
#include "World.h"

#include <GLFW/glfw3.h>
#include "fmod.hpp"
#include "fmod_errors.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "../Assets/dirent.h"

using namespace std;


// Time
double EventManager::sLastFrameTime = glfwGetTime();
float  EventManager::sFrameTime = 0.0f;

// Mouse
double EventManager::sLastMousePositionX = 0.0f;
float  EventManager::sMouseDeltaX = 0.0f;
double EventManager::sLastMousePositionY = 0.0f;
float  EventManager::sMouseDeltaY = 0.0f;

// Window
GLFWwindow* EventManager::spWindow = nullptr;

// Sound
Sound sound;
FMOD_DSP_PARAMETER_FFT *fftParameter;
float val;
unsigned int len;
char s[256];
int windowsize = 2048;
float *specLeft = new float[windowsize / 2];
float *specRight = new float[windowsize / 2];
float *spec = new float[windowsize / 2];
float smoothedVolume = 0;
float currentVolume = 0;

float energyBuffer[43];
int index = 0;



void EventManager::Initialize()
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		exit(-1);
	}
		
	glfwWindowHint(GLFW_SAMPLES, 4);
    
#if defined(PLATFORM_OSX)
    // OS X would use legacy opengl by default, and wouldn't be able to load shaders
    // This is the proper way to setup GLFW to use modern OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_DEPTH_BITS, 32);
    
#else
    // Allow older laptops to run the framework, even though, our framework
    // is compatible with OpenGL 3.3 (which removed many deprecated features)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_DEPTH_BITS, 32);
	LoadMusicFileNames();
#endif
    
    
	// Open a window and create its OpenGL context
	glfwWindowHint(GLFW_RESIZABLE, 0);
	spWindow = glfwCreateWindow(1024, 768, "NOISE", nullptr, nullptr);

	if (spWindow == nullptr)
	{
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		exit(-1);
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(spWindow, GLFW_STICKY_KEYS, GL_TRUE);

	// Initial mouse position
	glfwPollEvents();
	double x, y;
	glfwGetCursorPos(spWindow, &x, &y);

	sLastMousePositionX = x;
	sLastMousePositionY = y;

	// Initial time
	sLastFrameTime = glfwGetTime();

	//initialize sound
	sound = Sound();
	sound.initialize();
	sound.playSong("../Assets/Harder Better Faster.mp3");
	for (int i = 0; i < 43; i++){
		energyBuffer[i] = 0;
	}
}

void EventManager::Shutdown()
{
	// Close OpenGL window and terminate GLFW
	//glfwTerminate();
	spWindow = nullptr;

}

void EventManager::Update()
{

	static bool m_pressed = 0;
	if(glfwGetKey(EventManager::GetWindow(), GLFW_KEY_M) == GLFW_PRESS && !m_pressed){
		
		m_pressed = 1;
		static int song = 0;
		if(filenames.size() > 0){
			song = (song + 1) % filenames.size();
			sound.playSong(std::string("../Assets/" + filenames[song]).c_str());
		}
		
	}
	if(glfwGetKey(EventManager::GetWindow(), GLFW_KEY_M) == GLFW_RELEASE){
		m_pressed = 0;
	}
	// Update inputs / events
	glfwPollEvents();

	// Update mouse position
	double x, y;
	glfwGetCursorPos(spWindow, &x, &y);
	sMouseDeltaX = static_cast<float>( x - sLastMousePositionX );
	sMouseDeltaY = static_cast<float>( y - sLastMousePositionY );
	sLastMousePositionX = x;
	sLastMousePositionY = y;

	// Update frame time
	double currentTime = glfwGetTime();
	sFrameTime = static_cast<float>(currentTime - sLastFrameTime);
	sLastFrameTime = currentTime;

	// update sound
	sound.update();

	sound.fft->setParameterInt(FMOD_DSP_FFT_WINDOWSIZE, windowsize);
	sound.fft->getParameterFloat(FMOD_DSP_FFT_DOMINANT_FREQ, &val, 0, 0);
	sound.fft->getParameterData(FMOD_DSP_FFT_SPECTRUMDATA, (void **)&fftParameter, &len, s, 256);
	float globalVolume = 0;
	float energy = 0;
	for (int i = 0; i < windowsize / 2; i++){
		specLeft[i] = fftParameter->spectrum[0][i];
		specRight[i] = fftParameter->spectrum[1][i];
		spec[i] = specLeft[i] + specRight[i] / 2;
		energy += specLeft[i] * specLeft[i] + specRight[i] * specRight[i];
		globalVolume += spec[i];
	}
	globalVolume = (globalVolume / 1024) * 500;//do the average volume then multiply by 500 because its too small
	smoothedVolume += (globalVolume - smoothedVolume) * 0.1;
	currentVolume = smoothedVolume;

	//BEAT DETECTION

	//fill buffer
	energyBuffer[index] = energy;
	//find buffer average
	float energyAverage = 0;
	for (int i = 0; i < 43; i++){
		energyAverage += energyBuffer[i];
	}
	energyAverage = energyAverage / 43;
	//find variance
	float energyVariance = 0;
	for (int i = 0; i < 43; i++){
		energyVariance = (energyAverage - energyBuffer[i]) * (energyAverage - energyBuffer[i]);
	}
	energyVariance = energyVariance / 43;
	//find C
	float C = -0.0000015 * energyVariance + 1.5142857;
	if (energyBuffer[index] > C * energyAverage){
		World::GetInstance()->TriggerBeat();
	}
	if (index == 42){
		index = 0;
	}
	else{
		index++;
	}


}

std::vector<std::string> EventManager::filenames = std::vector<std::string>(0);

void EventManager::LoadMusicFileNames(){
	std::string folder = "../Assets/";
	DIR *dir;
	struct dirent *ent;
	//printf("In Folder: %s\n", folder.c_str());
	if ((dir = opendir (folder.c_str())) != NULL) {
		while ((ent = readdir (dir)) != NULL) {
			std::string filename = std::string(ent->d_name);
			int len = filename.length();
			if(filename != std::string("..") && filename != std::string("."))
				if(filename.substr(len-3, 3) == std::string("mp3")){
					filenames.push_back(filename);
				}
		}
		closedir (dir);
	}
	else {
		perror ("could not open folder");
	}
	
}

float EventManager::GetFrameTime()
{
	return sFrameTime;
}

bool EventManager::ExitRequested()
{
	return glfwGetKey(spWindow, GLFW_KEY_ESCAPE ) == GLFW_PRESS || glfwWindowShouldClose(spWindow);
}

GLFWwindow* EventManager::GetWindow()
{
	return spWindow;
}

float EventManager::GetMouseMotionX()
{
	return sMouseDeltaX;
}

float EventManager::GetMouseMotionY()
{
	return sMouseDeltaY;
}
float EventManager::GetCurrentVolume(){
	return currentVolume;
}
float* EventManager::GetCurrentSpec(){
	return spec;
}
void EventManager::EnableMouseCursor()
{
	glfwSetInputMode(spWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void EventManager::DisableMouseCursor()
{
	glfwSetInputMode(spWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

float EventManager::GetRandomFloat(float min, float max)
{
	float value = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

	return min + value*(max - min);
}
