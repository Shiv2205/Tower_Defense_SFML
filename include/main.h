#ifndef MAIN_H
#define MAIN_H

#include "Map/MapObserver.h"
#include "Map/Selector/Selector.h"
#include "Map/TileMap.h"
#include "Parser/Parser.h"
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#define SCREEN_W 1920U
#define SCREEN_H 1080U
#define UP       sf::Keyboard::Scan::Up
#define DOWN     sf::Keyboard::Scan::Down
#define LEFT     sf::Keyboard::Scan::Left
#define RIGHT    sf::Keyboard::Scan::Right
#define ENTER    sf::Keyboard::Scan::Enter

// Typedefs
enum GameState
{
  MAP_INIT,
  PATH_BUILDER,
  TOWER_OPS
};

// Prototypes
inline void event_handler( sf::RenderWindow& window, std::string& user_in );
inline void loadFont( sf::Font& font );
inline void loadTexture( sf::Texture& texture, std::string texture_path );
inline void keyboardListener( const sf::Event::KeyReleased* released_key, Selector& selector,
                              TileMap& my_map );
inline void buildPathHandler( const sf::Keyboard::Scancode& key_code, Map& my_map, const Position& new_pos );

// Constants
const std::string    font_path = "res/poppins.ttf";
const std::string    img_path  = "res/Maps/32x32/[A]_type1/Tile_1.png";
const std::nullptr_t num       = nullptr;

// Global variables
bool      reload       = true;
bool      draw_path    = false;
bool      is_entry_set = false;
bool      is_exit_set  = false;
GameState game_state   = PATH_BUILDER;

#endif // MAIN_H