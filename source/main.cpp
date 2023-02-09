#define USE_SINGLE_RUN 0
#if USE_SINGLE_RUN
#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>
#endif

#include <exception>
#include <iostream>

#include "levels/gamelevel.h"

using namespace std;

#if USE_SINGLE_RUN
constexpr char semaphore_identifier[] = "roninengine.znakeq";
sem_t* sem;
void signal_out(int)
{
    if (sem)
        sem_unlink(semaphore_identifier);
    exit(EXIT_FAILURE);
}
#endif

int main()
{
    using namespace RoninEngine;
    setlocale(LC_ALL, "");
#if USE_SINGLE_RUN
    if ((sem = sem_open(semaphore_identifier, 0)) == SEM_FAILED) {
        sem = sem_open(semaphore_identifier, O_CREAT | O_EXCL, 0644, 1);
        if (sem == SEM_FAILED) {
            Application::fail(strerror(errno));
            return EXIT_FAILURE;
        }
    } else {
        Application::show_message("The application has already been launched.");
        return EXIT_FAILURE;
    }
#endif

    Application::init(1024, 600);

    auto level = new GameLevel;

    Application::loadLevel(level);

    Application::simulate();

    delete level;

    Application::Quit();

#if USE_SINGLE_RUN
    sem_close(sem);
    sem_unlink(semaphore_identifier);
#endif

    return EXIT_SUCCESS;
}
