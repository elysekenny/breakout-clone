
#ifndef BREAKOUT_GAMEOBJECT_H
#define BREAKOUT_GAMEOBJECT_H

#include "Vector2.h"
#include <SFML/Graphics.hpp>

class GameObject
{
 public:
  GameObject();
  ~GameObject();

  bool initialiseSprite(sf::Texture &texture, std::string filename);
  sf::Sprite* getSprite();
  void setVisibility(bool);
  bool getVisibility();
  bool ballMovement(float, float, int, int);

 private:
  sf::Sprite* sprite = nullptr;
  Vector2* vector = new Vector2(2,5);

  bool is_visible;
};


#endif // BREAKOUT_GAMEOBJECT_H
