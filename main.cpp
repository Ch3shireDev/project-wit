#include "ai_car.h"
#include "display.h"
#include "input.h"
#include "update.h"
#include "object.h"
#include "car.h"
#include "camera.h"
#include "speedway.h"


int main()
{
	auto* speedway = new Speedway(-1000, 0, 1000, 30);
	Car* car = new Car(6, 0);
	AiCar* ai_car = new AiCar(24, 0);
	car->set_speedway(speedway);
	car->set_collider(ai_car);
	auto* camera = new Camera(car, 10);
	while (true)
	{
		update();
		show(camera);
		input();
	}
}
