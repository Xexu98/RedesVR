#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Texture
{
private:
    SDL_Texture *texture;
    SDL_Renderer *renderer;

    int w;
    int h;
    int fw; // Frame width
    int fh; // Frame height
    int numCols;
    int numRows;

    std::string filename;

public:
    Texture(SDL_Renderer *r, std::string file, int numRows = 1, int numCols = 1);
    ~Texture();

    void free();

    int getW() const;
    int getH() const;

    int getNumCols() const;
    int getNumRows() const;

    SDL_Texture *getTexture() const;
    std::string getFilename() const;

    void load(std::string filename, int numRows = 1, int numCols = 1);

    void render(const SDL_Rect &destRect, double angle = 0, SDL_Point anchor = {0, 0}, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
    void renderFrame(const SDL_Rect &destRect, int row, int col, double angle = 0, SDL_Point anchor = {0, 0}, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
};

#endif