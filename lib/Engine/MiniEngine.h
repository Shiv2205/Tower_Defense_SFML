#ifndef MINIENGINE_H
#define MINIENGINE_H

#include "Factory/TileLayerFactory.h"
#include "Map/MapObserver.h"
#include "Map/Selector/Selector.h"
#include "Registry/TileLayerRegistry.h"
#include "TileLayer/TileCritters.h"
#include "TileLayer/TileMap.h"
#include "TileLayer/TilePath.h"
#include "TileLayer/TileTowers.h"
#include "Tower/ElectricTower.h"
#include "Tower/IceTower.h"
#include "Tower/PoisonTower.h"
#include "Util/Sfml_Util.h"
#include "Window/Window.h"

#define UP           sf::Keyboard::Scan::Up
#define DOWN         sf::Keyboard::Scan::Down
#define LEFT         sf::Keyboard::Scan::Left
#define RIGHT        sf::Keyboard::Scan::Right
#define ENTER        sf::Keyboard::Scan::Enter
#define VALIDATE_MAP sf::Keyboard::Scan::V
#define ICE          sf::Keyboard::Scan::I
#define POISON       sf::Keyboard::Scan::P
#define ELECTRIC     sf::Keyboard::Scan::E

// Typedefs
enum GameState
{
  PATH_BUILDER,
  TOWER_OPS,
  VALIDATE,
  TEST_CRITTERS
};

// Constants
const std::string font_path = "res/poppins.ttf";
const std::string img_path  = "res/Maps/32x32/[A]_type1/Tile_1.png";

// Global variables
extern bool      reload;
extern bool      draw_path;
extern bool      is_entry_set;
extern bool      is_exit_set;
extern bool      validate_map;
extern GameState game_state;

namespace Engine
{
// Game Window
extern Window game_window;

// Text
extern sf::Font font;
extern sf::Text my_text;

// Subjects
extern TileMap my_map;

// Observers
extern MapObserver map_obs;

// Cell Selector
extern Selector selector;

// Set Map dimensions
extern Dimension map_dim;

void        gameInit( void );
void        gameLoop( void );
inline void loadFont( sf::Font& font );
inline void keyboardListener( const sf::Event::KeyReleased* released_key );
inline void mapCreatorTck( const sf::Keyboard::Scancode& key_code );
inline void buildPathHandler( const sf::Keyboard::Scancode& key_code );
inline void addTowerHandler( const sf::Keyboard::Scancode& key_code );
inline void movementHandler( const sf::Keyboard::Scancode& key_code );
inline void gameFlowTck( void );
}; // namespace Engine

#endif // MINIENGINE_H