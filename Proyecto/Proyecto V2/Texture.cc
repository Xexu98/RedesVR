#include "Texture.h"

Texture::Texture(SDL_Renderer *r, std::string file, int numRows, int numCols) : renderer(r), filename(file)
{
    load(filename, numRows, numCols);
}

Texture::~Texture()
{
    free();
}

int Texture::getW() const
{
    return w;
}

int Texture::getH() const
{
    return h;
}

int Texture::getNumCols() const
{
    return numCols;
}

int Texture::getNumRows() const
{
    return numRows;
}

SDL_Texture *Texture::getTexture() const
{
    return texture;
}

std::string Texture::getFilename() const
{
    return filename;
}

void Texture::free()
{
    if (texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
    w = h = 0;
}

void Texture::load(std::string filename, int nRows, int nCols)
{
    if (renderer == nullptr)
        return;

    SDL_Surface *tempSurface = IMG_Load(filename.c_str());
    free();

    texture = SDL_CreateTextureFromSurface(renderer, tempSurface);

    numRows = nRows;
    numCols = nCols;
    w = tempSurface->w;
    h = tempSurface->h;
    fw = w / numCols;
    fh = h / numRows;

    SDL_FreeSurface(tempSurface);
}

void Texture::render(const SDL_Rect &destRect, double angle, SDL_Point anchor, SDL_RendererFlip flip) const
{
    SDL_Rect srcRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = w;
    srcRect.h = h;

    SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, &anchor, flip);
}

void Texture::renderFrame(const SDL_Rect &destRect, int row, int col, double angle, SDL_Point anchor, SDL_RendererFlip flip) const
{
    SDL_Rect srcRect;
    srcRect.x = fw * col;
    srcRect.y = fh * row;
    srcRect.w = fw;
    srcRect.h = fh;

    SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, &anchor, flip);
}