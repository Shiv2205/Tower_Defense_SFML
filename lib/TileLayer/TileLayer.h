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

  sf::Vertex*        getLayerVertex( const u_32 index );
  const sf::Texture& getLayerTexture( void ) const;
  bool               isLayerTexLoaded( void ) const;
  const std::string& getLayerTexPath( void ) const;
  static u_32        getNumVertices( void );

  void        setLayerVertices( const sf::VertexArray& layer_vertices );
  void        setLayerTexture( const sf::Texture& layer_texture );
  void        setLayerTexPath( const std::string& layer_tex_path );
  static void setNumVertices( const u_32& num_vertices );

  virtual bool Load( void );
  virtual void RegisterTile(const u_32& vertex_idx, const Position& target_tile, const std::string& tile_type="");

private:
  void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
  bool LoadTexture( void );

  sf::VertexArray layer_vertices;
  sf::Texture     layer_texture;
  std::string     layer_tex_path;
  bool            layer_tex_loaded;
  Vec_2i          tile_pos;
  Vec_2i          tile_size;

  static u_32 num_vertices;
};

#endif // TILELAYER_H