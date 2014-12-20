//
// breakout.c
//
// Fanney Zhu
// fanneyzhu@college.harvard.edu
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// height and width of paddle
#define HEIGHTPADDLE 10
#define WIDTHPADDLE 60

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// height and width of brick
#define HEIGHTBRICK 10
#define WIDTHBRICK 30

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);
    
    // randomize x velocity of ball
    double xvelocity = drand48()/50 + 0.05;
    double yvelocity = 0.1;

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    while (lives > 0 && bricks > 0)
    {
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        // if we heard one
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {   
                // ensure paddle follows mouse
                double x = getX(event) - WIDTHPADDLE/2;
        
                // makes sure paddle stays within screen
                if (x >= 0 || x <= WIDTH)
                {
                    setLocation(paddle, x, 9*HEIGHT/10);
                }
                if (x < 0)
                {
                    setLocation(paddle, 0, 9*HEIGHT/10);
                }
                if (x > WIDTH - WIDTHPADDLE) 
                {
                    setLocation(paddle, WIDTH - WIDTHPADDLE, 9*HEIGHT/10);
                }
             }
         }
        
        // compels ball to move
        move(ball, xvelocity, yvelocity);
                
        // bounce off edge of window
        if (getX(ball) + getWidth(ball) >= WIDTH || getX(ball) <= 0)
        {
            xvelocity = -xvelocity;
        }
        
        // bouce off top edge of window
        if (getY(ball) <= 0)
        {
            yvelocity = -yvelocity;
        }
        
        // detect collision
        GObject object = detectCollision(window, ball);
        
       
        // bounce off paddle
        if (object == paddle)
        {
            yvelocity = -yvelocity;
        }

        // bounce off brick
        else if (object != NULL)
        {
            if (strcmp(getType(object), "GRect") == 0)
            {
                yvelocity = -yvelocity;
                bricks--;
                removeGWindow(window, object);
                points++;
            }
        }

        // update scoreboard
        updateScoreboard(window, label, points);
        
        // ball at bottom edge of window
        if (getY(ball) + 2*RADIUS >= HEIGHT)
        {
            lives--;
            if (lives >= 1)
            {
                waitForClick();
            }    
            setLocation(ball, WIDTH/2 - RADIUS, HEIGHT/2 - RADIUS);
        }
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // y position of top left brick
    double y = HEIGHT/12;
    
    // instantiate bricks
    for (int i = 0; i < ROWS; i++)
    {
        double x = 5;
        for (int j = 0; j < COLS; j++)
        {
            GRect bricks = newGRect(x, y, WIDTHBRICK, HEIGHTBRICK);
            
            // magenta bricks in top row, light gray bricks in all others
            if (i/2.0 == 0)
            {
                setColor(bricks, "MAGENTA");
                setFilled(bricks, true);
            }
            else
            {
                setColor(bricks, "LIGHT_GRAY");
                setFilled(bricks, true);
            }
            
            // add brick to window
            add(window, bricks);
            
            // space between adjacent bricks
            x += WIDTHBRICK + 10;
        }
        
        // space between rows of bricks
        y += HEIGHTBRICK + 10;
    }
    return;
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // instantiate blue ball
    GOval ball = newGOval(WIDTH/2 - RADIUS, HEIGHT/2 - RADIUS, 2*RADIUS, 2*RADIUS);
    setColor(ball, "BLUE");
    setFilled(ball, true);
    
    // add ball to window
    add(window, ball);
    
    // return ball
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // instantiate red paddle
    GRect paddle = newGRect(WIDTH/2 - WIDTHPADDLE/2, 9*HEIGHT/10, WIDTHPADDLE, HEIGHTPADDLE);
    setColor(paddle, "RED");
    setFilled(paddle, true);
    
    // add paddle to window
    add(window, paddle);
    
    // return paddle
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // instantiate label
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-36");
    
    // add label to window
    add(window, label);
    
    // return label
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
