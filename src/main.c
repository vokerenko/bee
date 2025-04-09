#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define ERROR(text) (printf("%s: %s \n", text, SDL_GetError()))
#define YELLOW {255, 255, 0, 255}
#define RED {255, 0, 0, 255}
#define BLUE {0,0,255,255}
#define GREEN {0,255,0,255}
#define IMG_PATH "res/img/"
#define FONT_PATH "res/font/"
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

typedef struct {
    float x;
    float y;
} Vector2;
void normalize(Vector2* vec);
float random_float(float min, float max);
int collision(SDL_Rect*, SDL_Rect*);
SDL_Texture* CreateTextureFromImage(SDL_Surface* surface, const char* image, SDL_Renderer* renderer, SDL_Window* window);
int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        ERROR("SDL_Init_VIDEO");
        return 1;
    }

    if (SDL_Init(IMG_INIT_PNG) != 0) {
        ERROR("SDL_Init_PNG");
        return 1;
    }
    if (TTF_Init() != 0) {
        ERROR("TTF_Init()");
        SDL_Quit();
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("Bee game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (!window) {
        ERROR("SDL_CreateWindow");
        SDL_Quit();
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        ERROR("SDL_CreateRenderer");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    TTF_Font* font = TTF_OpenFont(FONT_PATH "font.ttf", 24);
    if (!font) {
        ERROR("font");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    char buffer[20];
    unsigned char running = 1;
    srand(time(0));
    SDL_Event event;
    SDL_Surface* surface;
    SDL_Rect text = {SCREEN_WIDTH - 200, 0 + 50, 200, 50};
    SDL_Texture* hive_texture = CreateTextureFromImage(surface,IMG_PATH "hive.png", renderer, window);
    SDL_Texture* bee_texture = CreateTextureFromImage(surface, IMG_PATH "bee_nowings.png", renderer, window);
    SDL_Texture* bee_wings_texture = CreateTextureFromImage(surface, IMG_PATH "bee_wings.png", renderer, window);
    SDL_Texture* bee_wings_hands_texture = CreateTextureFromImage(surface, IMG_PATH "bee_wings_hands.png", renderer, window);
    SDL_Texture* bee_hands_texture = CreateTextureFromImage(surface, IMG_PATH "bee_nowings_hands.png", renderer, window);
    
    SDL_Texture* flower_texture = CreateTextureFromImage(surface,IMG_PATH "flower_lit.png", renderer, window);
    SDL_Texture* flower_unlit_texture = CreateTextureFromImage(surface,IMG_PATH "flower_unlit.png", renderer, window);
    SDL_Texture* background_texture = CreateTextureFromImage(surface,IMG_PATH "background_copy.png", renderer, window);
    SDL_Rect hive = {SCREEN_WIDTH - 500, SCREEN_HEIGHT - 400, 300, 342};
    SDL_Rect bee = {300, 300,308/2, 300/2};
    int wings = 1;
    float bee_wings_timer = 0.0f;
    int has_food = 0;
    int direction = 0; // 0 - left, 1 - right
    SDL_Rect background = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
#define FLOWER_COUNT 15
    SDL_Rect flowers[FLOWER_COUNT];
    int is_unlit[FLOWER_COUNT];
    float litness[FLOWER_COUNT];
    float flower_timer[FLOWER_COUNT];
    
    for (int i = 0; i < FLOWER_COUNT; i++) {
        int x, y;
        int collides_with_flowers;
        do {
            collides_with_flowers = 0;
            x = rand() % (SCREEN_WIDTH - 100);
            y = rand() % (SCREEN_HEIGHT - 117);
            flowers[i].x = x;
            flowers[i].y = y;
            flowers[i].w = 100;
            flowers[i].h = 117;
            for (int j = 0; j < i; j++) {
                if (collision(&flowers[i], &flowers[j])) {
                    collides_with_flowers = 1;
                }
            }
        } while(collision(&flowers[i], &hive) || collides_with_flowers);
        is_unlit[i] = 0;
        litness[i] = 1.0f;
        flower_timer[i] =0.0f;
    }
    float speed = 10.0f;
    unsigned int lastTime = SDL_GetTicks();
    float deltaTime = 0.0f;
    while (running) {
        if (has_food) sprintf(buffer, "has_food");
        else sprintf(buffer, "no food");
        SDL_Surface* text_surface = TTF_RenderText_Solid(font, buffer, (SDL_Color)RED);
        SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        unsigned int currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
        Vector2 bee_direction = {0.0f, 0.0f};
        const char *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_LEFT]) {
            bee_direction.x -= 1.0f;
            direction = 0;
        }
        if (state[SDL_SCANCODE_RIGHT]) {
            bee_direction.x += 1.0f;
            direction = 1;
        }
        if (state[SDL_SCANCODE_UP]) {
            bee_direction.y -= 1.0f;
        }
        if (state[SDL_SCANCODE_DOWN]) {
            bee_direction.y += 1.0f;
        }
        if (state[SDL_SCANCODE_ESCAPE]) {
            running = 0;
        }
        bee_direction.x += random_float(-1.0f, 1.0f);
        bee_direction.y += random_float(-1.0f, 1.0f);

        normalize(&bee_direction);
        bee.x += roundf(speed * bee_direction.x);
        bee.y += roundf(speed * bee_direction.y);
        bee.x = fmax(bee.x, 0);
        bee.y = fmin(bee.y, SCREEN_HEIGHT - bee.h);
        bee.y = fmax(bee.y, 0);
        bee.x = fmin(bee.x, SCREEN_WIDTH - bee.w);
        for (int i = 0; i < FLOWER_COUNT; i++) {
            if (collision(flowers + i, &bee)) {        
                if (!has_food && !is_unlit[i]) {
                    litness[i] -= deltaTime; 
                    litness[i] = fmax(litness[i], 0.0f);
                    if (litness[i] <= 0.0f) {
                        has_food = 1;
                        is_unlit[i] = 1;
                    }
                    break;
                }
            }
        }
        bee_wings_timer += deltaTime;
        if (bee_wings_timer >= 1.0f / 16) {
            bee_wings_timer = 0.0f;
            if (wings) wings = 0;
            else wings = 1;
        }
#define FLOWER_TIMER 45.0f

        for (int i = 0; i < FLOWER_COUNT; i++) {
            if (is_unlit[i]) {
                flower_timer[i] += deltaTime;
                litness[i] += deltaTime / FLOWER_TIMER;
                litness[i] = fmin(litness[i], 1.0f);
                if (flower_timer[i] >= FLOWER_TIMER) {
                    is_unlit[i] = 0;
                    flower_timer[i] = 0.0f;
                }
            }
        }
        if (collision(&hive, &bee)) {
            has_food = 0;
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background_texture, NULL, &background);
        
        for (int i = 0; i < FLOWER_COUNT; i++) {
            SDL_RenderCopy(renderer, flower_unlit_texture, NULL, &flowers[i]);
            SDL_SetTextureAlphaMod(flower_texture, litness[i] * 255);
            SDL_RenderCopy(renderer, flower_texture, NULL, &flowers[i]);
        }
        SDL_RenderCopy(renderer, hive_texture, NULL, &hive);

        int flip;
        if (direction) flip = SDL_FLIP_HORIZONTAL;
        else flip = SDL_FLIP_NONE;
        if (wings) {
            SDL_Texture* texture = bee_wings_texture;
            if (has_food) texture = bee_wings_hands_texture;
            SDL_RenderCopyEx(renderer, texture, NULL, &bee, 0.0, NULL, flip);
        }
        else {
            SDL_Texture* texture = bee_texture;
            if (has_food) texture = bee_hands_texture;
            SDL_RenderCopyEx(renderer, texture, NULL, &bee, 0.0, NULL, flip);
        }

        SDL_RenderCopy(renderer, text_texture, NULL, &text);

        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
float random_float(float min, float max) {
    return (float)rand() / (float)(RAND_MAX) * (max-min) + min;
}
void normalize(Vector2* vec) {
    float length = sqrt(vec->x*vec->x +  vec->y*vec->y);
    if (length > 0.00001f) {
        vec->x /= length;
        vec->y /= length;
    }
}
// TODO Redo this function into few separate functions
SDL_Texture* CreateTextureFromImage(SDL_Surface* surface, const char* image, SDL_Renderer* renderer, SDL_Window* window){
    surface = IMG_Load(image);
    if (!surface) {
        SDL_Log("Image load %s  error: %s \n",image,  IMG_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return NULL;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}
int collision(SDL_Rect* a, SDL_Rect* b) {
    return a->x < b->x + b->w && a->x + a->w > b->x && a->y < b->y + b->h && a->y + a->h > b->y;
}
