#include "gamelevel.h"

#include <fstream>

GameLevel::GameLevel()
    : World("Excellent Game Level")
{
}
GameObject* g;
uid sld;

void GameLevel::on_start()
{
    sld = get_gui()->push_slider(1, -10, 10, { 50, 50, 200, 30 });
   // SDL_Surface* p = GC::GetSurface("plain");

    g = create_game_object();

    g->add_component<Camera2D>()->visibleObjects = true;

    auto spr = g->add_component<SpriteRenderer>();
 //   spr->setSpriteFromTextureToGC(p);
    spr->size *= 0.2f;

    auto clone = instantiate(g, Vec2::zero, g->transform());

    g->transform()->position();
}

void GameLevel::on_update()
{

    float a = g->transform()->angle();
    if (a > 360)
        a -= 360;
    g->transform()->local_angle(a + *static_cast<float*>(get_gui()->get_resources(sld)));
}

void GameLevel::on_gizmo()
{
    Gizmos::draw_storm(Vec2::one, 200, 15);
    Gizmos::draw_text(Camera::viewport_to_world(Vec2::half), std::to_string(*static_cast<float*>(get_gui()->get_resources(sld))));
}
