#include "../stdafx.h"
#include "Player.h"


#define KeyA  sf::Keyboard::isKeyPressed(sf::Keyboard::A) 
#define KeyD  sf::Keyboard::isKeyPressed(sf::Keyboard::D) 
#define AxisD sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) > 1
#define AxisA  (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X)) < 0
#define JostickSpace (sf::Joystick::isButtonPressed(0, 1))
#define KeySpace  sf::Keyboard::isKeyPressed(sf::Keyboard::Space)



Player::Player(float x, float y, sf::Texture& texture, std::string anim_file)
{
	
	this->speed = 0;
//	anim.loadFromXML("../res/animation/anim.xml", texture);
	//anim.set("run");
	this->posX = x;
	this->posY = y;
	this->dx = 0; this->dy = 0;
	this->state = STAY;
	this->playerOnGround = false;
	this->hp = 100;
	this->life = true;
	this->collider2D.setPosition(posX, posY);
	this->collider2D.setSize(sf::Vector2f(60,60));
	this->collider2D.setFillColor(sf::Color::Transparent);
	this->collider2D.setOutlineThickness(1.f);
	this->collider2D.setOutlineColor(sf::Color::Green);

	

}

Player::~Player()
{

}

const bool & Player::checkLife() const
{
	return this->life;
}

void Player::movement(float time)
{
	if (!sf::Keyboard::isKeyPressed)
	{
		this->state = STAY;
		
	}
	if (KeyD || AxisD)
	{
		this->state = RIGHT; this->speed = 0.1f;
		//anim.set("run");
	}
	else if (KeyA || AxisA)
	{
		this->state = LEFT; this->speed = 0.1f;
		//anim.flip("run");
	}

	if ((KeySpace || JostickSpace) && this->playerOnGround)
	{
		this->state = JUMP;
		this->dy = -0.4f;
		this->playerOnGround = false;
	}
}

void Player::checkCollision(float Dx, float Dy)
{
}

const sf::FloatRect & Player::getRect() const
{
	return sf::FloatRect(this->posX, this->posY, 35, 35);
}

const sf::FloatRect & Player::getGlobalBounds() const
{
	return this->collider2D.getGlobalBounds();
}

const sf::Vector2f & Player::getPosition() const
{
	return sf::Vector2f(this->posX, this->posY);
}


void Player::setPosition(const float x, const float y)
{
	this->posX = x;
	this->posY = y;
}

void Player::updateLife()
{

	if (this->hp <= 0)
	{
		this->life = false;
	}
	else
	{
		this->life = true;

	}
}


void Player::updateCollider(float time)
{
	this->collider2D.setPosition(this->posX, this->posY);
	this->collider2D.setSize(sf::Vector2f(60, 60));
}

void Player::update(float time)
{
		movement(time);
		switch (state) {

		case STAY:break;
		case LEFT:this->dx = -speed; break;
		case RIGHT:this->dx = speed; break;
		case JUMP: break;
		}

		this->posX += dx * time;
		this->updateCollider(time);
		this->posY += dy * time;
		this->speed = 0;
		this->sprite.setPosition(posX, posY);
		//this->dy = dy + 0.0014*time;


		this->updateLife();

	//anim.tick(time);

	

}


void Player::renderCollider(sf::RenderWindow * window)
{
	window->draw(this->collider2D);
}

void Player::render(sf::RenderWindow * window)
{
	this->renderCollider(window);
//	anim.draw(*window, this->posX, this->posY);
}