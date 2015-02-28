#include "ThirteenGame.h"

// Declare our game instance
ThirteenGame game;

ThirteenGame::ThirteenGame()
{
}

void ThirteenGame::initialize()
{
    // Create your sprite batch from a PNG image
    _batch = SpriteBatch::create("res/img/cards.png");
}

void ThirteenGame::finalize()
{
    SAFE_DELETE(_batch);
}

void ThirteenGame::update(float elapsedTime)
{

}

void ThirteenGame::render(float elapsedTime)
{
    // Clear the color and depth buffers
    clear(CLEAR_COLOR_DEPTH, Vector4::zero(), 1.0f, 0);
    
    // Draw your sprites
    _batch->start();
    _batch->draw(Rectangle(0, 0, 160, 220),
                 Rectangle(0, 0, 160, 220), Vector4(1.0,1.0,1.0,1.0));
    // SpriteBatch::draw() can be called multiple times between start() and finish()
    _batch->finish();
}

void ThirteenGame::controlEvent(gameplay::Control *control, gameplay::Control::Listener::EventType evt)
{
    switch(evt)
    {
        case Control::Listener::RELEASE:
            if( strcmp("playGameButton", control->getId()) == 0)
            {
                printf("Clicked play game button.\n");
            }
            break;
        default:
            break;
    }
    
}

void ThirteenGame::keyEvent(Keyboard::KeyEvent evt, int key)
{
    if (evt == Keyboard::KEY_PRESS)
    {
        switch (key)
        {
        case Keyboard::KEY_ESCAPE:
            exit();
            break;
        }
    }
}

void ThirteenGame::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex)
{
    switch (evt)
    {
    case Touch::TOUCH_PRESS:
        break;
    case Touch::TOUCH_RELEASE:
        break;
    case Touch::TOUCH_MOVE:
        break;
    };
}
