
#ifndef BREAKOUT_GAME_H
#define BREAKOUT_GAME_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "GameObject.h"

class Game
{
 public:
  Game(sf::RenderWindow& game_window);
  ~Game();
  bool initMenu();
  bool initGameOver();
  bool initLives();
  bool initScore();
  bool init();
  bool initBlocks();
  bool initGems();
  void spawnGems(float);
  bool checkIfLoseLive();
  bool checkForBlocks();
  bool checkForGems();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);

  //collision functions - will return 0 for no collision, 1 for x and 2 for y
  int collision_check();
  int block_collision_check();

  bool gem_collision_check(bool ball_respawn);

 private:
  //constants for the 2d array of blocks
  static const int cols = 10;
  static const int rows = 7;

  sf::RenderWindow& window;

  //start screen set up
  sf::Font font;
  sf::Text start_screen;
  sf::Text live_counter;
  sf::Text respawn_ball_text;
  sf::Text game_over;
  sf::Text score_text;

  //textures
  sf::Texture paddle_texture;
  sf::Texture ball_texture;
  sf::Texture* block_texture;
  sf::Texture* gem_texture;

  //object declaration
  GameObject paddle;
  GameObject ball;
  GameObject blocks[cols][rows];
  GameObject gems[3];

  // 0 = menu, 1 = game, 2 = game over
  int game_state = 0;

  //paddle is initially stationary, will become -1 or 1 depending on which key is pressed
  float paddle_direction = 0;
  const float paddle_speed = 500;
  const float ball_speed = 400;

  //collision variables 1 for x and 2 for y (0 for no collision)
  int collision_axis;
  int block_collider;

  //game over conditions and variables
  int health = 5;
  bool respawn_ball = false;
  bool player_has_won;
  int score = 0;

  //gem variables
  int gem_spawn;
  bool gem_on_screen = false;
  float gem_speed = 1;
};

#endif // BREAKOUT_GAME_H
