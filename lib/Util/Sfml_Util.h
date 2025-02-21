#ifndef SFML_UTIL_H
#define SFML_UTIL_H

#include "Map/Cell/Cell.h"
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>


//Typedefs and Aliases
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
void InitVertices( sf::Vertex* cell_vts, const Position& cell_pos );

#endif // SFML_UTIL_H