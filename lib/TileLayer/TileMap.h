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
#include "TileLayer.h"
#include "Util/Sfml_Util.h"
#include <string>

#define SCENERY_TEXTURE std::string( "res/Maps/32x32/[A]_type1/Tile_1.png" )
#define SCENE_TEX_POS   Vec_2i( { 0, 128 } )
#define SCENE_TEX_SIZE  Vec_2i( { 32, 32 } )

// Forward declaration
class TilePath;
class TileTowers;
class TileCritters;

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

  /**
   * @brief Load the Tile Map object
   *
   * @return true
   * @return false
   */
  bool Load( void ) override;

  TilePath*     getPathLayer( void ) { return this->path_layer_ptr; }
  TileTowers*   getTowerLayer( void ) { return this->tower_layer_ptr; }
  TileCritters* getCritterLayer( void ) { return this->critter_layer_ptr; }

  void setPathLayer( TilePath* path_layer_ptr ) { this->path_layer_ptr = path_layer_ptr; }
  void setTowerLayer( TileTowers* tower_layer_ptr ) { this->tower_layer_ptr = tower_layer_ptr; }
  void setCritterLayer( TileCritters* critter_layer_ptr ) { this->critter_layer_ptr = critter_layer_ptr; }

private:
  TilePath*     path_layer_ptr;
  TileTowers*   tower_layer_ptr;
  TileCritters* critter_layer_ptr;
};

#endif // TILEMAP_H