#include <Ogre.h>

class MoteurDeJeu
{
public : 
	MoteurDeJeu(Ogre::RenderWindow* window,Ogre::Root* root);
	~MoteurDeJeu();
	bool MoteurDeJeu::boucle();

private : 
	Ogre::RenderWindow* mWindow;
	Ogre::Root *mRoot;
};