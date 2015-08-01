//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#include "Renderer.h"
#include "World.h"
#include "EventManager.h"
#include "Sound.h"

#include <fmod.hpp>
#include <fmod_errors.h>


int main(int argc, char*argv[])
{
	EventManager::Initialize();
	Renderer::Initialize();

	World world;

	if (argc > 1)
	{
		world.LoadScene(argv[1]);
	}
	else
	{
		// TODO - You can alternate between different scenes for testing different things
		// Static Scene contains no animation
		// Animated Scene does
#if defined(PLATFORM_OSX)		//Bad OS!
//		world.LoadScene("Scenes/AnimatedScene.scene");
//		world.LoadScene("Scenes/StaticScene.scene");
//		world.LoadScene("Scenes/CoordinateSystem.scene");
#else
		world.LoadScene("../Assets/Scenes/NOISE.scene");
	//	world.LoadScene("../Assets/Scenes/AnimatedScene.scene");
	//	world.LoadScene("../Assets/Scenes/StaticScene.scene");
	//	world.LoadScene("../Assets/Scenes/CoordinateSystem.scene");
#endif
	}

	// Main Loop
	do
	{
		// Update Event Manager - Frame time / input / events processing / sound
		EventManager::Update();

		// Update World
		float dt = EventManager::GetFrameTime();
		float currentVolume = EventManager::GetCurrentVolume();
		float* currentSpec = EventManager::GetCurrentSpec();
		world.Update(dt, currentVolume, currentSpec);

		// Draw World
		world.Draw();
	}
	while(EventManager::ExitRequested() == false);

	Renderer::Shutdown();
	EventManager::Shutdown();

	return 0;
}
