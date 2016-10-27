#include "Player.h"
#include "Game.h"

#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

#include "Bomb.h"
#include "Block.h"
#include "TileMap.h"
#include "ItemBomb.h"
#include "SceneGame.h"
#include "ItemSword.h"
#include "ItemPickaxe.h"

Player::Player()
{
    inventory = new Inventory();
}

Player::~Player()
{
    delete spriteHeart;
}

bool Player::lookingLeft() const
{
    return velocity.x < 0.0f ||
            sprite->animation() == STAND_LEFT ||
            sprite->animation() == MOVE_LEFT ||
            sprite->animation() == PICKAXE_LEFT ||
            sprite->animation() == SWORD_LEFT ||
            sprite->animation() == BOMB_LEFT;
}


void Player::init()
{
    Character::init();

    ShaderProgram *program = Game::getCurrentScene()->getShaderProgram();

    // Heart
    textureHeart.loadFromFile("images/heartSpritesheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
    textureHeart.setMinFilter(GL_NEAREST);
    textureHeart.setWrapS(GL_CLAMP_TO_EDGE);
    spriteHeart = Sprite::createSprite(glm::ivec2(heartSize), glm::vec2(0.29f, 1.0f), &textureHeart, program);
    spriteHeart->setNumberAnimations(3);
    spriteHeart->addKeyframe(0, glm::vec2(0.7f, 0.f));
    spriteHeart->addKeyframe(1, glm::vec2(0.35f, 0.f));
    spriteHeart->addKeyframe(2, glm::vec2(0.0f, 0.f));
    //

    // Player
    spritesheet.loadFromFile("images/miner.png", TEXTURE_PIXEL_FORMAT_RGBA);

    sprite = Sprite::createSprite(glm::ivec2(36, 46), glm::vec2(0.081f, 0.24f), &spritesheet, program);
    sprite->setNumberAnimations(DEAD+1);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
    sprite->addKeyframe(STAND_LEFT, glm::vec2(0.0f, 0.0f));
    sprite->setAnimationSpeed(STAND_RIGHT, 8);
    sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.0f, 0.25f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.0f, 0.0f));
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.09f, 0.0f));
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.18f, 0.0f));
	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.0f, 0.25f));
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.1f, 0.25f));
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.2f, 0.25f));

    /*
        PICKAXE_LEFT, PICKAXE_RIGHT,
        SWORD_LEFT, SWORD_RIGHT,
        BOMB_LEFT, BOMB_RIGHT,
        DEAD
        */
    sprite->setAnimationSpeed(PICKAXE_LEFT, 8);
    sprite->addKeyframe(PICKAXE_LEFT, glm::vec2(0.28f, 0.0f));
    sprite->addKeyframe(PICKAXE_LEFT, glm::vec2(0.38f, 0.0f));
    sprite->addKeyframe(PICKAXE_LEFT, glm::vec2(0.48f, 0.0f));
    sprite->setAnimationSpeed(PICKAXE_RIGHT, 8);
    sprite->addKeyframe(PICKAXE_RIGHT, glm::vec2(0.29f, 0.25f));
    sprite->addKeyframe(PICKAXE_RIGHT, glm::vec2(0.39f, 0.25f));
    sprite->addKeyframe(PICKAXE_RIGHT, glm::vec2(0.49f, 0.25f));

    sprite->setAnimationSpeed(SWORD_LEFT, 8);
    sprite->addKeyframe(SWORD_LEFT, glm::vec2(0.67f, 0.497f));
    sprite->addKeyframe(SWORD_LEFT, glm::vec2(0.77f, 0.497f));
    sprite->addKeyframe(SWORD_LEFT, glm::vec2(0.87f, 0.497f));
    sprite->setAnimationSpeed(SWORD_RIGHT, 8);
    sprite->addKeyframe(SWORD_RIGHT, glm::vec2(0.67f, 0.735f));
    sprite->addKeyframe(SWORD_RIGHT, glm::vec2(0.77f, 0.735f));
    sprite->addKeyframe(SWORD_RIGHT, glm::vec2(0.87f, 0.735f));

    sprite->setAnimationSpeed(BOMB_LEFT, 8);
    sprite->addKeyframe(BOMB_LEFT, glm::vec2(0.67f, 0.0f));
    sprite->addKeyframe(BOMB_LEFT, glm::vec2(0.77f, 0.0f));
    sprite->addKeyframe(BOMB_LEFT, glm::vec2(0.87f, 0.0f));
    sprite->setAnimationSpeed(BOMB_RIGHT, 8);
    sprite->addKeyframe(BOMB_RIGHT, glm::vec2(0.67f, 0.255f));
    sprite->addKeyframe(BOMB_RIGHT, glm::vec2(0.77f, 0.255f));
    sprite->addKeyframe(BOMB_RIGHT, glm::vec2(0.87f, 0.255f));

    sprite->setAnimationSpeed(DEAD, 1);
    sprite->addKeyframe(DEAD, glm::vec2(0.575f, 0.05f));
    //

    inventory->init();

    int x = 700;
    int surfaceLevel = Game::getCurrentSceneGame()->getTileMap()->getSurfaceLevel(x);
    int y = surfaceLevel - 3 * sprite->getSize().y;
    setPosition(glm::ivec2(x, y));

    for (int i = 0; i < 99; ++i) inventory->addItem<ItemBomb>();
}

void Player::update(int deltaTime)
{
    Character::update(deltaTime);

    timeSinceLastItemUsed += deltaTime;

    if (!dead)
    {
        if (damaged)
        {
            sprite->setVisible(Scene::getCurrentTime() % (damageBlinkFrequency * 2) < damageBlinkFrequency);
            invulnerabilityTimer -= deltaTime;
        }

        if (invulnerabilityTimer <= 0) {
            damaged = false;
            sprite->setVisible(true);
            invulnerabilityTimer = invulnerabilityPeriod;
        }

        handleItemSelection();
        handleMouseActions();
    }
    else
    {
        sprite->changeAnimation(DEAD);

        timeSinceDead += deltaTime;
        float timeToDie = 4000.0f;
        Game::getCurrentSceneGame()->getShaderProgram()->
                setUniform1f("grayAmount", timeSinceDead / timeToDie);

        if (timeSinceDead > timeToDie)
        {
            die();
        }
    }

    updateMovementAnimation();
}

void Player::render(ShaderProgram &program)
{
    Character::render(program);
}

Item *Player::getSelectedItem() const
{
    return selectedItem;
}

int Player::getSelectedItemIndex() const
{
    return selectedItemIndex;
}

Inventory *Player::getInventory()
{
    return inventory;
}

void Player::move(int deltaTime)
{
    bool leftPressed = Game::instance().getKey('a') || Game::instance().getKey('A');
    bool rightPressed = Game::instance().getKey('d') || Game::instance().getKey('D');
	bool bothPressed = leftPressed && rightPressed;
	bool anyPressed = leftPressed || rightPressed;

    if (!anyPressed || bothPressed)
    {
		velocity.x = 0;
	}
	else
    {
        velocity.x = leftPressed ? -8 : 8;
    }
	
    if ((Game::instance().getKey('w') || Game::instance().getKey('W')) && !bJumping && isGrounded())
    {
		jump();
	}

    Character::applyGravity();
}

void Player::handleItemSelection()
{
    for (int i = 0; i < inventory->getNumSlots(); ++i)
    {
        // Key selection
        if (Game::instance().getKey( char('1' + i) ))
        {
            selectedItemIndex = i;
            break;
        }
        else if (Game::instance().getMouseLeftButtonDown())  // Mouse selection
        {
            glm::ivec2 mousePosScreen = Game::instance().getMousePosScreen();
            Rect slotRect = inventory->getSlotScreenRect(i);
            if (slotRect.contains(mousePosScreen))
            {
                selectedItemIndex = i;
                break;
            }
        }
    }

    // Q & E selection
    if (Game::instance().getKeyDown('q')) { --selectedItemIndex; }
    if (Game::instance().getKeyDown('e')) { ++selectedItemIndex; }

    // Limit itemIndex and update selectedItem
    selectedItemIndex = min(selectedItemIndex, inventory->getNumSlots()-1);
    selectedItemIndex = max(selectedItemIndex, 0);
    selectedItem = inventory->getItem(selectedItemIndex);
}

void Player::handleMouseActions()
{
    glm::ivec2 mousePosScreen = Game::instance().getMousePosScreen();
    Rect inventoryRect(inventory->getPosition(),inventory->getSize());
    if (inventoryRect.contains(mousePosScreen)) return;

    TileMap *tmap = Game::getCurrentSceneGame()->getTileMap();
    glm::ivec2 mousePos = Game::instance().getMousePosWorld();
    bool mouseToLeft = (mousePos.x < (getPosition() + getSize() / 2).x);

    Block *mouseBlock = NULL;
    int tileSize = tmap->getTileSize();
    glm::ivec2 playerCenter = getPosition() + getSize() / 2;

    glm::vec2 mouseDir = glm::normalize(glm::vec2(mousePos) - glm::vec2(playerCenter));
    mouseBlock = tmap->getBlock(playerCenter + glm::ivec2(mouseDir * float(tileSize) * 0.5f));
    mouseBlock = mouseBlock ? mouseBlock : tmap->getBlock(playerCenter + glm::ivec2(mouseDir * float(tileSize) * 1.0f));
    mouseBlock = mouseBlock ? mouseBlock : tmap->getBlock(playerCenter + glm::ivec2(mouseDir * float(tileSize) * 1.5f));
    mouseBlock = mouseBlock ? mouseBlock : tmap->getBlock(playerCenter + glm::ivec2(mouseDir * float(tileSize) * 2.0f));

    if (mouseBlock != lastMouseBlock || !Game::instance().getMouseLeftButton())
    {
        if (lastMouseBlock)
        {
            lastMouseBlock->onHitEnd();
            lastMouseBlock = NULL;
        }
    }

    if (timeSinceLastItemUsed < itemCooldown) return;


    if (!Game::instance().getMouseLeftButton())
        usingItem = false;


    if (!selectedItem || !dynamic_cast<ItemPickaxe*>(selectedItem)) { lastMouseBlock = NULL; }
    if (selectedItem)
    {
        if (dynamic_cast<ItemPickaxe*>(selectedItem))
        {
            if (Game::instance().getMouseLeftButton())
            {
                timeSinceLastItemUsed = 0;
                usingItem = true;
                if (mouseToLeft && sprite->animation() != PICKAXE_LEFT) sprite->changeAnimation(PICKAXE_LEFT);
                else if (!mouseToLeft && sprite->animation() != PICKAXE_RIGHT) sprite->changeAnimation(PICKAXE_RIGHT);
                Game::getCurrentSceneGame()->getSoundManager()->playSound("../sounds/gravel.wav",70.f);
            }

            if (Game::instance().getMouseLeftButton())
            {
                if (mouseBlock && mouseBlock->getType() != 0)
                {
                    Game::getCurrentSceneGame()->getCamera()->tremble(1, 50);
                    mouseBlock->onHitBegin();
                }
            }
        }
        else if (dynamic_cast<ItemSword*>(selectedItem))
        {
            if (Game::instance().getMouseLeftButton())
            {
                timeSinceLastItemUsed = 0;
                usingItem = true;
                if (mouseToLeft && sprite->animation() != SWORD_LEFT) sprite->changeAnimation(SWORD_LEFT);
                else if (!mouseToLeft && sprite->animation() != SWORD_RIGHT) sprite->changeAnimation(SWORD_RIGHT);
                Game::getCurrentSceneGame()->getSoundManager()->playSound("../sounds/sword.wav",70.f);

                for (Character *c : Game::getCurrentSceneGame()->getCharacters())
                {
                    if (!c) continue;

                    Enemy *e = dynamic_cast<Enemy*>(c);
                    if (e)
                    {
                        float d = glm::distance(glm::vec2(getPosition()), glm::vec2(e->getPosition()));
                        bool goodDir = (e->getPosition().x < getPosition().x) == mouseToLeft;
                        if (d < swordRange && goodDir)
                        {
                            e->takeDamage();
                        }
                    }
                }
            }
        }
        else if (dynamic_cast<Block*>(selectedItem))
        {
            if (Game::instance().getMouseLeftButton() && isGrounded())
            {
                timeSinceLastItemUsed = 0;
                if (glm::distance(glm::vec2(mousePos), glm::vec2(playerCenter)) < tileSize * 3)
                {
                    // Can it put a block where the mouse is?
                    if (tmap->getBlock(mousePos) == NULL && Game::getCurrentSceneGame()->whosThereTile(mousePos).size() == 0)
                    {
                        Block *b = dynamic_cast<Block*>(selectedItem);
                        // BLOCK ADDING
                        int amount = b->getAmount();
                        if (amount > 0)
                        {
                            Tile *addedBlock = NULL;
                            if (b->getType() == Block::DIRT)         { addedBlock = tmap->addTile<BlockDirt>(mousePos); }
                            else if (b->getType() == Block::ROCK)    { addedBlock = tmap->addTile<BlockRock>(mousePos); }
                            else if (b->getType() == Block::BEDROCK) { addedBlock = tmap->addTile<BlockBedRock>(mousePos); }
                            else if (b->getType() == Block::WOOD)    { addedBlock = tmap->addTile<BlockWood>(mousePos); }
                            else if (b->getType() == Block::PURPLE)  { addedBlock = tmap->addTile<BlockPurple>(mousePos); }

                            if (addedBlock)
                            {
                                inventory->dropItem(selectedItemIndex);
                            }
                        }
                    }
                }
            }
        }
        else if (dynamic_cast<ItemBomb*>(selectedItem))
        {
            if (Game::instance().getMouseLeftButton())
            {
                timeSinceLastItemUsed = 0;
                usingItem = true;
                if (mouseToLeft && sprite->animation() != BOMB_LEFT) sprite->changeAnimation(BOMB_LEFT);
                else if (!mouseToLeft && sprite->animation() != BOMB_RIGHT) sprite->changeAnimation(BOMB_RIGHT);

                Bomb *b = new Bomb();
                b->setPosition( getPosition() );

                glm::vec2 dir = glm::normalize( glm::vec2(mousePos - getPosition()) );
                float bombSpeed = 0.2f * glm::min(50.0f, glm::length(glm::vec2(mousePos - getPosition())));
                b->setVelocity( dir * bombSpeed );

                inventory->dropItem(selectedItemIndex);
            }
        }
    }

    lastMouseBlock = mouseBlock;
}

void Player::renderHearts(ShaderProgram &program)
{
    int heartMarginX = 10;
    for (int i = 0; i < maxHealth/2; ++i)
    {
        glm::ivec2 heartPos = heartLinePosition + (heartSize + heartMarginX) * glm::ivec2(i, 0);
        prepareModelViewMatrix(heartPos);
        program.setUniformMatrix4f("view", glm::mat4(1.0f));
        if ((i+1)*2 <= health)
        {
            spriteHeart->changeAnimation(2); // FULL HEART
        }
        else
        {
            if (i*2 + 1 == health) spriteHeart->changeAnimation(1); // MID HEART
            else spriteHeart->changeAnimation(0); // EMPTY HEART
        }
        spriteHeart->render();
    }
}

bool Player::isBlockSelected(Block *b)
{
    return lastMouseBlock == b && dynamic_cast<ItemPickaxe*>(selectedItem);
}

void Player::takeDamage(int damage)
{
    if (!damaged)
    {
        damaged = true;
        health -= damage;
        Game::getCurrentSceneGame()->getSoundManager()->playSound("../sounds/classic_hurt.wav");
        if (health < 0)
        {
            beginToDie();
        }
    }
}

void Player::beginToDie()
{
    dead = true;
    Text *t = Game::getCurrentSceneGame()->createText("You died", glm::ivec2(0, 200), 60);
    t->centerHorizontally();
    Game::getCurrentSceneGame()->getSoundManager()->playSound("../sounds/Wilhelm_Scream.ogg");
}

void Player::die()
{
    Game::getCurrentSceneGame()->getSoundManager()->stopMusic();
    Game::instance().gotoSceneGame();
}

void Player::onBlockDeleted(Block *b)
{
    if (lastMouseBlock == b)
    {
        lastMouseBlock = NULL;
    }
}

void Player::updateMovementAnimation()
{
    if (usingItem) return;

    bool leftPressed = Game::instance().getKey('a') || Game::instance().getKey('A');
    bool rightPressed = Game::instance().getKey('d') || Game::instance().getKey('D');
    bool bothPressed = leftPressed && rightPressed;
    bool anyPressed = leftPressed || rightPressed;

    if (bothPressed || (velocity.x == 0 && !anyPressed))
    {
        if (lookingLeft()) sprite->changeAnimation(STAND_LEFT);
        else sprite->changeAnimation(STAND_RIGHT);
    }
    else
    {
        if(leftPressed)
        {
            if (sprite->animation() != MOVE_LEFT)
                sprite->changeAnimation(MOVE_LEFT);
        }

        if (rightPressed)
        {
            if (sprite->animation() != MOVE_RIGHT)
                sprite->changeAnimation(MOVE_RIGHT);
        }
    }

}
