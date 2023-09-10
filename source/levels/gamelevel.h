#pragma once
#include <ronin/framework.h>

using namespace RoninEngine;
using namespace RoninEngine::Runtime;
using namespace RoninEngine::AI;
using namespace RoninEngine::UI;

class GameLevel : public World
{
protected:
    void on_start();
    void on_update();
    void on_gizmo();

public:
    GameLevel();
    ~GameLevel() = default;
};
