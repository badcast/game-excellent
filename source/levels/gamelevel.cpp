#include "gamelevel.h"

#include <fstream>

GameLevel::GameLevel()
    : Level("Excellent Game Level")
{
}
GameObject* g;
uid sld;

void GameLevel::start()
{
    sld = ui->Push_Slider(1, -10, 10, { 50, 50, 200, 30 });
    SDL_Surface* p = GC::GetSurface("plain");

    g = CreateGameObject();

    g->addComponent<Camera2D>()->visibleObjects = true;

    auto spr = g->addComponent<SpriteRenderer>();
    spr->setSpriteFromTextureToGC(p);
    spr->size *= 0.2f;

    auto clone = Instantiate(g, Vec2::one, g->transform());

    g->transform()->position();
}

void GameLevel::update()
{

    float a = g->transform()->angle();
    if (a > 360)
        a -= 360;
    g->transform()->localAngle(a + *static_cast<float*>(ui->getResources(sld)));
}

void GameLevel::onDrawGizmos()
{
    Gizmos::DrawStorm(Vec2::one, 200, 15);
    Gizmos::DrawTextOnPosition(Camera::ViewportToWorldPoint(Vec2::half), std::to_string(*static_cast<float*>(ui->getResources(sld))));
}
