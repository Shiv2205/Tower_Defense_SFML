#ifndef SFML_UTIL_H
#define SFML_UTIL_H

#include "Util.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>

#define SCREEN_W 1920U
#define SCREEN_H 1080U

// Tower Names
#define ICE_TOWER    std::string( "IceTower" )
#define POISON_TOWER std::string( "PoisonTower" )
#define ELEC_TOWER   std::string( "ElectricTower" )

// Typedefs and Aliases
using Vec_2f = sf::Vector2f;
using Vec_2i = sf::Vector2i;
using Vec_2u = sf::Vector2u;

/**
 * @brief Helps initialise a vertex array at a given `Position`
 * The Vertex array should have primitive type Triangles and be
 * made up of 2 Triangles, forming a square
 * @param cell_vertices
 * @param cell_pos
 */
void InitVertices( sf::Vertex* cell_vts, const Position& cell_pos, Vec_2u coord = { 0, 0 } );

void loadFont( sf::Font& font, const std::string& font_path );
void loadTexture( sf::Texture& texture, const std::string& texture_path );

#endif // SFML_UTIL_H