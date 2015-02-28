#include "ThirteenGame.h"

// Declare our game instance
ThirteenGame game;

ThirteenGame::ThirteenGame()
    : _scene(NULL), _wireframe(false)
{
}

void ThirteenGame::initialize()
{
    _mainMenuForm = Form::create("res/forms/mainMenu.form");
    
    Button* playGameButton = static_cast<Button*>(_mainMenuForm->getControl("playGameButton"));
    playGameButton->addListener(this, Control::Listener::PRESS | Control::Listener::RELEASE);
    // Load game scene from file
    _scene = Scene::load("res/demo.scene");

    // Get the box model and initialize its material parameter values and bindings
    Node* boxNode = _scene->findNode("box");
    Model* boxModel = dynamic_cast<Model*>(boxNode->getDrawable());
    Material* boxMaterial = boxModel->getMaterial();

    // Set the aspect ratio for the scene's camera to match the current resolution
    _scene->getActiveCamera()->setAspectRatio(getAspectRatio());
}

void ThirteenGame::finalize()
{
    SAFE_RELEASE(_scene);
}

void ThirteenGame::update(float elapsedTime)
{
    // Rotate model
    _scene->findNode("box")->rotateY(MATH_DEG_TO_RAD((float)elapsedTime / 1000.0f * 180.0f));
}

void ThirteenGame::render(float elapsedTime)
{
    // Clear the color and depth buffers
    clear(CLEAR_COLOR_DEPTH, Vector4::zero(), 1.0f, 0);

    // Visit all the nodes in the scene for drawing
    _scene->visit(this, &ThirteenGame::drawScene);
    
    _mainMenuForm->draw();
}

bool ThirteenGame::drawScene(Node* node)
{
    // If the node visited contains a drawable object, draw it
    Drawable* drawable = node->getDrawable(); 
    if (drawable)
        drawable->draw(_wireframe);

    return true;
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
        _wireframe = !_wireframe;
        break;
    case Touch::TOUCH_RELEASE:
        break;
    case Touch::TOUCH_MOVE:
        break;
    };
}
