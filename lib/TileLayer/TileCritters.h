#ifndef TILECRITTERS_H
#define TILECRITTERS_H

#include "Critters/CrittersGroup.h"
#include "TileLayer.h"
#include "Util/Sfml_Util.h"
#include <string>

#define CRITTER_TEXTURE  std::string( "res/Custom/Enemy 15-" )
#define CRITTER_TEX_POS  Vec_2i( { 0, 0 } )
#define CRITTER_TEX_SIZE Vec_2i( { 32, 32 } )

class TileCritters : public CritterGroup, public TileLayer
{
public:
  TileCritters( void );

  ~TileCritters( void );

  bool Load( void ) override;

  void WaveInit( void );
  void WaveMove( void );

  void InitCritterPos( int critter_idx );
  void MoveCritter( sf::Vertex* critter_vts, int critter_idx );

  const std::string getCritterTexPath( void ) const;

private:
  void CalculateOffset( int& offset_x, int& offset_y ) const;
  void CalculateIncrement( const Position& curr_pos, const Position& next_pos, Vec_2f& increment ) const;

  bool IsCritterOnCell( const Vec_2f& vertex_pos, const Position& cell_pos ) const
  {
    return ( (int)vertex_pos.x == cell_pos.col * this->getTileSize().x ) &&
           ( (int)vertex_pos.y == cell_pos.row * this->getTileSize().y );
  }
};

#endif // TILECRITTERS_H