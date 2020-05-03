#include "display.h"
#include "input.h"
#include "update.h"
#include "object.h"
#include "car.h"
#include "camera.h"


int main()
{
	Object* car = new Car(50, 30);

	Object* box = new Object(200, 150);
	box->width = 50;
	box->length = 50;

	Object* camera = new Camera(car);

	while (true)
	{
		update();
		show(camera);
		input();
	}
}
