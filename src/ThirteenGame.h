#ifndef ThirteenGame_H_
#define ThirteenGame_H_

#include "gameplay.h"

using namespace gameplay;

/**
 * Main game class.
 */
class ThirteenGame: public Game, Control::Listener
{
public:

    /**
     * Constructor.
     */
    ThirteenGame();

    /**
     * @see Game::keyEvent
     */
	void keyEvent(Keyboard::KeyEvent evt, int key);
	
    /**
     * @see Game::touchEvent
     */
    void touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex);
    
protected:

    /**
     * @see Game::initialize
     */
    void initialize();

    /**
     * @see Game::finalize
     */
    void finalize();

    /**
     * @see Game::update
     */
    void update(float elapsedTime);

    /**
     * @see Game::render
     */
    void render(float elapsedTime);

    /**
    * @see Control::Listener
    */
    void controlEvent(Control* control, EventType evt);

private:

    /**
     * Draws the scene each frame.
     */
    bool drawScene(Node* node);

    Form* _mainMenuForm;
    Scene* _scene;
    bool _wireframe;
};

#endif
