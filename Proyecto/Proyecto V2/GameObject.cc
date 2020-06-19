#include "GameObject.h"

#include <vector>

GameObject::GameObject(SDL_Renderer *renderer, std::string filename, const Vector2D &pos, const Vector2D &rot, const Vector2D &size)
    : Serializable(), position(pos), rotation(rot), area(size), texture(new Texture(renderer, filename)) {}

GameObject::~GameObject()
{
    if (texture != nullptr)
        delete texture;
}

void GameObject::to_bin()
{
    position.to_bin();
    rotation.to_bin();
    area.to_bin();

    alloc_data(position.size() + rotation.size() + area.size());

    memcpy(_data, position.data(), position.size());
    char *aux = _data + position.size();

    memcpy(aux, rotation.data(), rotation.size());
    aux += rotation.size();

    memcpy(aux, area.data(), area.size());
}

int GameObject::from_bin(char *data)
{
    try
    {
        //Reconstruir la clase usando el buffer _data
        position.from_bin(data);
        char *aux = data + position.size();

        rotation.from_bin(aux);
        aux += rotation.size();

        area.from_bin(aux);

        _size = position.size() + rotation.size() + area.size();

        return 0;
    }
    catch (std::exception e)
    {
        return -1;
    }
}

void GameObject::render()
{
    SDL_Rect destRect;
    destRect.x = position.x;
    destRect.y = position.y;
    destRect.w = texture->getW() * area.x;
    destRect.h = texture->getH() * area.y;

    texture->render(destRect);
}

Vector2D GameObject::getPosition()
{
    return position;
}

Vector2D GameObject::getRotation()
{
    return rotation;
}

Vector2D GameObject::getSize()
{
    return area;
}

void GameObject::setPosition(const Vector2D &pos)
{
    position = pos;
}

void GameObject::setRotation(const Vector2D &rot)
{
    rotation = rot;
}

void GameObject::setSize(const Vector2D &s)
{
    area = s;
}

bool GameObject::isInside(const Vector2D &pos)
{
    return pos.x > (position.x - area.x) && pos.x < (position.x + area.x) &&
           pos.y > (position.y - area.y) && pos.y < (position.y + area.y);
}

bool GameObject::overlaps(GameObject *other)
{
    if (other == nullptr)
        return false;

    std::vector<int> x = {-1, 1, -1, 1}, y = {-1, -1, 1, 1};
    bool inside = false;
    int i = 0;

    while (!inside && i < 4)
    {
        Vector2 aux = {other->getPosition().x + x[i] * other->getSize().x, other->getPosition().y + y[i] * other->getSize().y};
        inside = isInside({0, 0});
        i++;
    }

    return inside;
}