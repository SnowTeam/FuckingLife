#include "MoteurDeJeu.h";

MoteurDeJeu::MoteurDeJeu(Ogre::RenderWindow* window,Ogre::Root* root)
{
	mWindow = window;
	mRoot = root;
}

bool MoteurDeJeu::boucle()
{
	while(true)
	{
		Ogre::WindowEventUtilities::messagePump();
 
		if(mWindow->isClosed())
			return false;
 
		if(!mRoot->renderOneFrame())
			return false;
	}
}