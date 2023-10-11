
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window): window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::initMenu()
{
  if(!font.loadFromFile("Data/Fonts/open-sans/OpenSans-ExtraBold.ttf"))
  {
    std::cout << "an error has occurred whilst trying to load the font\n";
  }

  start_screen.setString("--------PRESS ENTER TO PLAY--------");
  start_screen.setFont(font);
  start_screen.setCharacterSize(70);
  start_screen.setFillColor(sf::Color(255,255,255,255));
  start_screen.setPosition(
    window.getSize().x /2 - start_screen.getGlobalBounds().width /2,250);

  return true;
}

bool Game::initGameOver()
{
  if(!font.loadFromFile("Data/Fonts/open-sans/OpenSans-ExtraBold.ttf"))
  {
    std::cout << "an error has occurred whilst trying to load the font\n";
  }

  game_over.setString("GAME OVER YOU LOSE! \n[ENTER] to play again \n [ESC] to quit");
  game_over.setFont(font);
  game_over.setCharacterSize(70);
  game_over.setFillColor(sf::Color(255,0,0,255));
  game_over.setPosition(
    window.getSize().x /2 - game_over.getGlobalBounds().width /2,250);

  return true;
}

bool Game::initLives()
{
  if(!font.loadFromFile("Data/Fonts/open-sans/OpenSans-ExtraBold.ttf"))
  {
    std::cout << "an error has occurred whilst trying to load the font\n";
  }

  live_counter.setString("PLAYER LIVES: 5");
  live_counter.setFont(font);
  live_counter.setCharacterSize(25);
  live_counter.setPosition(35,50);
  live_counter.setFillColor(sf::Color(255,255,255,255));

  respawn_ball_text.setString("USE -SPACE- TO RELEASE THE BALL");
  respawn_ball_text.setFont(font);
  respawn_ball_text.setCharacterSize(35);
  respawn_ball_text.setPosition(window.getSize().x / 2 - respawn_ball_text.getGlobalBounds().width/2,580);
  respawn_ball_text.setFillColor(sf::Color(255,255,255,100));

  return true;
}
bool Game::initScore()
{
  if (!font.loadFromFile("Data/Fonts/open-sans/OpenSans-ExtraBold.ttf"))
  {
    std::cout << "an error has occurred whilst trying to load the font\n";
  }

  score_text.setString("SCORE: 0");
  score_text.setFont(font);
  score_text.setCharacterSize(25);
  score_text.setPosition(900, 50);
  score_text.setFillColor(sf::Color(255, 255, 255, 255));

  return true;
}

bool Game::initBlocks()
{
  std::string colours[] = {"element_red_rectangle_glossy.png",
                            "element_yellow_rectangle_glossy.png",
                            "element_yellow_rectangle.png",
                            "element_green_rectangle_glossy.png",
                            "element_green_rectangle.png",
                            "element_blue_rectangle_glossy.png",
                            "element_purple_rectangle_glossy.png",
                            "element_purple_rectangle.png"};

  for(int i = 0; i < cols; i++)
  {
    for (int j = 0; j < rows; j++)
    {
      block_texture = new sf::Texture;
      blocks[i][j].initialiseSprite(*block_texture, "Data/Images/" + colours[j]);
      blocks[i][j].setVisibility(true);

      if (j % 2 == 0)
      {
        blocks[i][j].getSprite()->setPosition(
          85 * (i + 1.5), 40 * (j + 2));
      }
      else
      {
        blocks[i][j].getSprite()->setPosition(
          85 * (i + 2), 40 * (j + 2));
      }
    }
  }

  return true;
}

bool Game::initGems()
{

  std::string shapes[] = {"element_yellow_diamond.png",
                            "element_grey_diamond.png"};

  for(int i = 0; i < 2; i++)
  {
    gem_texture = new sf::Texture;
    gems[i].initialiseSprite(*gem_texture,"Data/Images/" + shapes[i]);
    gems[i].setVisibility(true);
    //hide initial gems off the screen
    gems[i].getSprite()->setPosition(0,-100);
  }

  return true;
}

void Game::spawnGems(float speed)
{
  for(int i = 0; i < 2; i++)
  {


    gems[i].getSprite()->move(0, speed);
  }
}

bool Game::init()
{
  initMenu();
  initLives();
  initScore();
  initBlocks();
  initGameOver();
  initGems();

  paddle.initialiseSprite(paddle_texture,"Data/Images/paddleBlue.png");
  paddle.getSprite()->setPosition(
    window.getSize().x / 2 - paddle.getSprite()->getGlobalBounds().width / 2,
    window.getSize().y - 50);

  ball.initialiseSprite(ball_texture, "Data/Images/ballGrey.png");
  ball.getSprite()->setPosition(
    window.getSize().x / 2 - ball.getSprite()->getGlobalBounds().width / 2,
    window.getSize().y - 200);

  return true;
}

void Game::update(float dt)
{
  switch(game_state)
  {
    case 0:
      break;

    case 1:
      //random chance to spawn gems
      if(gem_on_screen && !respawn_ball)
      {
        spawnGems(gem_speed);
        gem_collision_check(respawn_ball);
        //code is greyed out but does work
        if(!checkForGems())
        {
          //there are no gems visible so more can be spawned
          gem_on_screen = false;
          for(int i = 0; i < 2; i++)
          {
            gems[i].setVisibility(true);
          }
        }

      }
      else
      {
        gem_spawn = std::rand() % 100;
        switch(gem_spawn)
        {
          case 1:
            gem_on_screen = true;
            for(int i = 0; i < 2; i++)
            {
              float random_x = std::rand() % window.getSize().x -50;
              gem_speed = std::rand() %6 + 1;
              gems[i].getSprite()->setPosition(random_x, -100);
            }
            break;
        }
      }

      //paddle movement
      paddle.getSprite()->move(paddle_speed * dt * paddle_direction,0);

      //paddle boundary check to loop it to the other side of the screen
      if(paddle.getSprite()->getPosition().x + paddle.getSprite()->getGlobalBounds().width <= 0)
      {
        paddle.getSprite()->setPosition(window.getSize().x, window.getSize().y - 50);
      }
      else if(paddle.getSprite()->getPosition().x>= window.getSize().x - 1)
      {
        paddle.getSprite()->setPosition(0, window.getSize().y - 50);
      }
      //ball movement and collision check
      if(respawn_ball)
      {
        ball.ballMovement(dt, 0, collision_axis, block_collider);
      }
      else
      {
        respawn_ball = checkIfLoseLive();
        collision_axis = collision_check();
        block_collider = block_collision_check();
        ball.ballMovement(dt, ball_speed, collision_axis, block_collider);
      }

      if(health <= 0)
      {
        //trigger game over
        game_state = 2;
        player_has_won = false;
      }

      //it may be greyed out but it works trust me
      if(!checkForBlocks())
      {
        //there are no blocks visible and therefore the player has won
        game_state = 2;
        player_has_won = true;
      }
      break;
  }
}

void Game::render()
{
  switch(game_state)
  {
    case 0:
      window.draw(start_screen);
      break;

    case 1:
      window.draw(*paddle.getSprite());
      window.draw(*ball.getSprite());
      window.draw(live_counter);
      window.draw(score_text);
      for(int i = 0; i < cols; i++)
      {
        for(int j = 0; j < rows; j++)
        {
          if(blocks[i][j].getVisibility())
          {
            window.draw(*blocks[i][j].getSprite());
          }
        }
      }

      for(int i = 0; i < 2; i++)
      {
        if(gems[i].getVisibility())
        {
          window.draw(*gems[i].getSprite());
        }
      }

      if(respawn_ball)
      {
        window.draw(respawn_ball_text);
      }
      break;

    case 2:
      //player score will display regardless if the player has won or lost
      score_text.setString("YOUR FINAL SCORE WAS: " + std::to_string(score));
      score_text.setPosition(window.getSize().x /2 - score_text.getGlobalBounds().width /2, 50);
      score_text.setScale(1,1);
      score_text.setFillColor(sf::Color(0,0,255,255));
      window.draw(score_text);
      if(!player_has_won)
      {
        window.draw(game_over);
        //game over screen
      }
      else
      {
        //player has won text
        game_over.setString("GAME OVER YOU WIN! \n[ENTER] to play again \n [ESC] to quit");
        game_over.setFillColor(sf::Color(0,255,0,255));
        window.draw(game_over);
      }
      break;
  }
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
}

void Game::keyPressed(sf::Event event)
{
  switch(game_state)
  {
    case 0:
      //menu
      if(event.key.code == sf::Keyboard::Enter)
      {
        game_state = 1;
        //game starts running
      }
      break;

    case 1:
      //key presses for game running
      if(event.key.code == sf::Keyboard::A)
      {
        //paddle will move (reverse direction)
        paddle_direction = -1;
      }
      else if(event.key.code == sf::Keyboard::D)
      {
        //paddle moves conventionally
        paddle_direction = 1;
      }

      if(respawn_ball)
      {
        if(event.key.code == sf::Keyboard::Space)
        {
          respawn_ball = false;
        }
      }
      break;

    case 2:
      //game over player can press enter to play again or esc to quit
      if(event.key.code == sf::Keyboard::Enter)
      {
        game_state = 1;
        //game starts running
        //reset all variables to create a new game
        health = 5;
        score = 0;
        live_counter.setString("PLAYER LIVES: 5");
        respawn_ball = false;

        //ensure paddle doesnt keep moving
        paddle_direction = 0;

        //resets the score text
        initScore();

        //resets the gems
        gem_on_screen = false;
        initGems();

        //reset ball to original position
        ball.getSprite()->setPosition(
          window.getSize().x / 2 - ball.getSprite()->getGlobalBounds().width / 2,
          window.getSize().y - 200);
        //resets visibility for blocks
        for(int i = 0; i < cols; i++)
        {
          for(int j = 0; j < rows; j++)
          {
            blocks[i][j].setVisibility(true);
          }
        }
      }

      if(event.key.code == sf::Keyboard::Escape)
      {
        window.close();
      }
      break;
  }
}

void Game::keyReleased(sf::Event event)
{
  switch(game_state)
  {
    case 1:
      if(event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D)
      {
        //paddle will stop moving
        paddle_direction = 0;
      }

      //game running
      break;
  }
}

bool Game::checkIfLoseLive()
{
  if(ball.getSprite()->getPosition().y + ball.getSprite()->getGlobalBounds().height
      >= window.getSize().y)
  {
    health -= 1;
    live_counter.setString("PLAYER LIVES: " + std::to_string(health));
    ball.getSprite()->setPosition(
      window.getSize().x / 2 - ball.getSprite()->getGlobalBounds().width / 2,
      window.getSize().y - 200);
    return true;
  }
}

bool Game::checkForBlocks()
{
  for(int i = 0; i < cols; i++)
  {
    for(int j = 0; j < rows; j++)
    {
      if(blocks[i][j].getVisibility())
      {
        return true;
      }
    }
  }
}

bool Game::checkForGems()
{
  for(int i = 0; i < 2; i++)
  {
    if(gems[i].getVisibility())
    {
      return true;
    }
  }
}

int Game::collision_check()
{
  //due to ball being at high speed 1 instead of 0 is used to make the ball not look like its going off the screen
  if(ball.getSprite()->getPosition().x <= 1 ||
      ball.getSprite()->getPosition().x + ball.getSprite()->getGlobalBounds().width >= window.getSize().x - 1)
  {
    //collision on x-axis means x vector is reversed
    return 1;
  }
  else if(ball.getSprite()->getPosition().y <= 1)
  {
    //collision with y-axis means y vector *= -1
    return 2;
  }
  else if(ball.getSprite()->getPosition().y + ball.getSprite()->getGlobalBounds().height >= paddle.getSprite()->getPosition().y &&
           ball.getSprite()->getPosition().x + ball.getSprite()->getGlobalBounds().width >= paddle.getSprite()->getPosition().x &&
           ball.getSprite()->getPosition().x <= paddle.getSprite()->getPosition().x + paddle.getSprite()->getGlobalBounds().width)
  {
    //collision with paddle
    return 2;
  }
  else
  {
    return 0;
  }

}

int Game::block_collision_check()
{
  for(int i = 0; i < cols; i++)
  {
    for(int j = 0; j < rows; j++)
    {
      if((ball.getSprite()->getPosition().y <= blocks[i][j].getSprite()->getPosition().y + blocks[i][j].getSprite()->getGlobalBounds().height &&
          ball.getSprite()->getPosition().x + ball.getSprite()->getGlobalBounds().width >= blocks[i][j].getSprite()->getPosition().x &&
          ball.getSprite()->getPosition().x <= blocks[i][j].getSprite()->getPosition().x + blocks[i][j].getSprite()->getGlobalBounds().width) &&

         (ball.getSprite()->getPosition().y + ball.getSprite()->getGlobalBounds().height >= blocks[i][j].getSprite()->getPosition().y &&
         ball.getSprite()->getPosition().x + ball.getSprite()->getGlobalBounds().width >= blocks[i][j].getSprite()->getPosition().x &&
           ball.getSprite()->getPosition().x <= blocks[i][j].getSprite()->getPosition().x + blocks[i][j].getSprite()->getGlobalBounds().width)&&
          blocks[i][j].getVisibility())
      {
        //ball has hit the bottom of the block
        blocks[i][j].setVisibility(false);
        score += 1;
        score_text.setString("SCORE: " + std::to_string(score));
        return 2;
      }
    }
  }
}

bool Game::gem_collision_check(bool ball_respawn)
{
  for(int i = 0; i < 2; i ++)
  {
    if(gems[i].getSprite()->getPosition().y + gems[i].getSprite()->getGlobalBounds().height >= paddle.getSprite()->getPosition().y &&
        gems[i].getSprite()->getPosition().x + gems[i].getSprite()->getGlobalBounds().width >= paddle.getSprite()->getPosition().x &&
        gems[i].getSprite()->getPosition().x <= paddle.getSprite()->getPosition().x + paddle.getSprite()->getGlobalBounds().width &&
        gems[i].getVisibility())
    {
      gems[i].getSprite()->setPosition(-100, -100);
      score += 3;
      score_text.setString("SCORE: " + std::to_string(score));
      gems[i].setVisibility(false);
    }
    else if(gems[i].getSprite()->getPosition().y + gems[i].getSprite()->getGlobalBounds().height >= window.getSize().y + 50)
    {
      //gem is off the screen and new ones can be spawned
      gems[i].setVisibility(false);
    }
  }

  if(ball_respawn)
  {
    for(int i = 0; i < 2; i ++)
    {
      gems[i].setVisibility(false);
    }
  }
}