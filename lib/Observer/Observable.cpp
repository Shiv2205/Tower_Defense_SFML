#include "Observable.h"

void Observable::addObserver( const Observer* observer )
{
  this->observers.push_back( observer );
}

void Observable::removeObserver( const Observer* observer )
{
}

void Observable::notify( void )
{
  auto begin = this->observers.begin();
  auto end   = this->observers.end();

  for ( int i = 0; i < this->observers.size(); i++ )
  {
    this->observers.at(i)->update(this);
  }
}