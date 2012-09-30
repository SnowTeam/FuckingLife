#include <Ogre.h>
#include "MoteurDeJeu.h";
#include "InputListener.h";

class AppDemarrage
{
public:
    AppDemarrage();
    ~AppDemarrage();

    bool start();
	bool initJoueur();
	bool initMap();
	void createFrameListener();

private:
    Ogre::Root *mRoot;
	Ogre::RenderWindow* mWindow;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;
	InputListener* mInputListener;
};
