#include <Ogre.h>
#include <OIS.h>

class InputListener: public Ogre::FrameListener, public Ogre::WindowEventListener
{
public:
	InputListener(Ogre::RenderWindow *wnd, Ogre::Camera *camera);
	~InputListener();
	void InputListener::startOIS();
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	void windowResized(Ogre::RenderWindow* wnd);
	void windowClosed(Ogre::RenderWindow* wnd);

private:
    Ogre::RenderWindow* mWindow;
    Ogre::Camera*       mCamera;

    OIS::InputManager*  mInputManager;
    OIS::Mouse*         mMouse;
    OIS::Keyboard*      mKeyboard;
};