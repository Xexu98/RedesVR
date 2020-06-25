#include "Map.h"
#include "Game.h"   
#include "Player.h"
#include "Bullet.h"

#include <algorithm>

std::vector<Vector2D> Map::bulletsBasePos = std::vector<Vector2D>();
double Map::endY = 200;

Map::Map(SDL_Renderer *renderer, const Vector2D &startPos, int width) : bulletFilename("./Assets/whiterect.png"), playerFilename("./Assets/player.png"),
                                                                           backgroundFilename("./Assets/cs2d.jpg"),
                                                                           bullets(std::vector<Bullet *>()), startPos(startPos), renderer(renderer)
{
    offset = width / (N_LANES * 4);

    background = new GameObject(renderer, backgroundFilename, {startPos.x, -INITIAL_RESOLUTION_Y}, {}, {5, 5});
	bullet = new Bullet(renderer, bulletFilename, startPos, {}, { 0.1, 0.1 }, width);
    player = new Player(renderer, playerFilename, startPos, {}, {0.5, 0.5}, width);

	clearBullets();
}

Map::~Map()
{
	clearBullets();
    delete player;
    delete background;

}

void Map::to_bin()
{
    startPos.to_bin();
    int dataSize = startPos.size();
    for (Bullet *bullet : bullets)
    {
        if (bullet != nullptr)
        {
			bullet->to_bin();
			bullet += obstacle->size();
        }
    }

    if (player != nullptr)
    {
        player->to_bin();
        dataSize += player->size();
    }

    if (background != nullptr)
    {
        background->to_bin();
        dataSize += background->size();
    }

  

    alloc_data(dataSize + sizeof(int));
    memcpy(_data, startPos.data(), startPos.size());
    char *aux = _data + startPos.size();

    int nBullets = bullets.size();
    memcpy(aux, &nBullets, sizeof(int));
    aux += sizeof(int);

    for (Bullet *bullet : bullets)
    {
        if (bullet != nullptr)
        {
            memcpy(aux, bullet->data(), bullet->size());
            aux += bullet->size();
        }
    }

    if (player != nullptr)
    {
        memcpy(aux, player->data(), player->size());
        aux += player->size();
    }

    if (background != nullptr)
    {
        memcpy(aux, background->data(), background->size());
        aux += background->size();
    }

  
}

int Map::from_bin(char *data)
{
    try
    {
        startPos.from_bin(data);
        char *aux = data + startPos.size();

        int dataSize = startPos.size();

        int nBullets = 0;
        memcpy(&nBullets, aux, sizeof(int));
        aux += sizeof(int);

        if (nBullets > bullets.size())
            for (int i = bullets.size(); i < nBullets; i++)
				bullets.push_back(new GameObject(renderer, obstacleFilename));

        for (int i = 0; i < nBullets; i++)
        {
            Bullet *bullet = bullets[i];
            if (bullet != nullptr)
            {
				bullet->from_bin(aux);
                aux += bullet->size();
                dataSize += bullet->size();
            }
        }

        if (player == nullptr)
            player = new Player(renderer, playerFilename);

        player->from_bin(aux);
        aux += player->size();
        dataSize += player->size();

        if (background == nullptr)
            background = new GameObject(renderer, backgroundFilename);

        background->from_bin(aux);
        aux += background->size();
        dataSize += background->size();

      

        _size = dataSize + sizeof(int);

        return 0;
    }
    catch (std::exception e)
    {
        std::cout << "Error al deserializar\n";
        return -1;
    }
}

void Map::update(double deltaTime)
{
    if (player != nullptr)
    {
        player->update(deltaTime);

        Vector2D vel = {0, player->getVelocity()};
        for (Bullet *bullet : bullets)
            if (bullet != nullptr)
				bullet->setPosition(bullet->getPosition() + vel * deltaTime);

        if (background != nullptr)
        {
            background->setPosition(background->getPosition() + vel * deltaTime);
            if (background->getPosition().y + 10 >= 0)
                background->setPosition({background->getPosition().x, -INITIAL_RESOLUTION_Y});
        }


    }
    checkCollisions();
}

void Map::render()
{
    if (background != nullptr)
        background->render();


    for (Bullet *bullet : bullets)
        if (bullet != nullptr)
			bullet->render();

    if (player != nullptr)
        player->render();
}

void Map::handleInput(Input input)
{
    if (player != nullptr)
        player->handleInput(input);
}

void Map::checkCollisions()
{
    int i = 0;
    while (i < bullets.size())
    {        
        if (bullets[i] != nullptr && player != nullptr && (bullets[i]->overlaps(player) || player->overlaps(bullets[i])))
            break;

        i++;
    }

    if (i < bullets.size())
    {
        if (player != nullptr)
            player->lessLife();

        std::cout << "Colision\n";
    }   
}

void Map::createBullets()
{
    for (int i = 0; i < Map::bulletsBasePos.size(); i++)
    {
        Vector2D pos = Vector2D(startPos.x + offset, 0) + Map::bulletsBasePos[i];
        bullets.push_back(new GameObject(renderer, bulletFilename, pos, {}, {0.5, 0.5}));        
    }
}

bool Map::raceEnded()
{
    return player != nullptr && goal != nullptr && (goal->overlaps(player) || player->overlaps(goal));
}

void Map::setBulletsPosition(int width, int posY)
{
    if (!Map::bulletsBasePos.empty())
        return;

    srand((unsigned)time(0));
    double y = posY;

    while (y > endY)
    {
        int lane;
        int nBulletsInMap = rand() % N_LANES;

        std::vector<bool> obstacleInLane(N_LANES, false);
        for (int i = 0; i < nBulletsInMap; i++)
        {
            do
            {
                lane = std::rand() % N_LANES;
            } while (obstacleInLane[lane]);

			Map::bulletsBasePos.push_back({lane * (double)width / (double)N_LANES, y});
            y -= (std::rand() % (MAX_O_DIST - MIN_O_DIST)) + MIN_O_DIST;
        }
    }
}

void Map::removeBullet(Bullet *obstacle)
{
    auto it = std::find(bullets.begin(), bullets.end(), obstacle);
    if (it != bullets.end())
    {
		bullets.erase(it);
        if (obstacle != nullptr)
            delete obstacle;
    }
}

void Map::clearBullets()
{

    std::vector<Bullet *> aux = bullets;
    for (Bullet *bullet : aux)
        removeObstacle(bullet);

    aux.clear();
	bullets.clear();
}