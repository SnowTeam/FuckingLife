#include <Ogre.h>
#include <OIS.h>

class InputListener: public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::MouseListener, public OIS::KeyListener
{
public:
	InputListener(Ogre::RenderWindow *wnd, Ogre::Camera *camera);
	~InputListener();
	void InputListener::startOIS();
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	void windowResized(Ogre::RenderWindow* wnd);
	void windowClosed(Ogre::RenderWindow* wnd);
	bool mouseMoved(const OIS::MouseEvent &e);
	bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool keyPressed(const OIS::KeyEvent &e);
	bool keyReleased(const OIS::KeyEvent &e);

private:
    Ogre::RenderWindow* mWindow;
    Ogre::Camera*       mCamera;

    OIS::InputManager*  mInputManager;
    OIS::Mouse*         mMouse;
    OIS::Keyboard*      mKeyboard;
};