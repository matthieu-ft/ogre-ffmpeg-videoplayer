#include "BaseApplication.h"

#include <memory>

namespace Video
{
	class VideoPlayer;
}

namespace Ogre
{
	class SceneManager;
	class Viewport;
	class Camera;
	class OverlaySystem;
	class OverlayContainer;
	class Overlay;
}

class Application : public BaseApplication
{
public:
	Application();
	~Application();

	void setVideoFileName(const std::string& resourceName);

private:
	std::auto_ptr<Video::VideoPlayer> mVideoPlayer;
	std::string mVideoFileName;
	
protected:
	virtual void createScene();
	virtual void destroyScene();

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	std::auto_ptr<Ogre::OverlaySystem> mOverlaySystem;
	Ogre::OverlayContainer* mVideoPanel;
	Ogre::Overlay* mVideoOverlay;

	Ogre::SceneManager* mSceneMgr;
	Ogre::Viewport* mViewport;
	Ogre::Camera* mCamera;

	virtual bool mouseMoved(const OIS::MouseEvent&);
	virtual bool mousePressed(const OIS::MouseEvent&, OIS::MouseButtonID);
	virtual bool mouseReleased(const OIS::MouseEvent&, OIS::MouseButtonID);
	virtual bool keyPressed(const OIS::KeyEvent&);
	virtual bool keyReleased(const OIS::KeyEvent&);
};
