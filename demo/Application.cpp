#include "Application.h"

#include <OgreSceneManager.h>
#include <OgreViewport.h>
#include <OgreCamera.h>
#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreColourValue.h>
#include <OgreMaterialManager.h>
#include <OgreMaterial.h>
#include <OgrePass.h>
#include <OgreTextureUnitState.h>
#include <OgreTechnique.h>

#include <Overlay/OgreOverlayContainer.h>
#include <Overlay/OgreOverlay.h>
#include <Overlay/OgreOverlaySystem.h>
#include <Overlay/OgreOverlayManager.h>

#include "videoplayer.hpp"

#include "SDLMovieAudioFactory.h"

using namespace Ogre;

Application::Application()
{
}

Application::~Application()
{
	
}

void Application::setVideoFileName(const std::string& resourceName)
{
	mVideoFileName = resourceName;
}


void Application::createScene()
{
	mSceneMgr = Root::getSingleton().createSceneManager(ST_GENERIC);
	
	mCamera = mSceneMgr->createCamera("Camera");
	
	mViewport = mWindow->addViewport(mCamera);
	mViewport->setBackgroundColour(ColourValue(0.0, 0.0, 0.0, 1.0));


	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(".", "FileSystem", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	// Video material
	Ogre::MaterialPtr videoMaterial = Ogre::MaterialManager::getSingleton().create(
                    "VideoMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	Ogre::Pass *pass = videoMaterial->getTechnique( 0 )->getPass( 0 );
	pass->setLightingEnabled( false );
	Ogre::TextureUnitState *tex = pass->createTextureUnitState();

	mOverlaySystem.reset(new Ogre::OverlaySystem());
	mSceneMgr->addRenderQueueListener(mOverlaySystem.get());

	// Fullscreen video overlay
	// in frameRenderingQueued, we will adjust position/size to add black bars to the side when needed
	Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
	mVideoOverlay = overlayManager.create( "VideoOverlay" );
	mVideoPanel = static_cast<Ogre::OverlayContainer*>( overlayManager.createOverlayElement( "Panel", "PanelName" ) );
	mVideoPanel->setPosition( 0.0, 0.0 );
	mVideoPanel->setDimensions( 1.0, 1.0 );
	mVideoPanel->setMaterialName( "VideoMaterial" );
	mVideoOverlay->add2D( mVideoPanel );

	mVideoPlayer.reset(new Video::VideoPlayer());
	mVideoPlayer->setAudioFactory(new SDLMovieAudioFactory());
	mVideoPlayer->playVideo(mVideoFileName);

	if (!mVideoPlayer->getTextureName().empty())
	{
		tex->setTextureName(mVideoPlayer->getTextureName());
		mVideoOverlay->show();
	}
	else
		mVideoOverlay->hide();

	if (mVideoPlayer->getVideoWidth() > 0 && mVideoPlayer->getVideoHeight() > 0)
		mWindow->resize(mVideoPlayer->getVideoWidth(), mVideoPlayer->getVideoHeight());
}

void Application::destroyScene()
{
	mOverlaySystem.reset();
	mVideoPlayer.reset();
}

bool Application::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    mOISKeyboard->capture();
    mOISMouse->capture();

    mVideoPlayer->update();

	// Use black bars to correct aspect ratio
	if (mVideoPlayer->getVideoHeight() != 0)
	{
		double imageaspect = static_cast<double>(mVideoPlayer->getVideoWidth())/mVideoPlayer->getVideoHeight();

		int screenWidth = mWindow->getWidth();
		int screenHeight = mWindow->getHeight();

		double leftPadding = std::max(0.0, (screenWidth - screenHeight * imageaspect) / 2);
		double topPadding = std::max(0.0, (screenHeight - screenWidth / imageaspect) / 2);

		mVideoPanel->setPosition(leftPadding/screenWidth, topPadding/screenHeight);
		mVideoPanel->setDimensions((screenWidth - leftPadding*2)/screenWidth, (screenHeight - topPadding*2)/screenHeight);
	}

	return !mShutdown;
}


bool Application::mouseMoved(const OIS::MouseEvent& event)
{
	return true;
}

bool Application::mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID id)
{
	return true;
}

bool Application::mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID id)
{
	return true;
}

bool Application::keyPressed(const OIS::KeyEvent& event)
{
    if (event.key == OIS::KC_ESCAPE)
		mShutdown = true;

	if (event.key == OIS::KC_LEFT)
		mVideoPlayer->seek(mVideoPlayer->getCurrentTime() - 5.0);
	if (event.key == OIS::KC_RIGHT)
		mVideoPlayer->seek(mVideoPlayer->getCurrentTime() + 5.0);
	if (event.key == OIS::KC_DOWN)
		mVideoPlayer->seek(mVideoPlayer->getCurrentTime() - 30.0);
	if (event.key == OIS::KC_UP)
		mVideoPlayer->seek(mVideoPlayer->getCurrentTime() + 30.0);
	if (event.key == OIS::KC_SPACE)
	{
		if (mVideoPlayer->isPaused())
			mVideoPlayer->play();
		else
			mVideoPlayer->pause();
	}

	return true;
}

bool Application::keyReleased(const OIS::KeyEvent& event)
{
	return true;
}

