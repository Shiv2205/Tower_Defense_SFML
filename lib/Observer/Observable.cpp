#include "Observable.h"
#include "Observer.h"

void Observable::addObserver( const Observer* observer )
{
  this->observers.push_back( observer );
}

void Observable::removeObserver( const Observer* observer )
{
  auto begin = this->observers.begin();

  for ( int i = 0; i < this->observers.size(); i++ )
  {
    if ( observer == this->observers.at( i ) )
    {
      this->observers.erase( begin + i );
    }
  }
}

void Observable::notify( void )
{
  for ( const Observer* observer : this->observers )
  {
    observer->update( this );
  }
}