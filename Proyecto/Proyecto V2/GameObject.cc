#include "GameObject.h"

#include <vector>

GameObject::GameObject(SDL_Renderer *renderer, std::string filename, const Vector2 &pos, const Vector2 &rot, const Vector2 &size)
    : Serializable(), position(pos), rotation(rot), area(size), texture(new Texture(renderer, filename)) {}

GameObject::GameObject(GameObject *g) : position(g->position), rotation(g->rotation), area(g->area), texture(g->texture)
{
}

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
        std::cout << "Error al deserializar\n";
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

Vector2 GameObject::getPosition()
{
    return position;
}

Vector2 GameObject::getRotation()
{
    return rotation;
}

Vector2 GameObject::getSize()
{
    return area;
}

void GameObject::setPosition(const Vector2 &pos)
{
    position = pos;
}

void GameObject::setRotation(const Vector2 &rot)
{
    rotation = rot;
}

void GameObject::setSize(const Vector2 &s)
{
    area = s;
}

Texture *GameObject::getTexture()
{
    return texture;
}

bool GameObject::isInside(const Vector2 &pos)
{
    return pos.x > position.x && pos.x < position.x + area.x * texture->getW() &&
           pos.y > position.y && pos.y < position.y + area.y * texture->getH();
}

bool GameObject::overlaps(GameObject *other)
{
    if (other == nullptr)
        return false;

    std::vector<int> x = {0, 1, 0, 1}, y = {0, 0, 1, 1};
    bool inside = false;
    int i = 0;

    while (!inside && i < 4)
    {
        Vector2 aux = {other->getPosition().x + x[i] * other->getSize().x * other->getTexture()->getW(), 
        other->getPosition().y + y[i] * other->getSize().y * other->getTexture()->getH()};
        inside = isInside(aux);
        i++;
    }

    return inside;
}
