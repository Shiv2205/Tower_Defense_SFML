/**
 * @file TileMap.h
 * @author Shivam Veerabudren
 * @brief Tilemap includes SFML graphics functionality to Map class
 * @version 0.1
 * @date 2025-03-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef TILEMAP_H
#define TILEMAP_H

#include "Map.h"
#include "Util/Sfml_Util.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#define SCENERY_TEXTURE "res/Maps/32x32/[A]_type1/Tile_1.png"
#define PATH_TEXTURE    "res/Maps/32x32/[A]_type1/Tile_4.png"

class TileMap : public Map, public sf::Drawable, public sf::Transformable
{
public:
  /**
   * @brief Construct a new Tile Map object
   * 
   */
  TileMap( void );

  /**
   * @brief Construct a new Tile Map object
   * 
   * @param dimensions Dimensions of the tile map
   */
  TileMap( const Dimension& dimensions );

  /**
   * @brief Destroy the Tile Map object
   * 
   */
  ~TileMap( void );

  /**
   * @brief Load the Tile Map object
   * 
   * @return true 
   * @return false 
   */
  bool Load( void );

private:

  void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

  bool LoadSceneryTexture( void );
  
  bool LoadPathTexture( void );

  sf::VertexArray scene_vertices;
  sf::VertexArray path_vertices;
  sf::VertexArray tower_vertices;

  sf::Texture scene_texture;
  sf::Texture path_texture;
  sf::Texture tower_texture;

  bool scene_tex_loaded;
  bool path_tex_loaded;
};

#endif // TILEMAP_H