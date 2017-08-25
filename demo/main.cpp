#include "Application.h"

#include <OgrePlatform.h>
#include <OgreException.h>
#include <OISException.h>
#include <iostream>

int main(int argc, char* argv[])
{	
	Application app;

	if (argc < 2)
	{
		std::cerr << "Must specify a video file name!" << std::endl;
		return 0;
	}

	const std::string& name = argv[1];
	app.setVideoFileName(name);

	try
	{
		app.run();
	}
	catch (Ogre::Exception& e)
	{
		std::cerr << e.getFullDescription().c_str() << std::endl;
	}
	catch (OIS::Exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
		
	return 0;
}
