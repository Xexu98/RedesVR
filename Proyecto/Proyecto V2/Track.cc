#include "Map.h"
#include "Game.h"   
#include "Player.h"

#include <algorithm>

std::vector<Vector2> Track::obstaclesBasePos = std::vector<Vector2>();
double Track::endY = 200;

Track::Track(SDL_Renderer *renderer, const Vector2 &startPos, int width) : obstacleFilename("./Assets/OilSpill.png"), playerFilename("./Assets/player.png"),
                                                                           backgroundFilename("./Assets/Road.png"), goalFilename("./Assets/Goal.png"),
                                                                           obstacles(std::vector<GameObject *>()), startPos(startPos), renderer(renderer)
{
    offset = width / (N_LANES * 4);

    background = new GameObject(renderer, backgroundFilename, {startPos.x, -INITIAL_RESOLUTION_Y}, {}, {5, 5});
    goal = new GameObject(renderer, goalFilename, {startPos.x, endY}, {}, {5, 1});
    player = new Player(renderer, playerFilename, startPos, {}, {0.5, 0.5}, width);

    createObstacles();
}

Track::~Track()
{
    clearObstacles();
    delete player;
    delete background;
    delete goal;
}

void Track::to_bin()
{
    startPos.to_bin();
    int dataSize = startPos.size();
    for (GameObject *obstacle : obstacles)
    {
        if (obstacle != nullptr)
        {
            obstacle->to_bin();
            dataSize += obstacle->size();
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

    if (goal != nullptr)
    {
        goal->to_bin();
        dataSize += goal->size();
    }

    alloc_data(dataSize + sizeof(int));
    memcpy(_data, startPos.data(), startPos.size());
    char *aux = _data + startPos.size();

    int nObstacles = obstacles.size();
    memcpy(aux, &nObstacles, sizeof(int));
    aux += sizeof(int);

    for (GameObject *obstacle : obstacles)
    {
        if (obstacle != nullptr)
        {
            memcpy(aux, obstacle->data(), obstacle->size());
            aux += obstacle->size();
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

    if (goal != nullptr)
    {
        memcpy(aux, goal->data(), goal->size());
        aux += goal->size();
    }
}

int Track::from_bin(char *data)
{
    try
    {
        startPos.from_bin(data);
        char *aux = data + startPos.size();

        int dataSize = startPos.size();

        int nObstacles = 0;
        memcpy(&nObstacles, aux, sizeof(int));
        aux += sizeof(int);

        if (nObstacles > obstacles.size())
            for (int i = obstacles.size(); i < nObstacles; i++)
                obstacles.push_back(new GameObject(renderer, obstacleFilename));

        for (int i = 0; i < nObstacles; i++)
        {
            GameObject *obstacle = obstacles[i];
            if (obstacle != nullptr)
            {
                obstacle->from_bin(aux);
                aux += obstacle->size();
                dataSize += obstacle->size();
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

        if (goal == nullptr)
            goal = new GameObject(renderer, goalFilename);

        goal->from_bin(aux);
        aux += goal->size();
        dataSize += goal->size();

        _size = dataSize + sizeof(int);

        return 0;
    }
    catch (std::exception e)
    {
        std::cout << "Error al deserializar\n";
        return -1;
    }
}

void Track::update(double deltaTime)
{
    if (player != nullptr)
    {
        player->update(deltaTime);

        Vector2 vel = {0, player->getVelocity()};
        for (GameObject *obstacle : obstacles)
            if (obstacle != nullptr)
                obstacle->setPosition(obstacle->getPosition() + vel * deltaTime);

        if (background != nullptr)
        {
            background->setPosition(background->getPosition() + vel * deltaTime);
            if (background->getPosition().y + 10 >= 0)
                background->setPosition({background->getPosition().x, -INITIAL_RESOLUTION_Y});
        }

        if (goal != nullptr)
            goal->setPosition(goal->getPosition() + vel * deltaTime);
    }
    checkCollisions();
}

void Track::render()
{
    if (background != nullptr)
        background->render();

    if (goal != nullptr)
        goal->render();

    for (GameObject *obstacle : obstacles)
        if (obstacle != nullptr)
            obstacle->render();

    if (player != nullptr)
        player->render();
}

void Track::handleInput(Input input)
{
    if (player != nullptr)
        player->handleInput(input);
}

void Track::checkCollisions()
{
    int i = 0;
    while (i < obstacles.size())
    {        
        if (obstacles[i] != nullptr && player != nullptr && (obstacles[i]->overlaps(player) || player->overlaps(obstacles[i])))
            break;

        i++;
    }

    if (i < obstacles.size())
    {
        if (player != nullptr)
            player->slowDown();

        std::cout << "Colision\n";
    }   
}

void Track::createObstacles()
{
    for (int i = 0; i < Track::obstaclesBasePos.size(); i++)
    {
        Vector2 pos = Vector2(startPos.x + offset, 0) + Track::obstaclesBasePos[i];
        obstacles.push_back(new GameObject(renderer, obstacleFilename, pos, {}, {0.5, 0.5}));        
    }
}

bool Track::raceEnded()
{
    return player != nullptr && goal != nullptr && (goal->overlaps(player) || player->overlaps(goal));
}

void Track::setObstaclesPosition(int width, int posY)
{
    if (!Track::obstaclesBasePos.empty())
        return;

    srand((unsigned)time(0));
    double y = posY;

    while (y > endY)
    {
        int lane;
        int nObstaclesInLane = rand() % N_LANES;

        std::vector<bool> obstacleInLane(N_LANES, false);
        for (int i = 0; i < nObstaclesInLane; i++)
        {
            do
            {
                lane = std::rand() % N_LANES;
            } while (obstacleInLane[lane]);

            Track::obstaclesBasePos.push_back({lane * (double)width / (double)N_LANES, y});
            y -= (std::rand() % (MAX_O_DIST - MIN_O_DIST)) + MIN_O_DIST;
        }
    }
}

void Track::removeObstacle(GameObject *obstacle)
{
    auto it = std::find(obstacles.begin(), obstacles.end(), obstacle);
    if (it != obstacles.end())
    {
        obstacles.erase(it);
        if (obstacle != nullptr)
            delete obstacle;
    }
}

void Track::clearObstacles()
{
    //Vector auxiliar para poder borrar referencias
    std::vector<GameObject *> aux = obstacles;
    for (GameObject *obstacle : aux)
        removeObstacle(obstacle);

    aux.clear();
    obstacles.clear();
}