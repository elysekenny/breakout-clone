#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{
  sprite = new sf::Sprite;
}

GameObject::~GameObject()
{

}

bool GameObject::initialiseSprite(sf::Texture &texture, std::string filename)
{
    if(!texture.loadFromFile(filename))
    {
      std::cout << "sprite texture cannot be loaded";
      return false;
    }

    if(sprite != nullptr)
    {
      sprite->setTexture(texture);
      sprite->setScale(1,1);
    }

    return true;
}

sf::Sprite* GameObject::getSprite()
{
  return sprite;
}

void GameObject::setVisibility(bool visibility)
{
  is_visible = visibility;
}

bool GameObject::getVisibility()
{
  return is_visible;
}

bool GameObject::ballMovement(float dt, float ball_speed, int collision, int block_collision)
{
  if(collision == 1 || block_collision == 1)
  {
    vector->x *= -1;
  }
  else if(collision == 2 || block_collision == 2)
  {
    vector->y *= -1;
  }

  vector->normalise();
  sprite->move(vector->x * dt * ball_speed, vector->y * dt * ball_speed);

  return true;
}