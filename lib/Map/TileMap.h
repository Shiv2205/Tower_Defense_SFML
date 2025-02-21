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
  TileMap( void );

  TileMap( const Dimension& dimensions );

  ~TileMap( void );

  bool LoadScenery( void );

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