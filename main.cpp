#include "display.h"
#include "input.h"
#include "update.h"
#include "object.h"
#include "car.h"
#include "camera.h"
#include "speedway.h"


int main()
{
	Object* car = new Car(10, 0);

	auto* camera = new Camera(car, 10);
	auto* speedway = new Speedway(-150, 0, 150, 20);

	while (true)
	{
		update();
		show(camera);
		input();
	}
}
