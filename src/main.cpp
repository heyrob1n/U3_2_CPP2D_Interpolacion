#include <vector>
#include <Motor/GameEngine.hpp>

int main(int argc, char *argv[])
{
	srand(time(nullptr));
	GameEngine motor;
	motor.OnInit();

    return motor.MainLoop();
}