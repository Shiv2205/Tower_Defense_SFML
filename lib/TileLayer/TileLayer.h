#ifndef TILELAYER_H
#define TILELAYER_H

#include "Util/Sfml_Util.h"
#include <string>

class TileLayer : public sf::Drawable, public sf::Transformable
{
public:
  TileLayer( void );
  TileLayer( const std::string& tex_path, const Vec_2i& tile_pos, const Vec_2i& tile_size );

  virtual ~TileLayer( void );

  sf::Vertex*        getLayerVertex( const u_32 index ) { return &this->layer_vertices[ index ]; }
  const sf::Texture& getLayerTexture( void ) const { return this->layer_texture; }
  bool               isLayerTexLoaded( void ) const { return this->layer_tex_loaded; }
  const std::string& getLayerTexPath( void ) const { return this->layer_tex_path; }
  const Vec_2i&      getTileSize( void ) const { return this->tile_size; }
  const Vec_2i&      getTilePos( void ) const { return this->tile_pos; }
  static Vec_2u      getBoundaries( void ) { return TileLayer::boundaries; }

  void        setLayerVertices( const sf::VertexArray& layer_vertices ) { this->layer_vertices = layer_vertices; }
  void        setLayerTexture( const sf::Texture& layer_texture ) { this->layer_texture = layer_texture; }
  void        setLayerTexPath( const std::string& layer_tex_path ) { this->layer_tex_path = layer_tex_path; }
  void        setTileSize( const Vec_2i& tile_size ) { this->tile_size = tile_size; }
  void        setTilePos( const Vec_2i& tile_pos ) { this->tile_pos = tile_pos; }
  static void setBoundaries( const Vec_2u& boundaries ) { TileLayer::boundaries = boundaries; }

  virtual bool Load( void );
  virtual void RegisterTile( const u_32& vertex_idx, const Position& target_tile, const std::string& tile_type = "" );

private:
  void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
  bool LoadTexture( void );

  sf::VertexArray layer_vertices;
  sf::Texture     layer_texture;
  std::string     layer_tex_path;
  bool            layer_tex_loaded;
  Vec_2i          tile_pos;
  Vec_2i          tile_size;

  static Vec_2u boundaries;
};

#endif // TILELAYER_H