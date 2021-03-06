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
	if(booleen)
	{
		booleen = initJoueur();
	}
	if(booleen)
	{
		createFrameListener();
		MoteurDeJeu* moteur = new MoteurDeJeu(mWindow,mRoot);
		booleen = moteur->boucle();
	}
    return booleen;
}

bool AppDemarrage::initMap()
{
	DotSceneLoader loader;
	loader.parseDotScene("map.scene","General", mSceneMgr);
	Ogre::Vector3 lightdir(0.0f, -0.5f, 1.0f);
	Ogre::Light* mLight;
	mLight = mSceneMgr->createLight("terrainLight");
	mLight->setType(Ogre::Light::LT_DIRECTIONAL);
	mLight->setDirection(lightdir);
	mLight->setDiffuseColour(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	return true;
}

bool AppDemarrage::initJoueur()
{
	mCamera = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Ogre::Vector3(0,100,-100));
	mCamera->lookAt(Ogre::Vector3(0,0,0));
	mCamera->setNearClipDistance(5);

	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

	return true;
}

void AppDemarrage::createFrameListener()
{
    mInputListener = new InputListener(mWindow, mCamera);
    mRoot->addFrameListener(mInputListener);
}