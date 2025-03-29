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

#include "Map/Map.h"
#include "Registry/TileLayerRegistry.h"
#include "TileLayer.h"
#include "Util/Sfml_Util.h"
#include <string>

#define SCENERY_TEXTURE std::string( "res/Maps/32x32/[A]_type1/Tile_1.png" )
#define SCENE_TEX_POS   Vec_2i( { 0, 128 } )
#define SCENE_TEX_SIZE  Vec_2i( { 32, 32 } )

// Forward declaration

class TileMap : public Map, public TileLayer
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

  TileLayerRegistry* const getLayerReg( void ) const { return (TileLayerRegistry* const)&this->layer_reg; }

  /**
   * @brief Load the Tile Map object
   *
   * @return true
   * @return false
   */
  bool Load( void ) override;

private:
  TileLayerRegistry layer_reg;
};

#endif // TILEMAP_H