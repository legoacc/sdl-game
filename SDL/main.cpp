//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <string>
#include <array>
#include "base.hpp"
#include "ship.hpp"
#include "enemy.hpp"
#include "bullet.hpp"
#include "anim.hpp"
#include "enemymanager.hpp"

using namespace std;

//Screen dimension constants


SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
//Texture wrapper class


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Scene textures
LTexture bullet [2];
LTexture enemy;
LTexture ship [4];
LTexture blast[23];
string files [4] = {"ship64", "ship64move0", "ship64move1", "ship64move2"};

//Scene animations
Animation blastanim;

bool init()
{
    //Initialization flag
    bool success = true;
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }
        
        //Create window
        gWindow = SDL_CreateWindow( "Space Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create vsynced renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }
    
    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;
    
    //Load ship textures
    for (int i=0;i<sizeof(files)/sizeof(files[0]);i++) {
        ship[i].loadFromFile(files[i]+".png");
    }
    
    //Load bullet texture
    for (int i=0;i<sizeof(bullet)/sizeof(bullet[0]);i++) {
        if(!bullet[i].loadFromFile("bullet"+to_string(i)+".png")) printf ("bullet could not be loaded");
    }
    
    //Load other textures
    enemy.loadFromFile("enemy.png");
    for (int i=0;i<23;i++) {
        blast[i].loadFromFile("blast"+to_string(i)+".png");
    }
    
    //Set up animations
    blastanim.getFromArray(blast, "blast", 23);
    blastanim.betweenFrameCount = 3;
    
    
    return success;
}

void close()
{
    //Free loaded images
    for (int i=0;i<sizeof(files)/sizeof(files[0]);i++) {
        ship[i].free();
    }
    
    enemy.free();
    
    for (int i=0;i<sizeof(bullet)/sizeof(bullet[0]);i++) {
        bullet[i].free();
    }
    
    for (int i=0;i<23;i++) {
        blast[i].free();
    }
    
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

void beforeStartGame() {
    
}

void startGame() {
    
}

int main( int argc, char* args[] )
{
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {	
            //Main loop flag
            bool quit = false;
            
            //Event handler
            SDL_Event e;
            
            //The dot that will be moving around on the screen
            Ship ship;
            
            EnemyManager::createEnemy (400, 20);
            EnemyManager::createEnemy (SCREEN_WIDTH/3, SCREEN_HEIGHT/2);
            
            bool alive2 = true;
            
            //While application is running
            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    
                    //Handle input for the dot
                    if (alive2) ship.handleEvent( e);

                }
                
                //Move the dot
                ship.move();
                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 50, 50, 50, 255 );
                SDL_RenderClear( gRenderer );
                EnemyManager::renderEnemies(ship.mPosX, ship.mPosY, ship.bullets);
                ship.render(EnemyManager::allbullets);
                AnimationManager::playFrames();
                
                //Update screen
                SDL_RenderPresent( gRenderer );
            }
        }
    }
    
    //Free resources and close SDL
    close();
    
    return 0;
}