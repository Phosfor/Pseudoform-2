#include "Core/GameApplication.hpp"

GameApplication::GameApplication()
{
    mSystemsList.push_back(new GraphicSystem());
    mSystemsList.push_back(new InputSystem());
    mSystemsList.push_back(new GuiSystem());
    mSystemsList.push_back(new ScriptSystem());

    mRunning = false;

    mAccumulator = mElapsed = mFrameRate = 0.0f;
    mDrawn = false;
    mDt = 1.f / 60.f;

    this->_init();

    CONNECT2(Events::ClosingEvent, "WindowClosing", &GameApplication::WindowClosing);
}

GameApplication::~GameApplication() { }

void GameApplication::setGameState(bool running) { mRunning = running; }
const float GameApplication::getElapsed() const { return mElapsed; }
float GameApplication::getFPS() { return floor(mFrameRate+0.5); }

void GameApplication::_init()
{
	LOG_NOFORMAT("Systems initialization:\n=======================\n\n");
	utils.writeTimestamp();

    BOOST_FOREACH(ISystem &curSystem, mSystemsList)
    {
        LOG(FORMAT("--------------- Start initialization of `%1%` system", curSystem.toString()));
        curSystem.init();
        LOG(FORMAT("--------------- Initialization of `%1%` is finished\n", curSystem.toString()));
    }

    LOG_NOFORMAT("Finished in: [" + utils.getTimeDifference() + "]\n\n");
	LOG_NOFORMAT("Game initialization:\n====================\n\n");
	utils.writeTimestamp();
}

void GameApplication::Start()
{
    mRunning = true;

    utils.setMediaPath(CONFIG("resources.MediaFolder", string, "Media"));

    SIGNAL(Engine::Events::GlobalInitEvent, "Inited", );

    LOG_NOFORMAT("\nFinished in: [" + utils.getTimeDifference() + "]\n");
	LOG_NOFORMAT("\nGame Loop:\n==========\n\n");
	utils.writeTimestamp();

    this->_loop();
}

void GameApplication::_loop()
{
    while(mRunning)
    {
        Ogre::WindowEventUtilities::messagePump();

        mElapsed = mClock.GetElapsedTime();
        mAccumulator += mElapsed;
        mClock.Reset();

        mFrameRate = 1.f / mElapsed;

        while (mAccumulator >= mDt)
        {
            BOOST_FOREACH(ISystem &curSystem, mSystemsList)
            {
                curSystem.update(mElapsed);
            }
            SIGNAL(Engine::Events::GlobalUpdateEvent, "Updated", );
            stateManager.update();

            mAccumulator -= mDt;
            mDrawn = false;
        }

        if (mDrawn)
        {
            sf::Sleep(mDt);
        }
        else
        {
            if (!graphicSystem.getRoot()->renderOneFrame())
                LOG("Something bad happened in the render cycle!");

            mDrawn = true;
        }
    }

    this->_shutdown();
}

void GameApplication::_shutdown()
{
    LOG_NOFORMAT("\nFinished in: [" + utils.getTimeDifference() + "]\n");
    mSystemsList.clear();
}

void GameApplication::WindowClosing(Ogre::RenderWindow *rw, bool &shouldClose)
{
    if(shouldClose){
        LOG("Clicked on [X] -> closing");
        mRunning = false;
    }
}
