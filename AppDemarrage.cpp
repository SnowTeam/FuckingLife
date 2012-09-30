#include "AppDemarrage.h"

AppDemarrage::AppDemarrage() : mRoot(0)
{
	mRoot = new Ogre::Root("plugins.cfg", "ogre.cfg", "Ogre.log");
	Ogre::ConfigFile configFile;
	configFile.load("resources.cfg");
	// Chargement de la configuration //
	Ogre::ConfigFile::SectionIterator seci = configFile.getSectionIterator();
	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
		}
	}
	// Fin chargement configuration //
}
AppDemarrage::~AppDemarrage()
{
    delete mRoot;
}
bool AppDemarrage::start()
{
	if(!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
	{
		return false;
	}
	mWindow = mRoot->initialise(true, "Fucking Life");
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	mSceneMgr = mRoot->createSceneManager("DefaultSceneManager", "Mon Scene Manager");
	mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	bool booleen;
	booleen = initMap();
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS **0*");
	if(booleen)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS **00*");
		booleen = initJoueur();
	}
	if(booleen)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
		createFrameListener();
		MoteurDeJeu* moteur = new MoteurDeJeu(mWindow,mRoot);
		booleen = moteur->boucle();
	}
    return booleen;
}

bool AppDemarrage::initMap()
{
	return true;
}

bool AppDemarrage::initJoueur()
{
	mCamera = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Ogre::Vector3(0,0,100));
	mCamera->lookAt(Ogre::Vector3(0,0,0));
	mCamera->setNearClipDistance(5);

	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

	Ogre::Entity *ent = mSceneMgr->createEntity("pinguin", "penguin.mesh");
	Ogre::SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	node->attachObject(ent);
	return true;
}

void AppDemarrage::createFrameListener()
{
    mInputListener = new InputListener(mWindow, mCamera);
    mRoot->addFrameListener(mInputListener);
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS **2");
}