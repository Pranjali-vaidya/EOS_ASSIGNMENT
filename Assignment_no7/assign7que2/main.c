#include <stdio.h>
#include "circle.h"
#include "square.h"
#include "rectangle.h"

int main()
{
	circle_radius = 8.0;
	square_radius = 9.0;
	rectangle_length = 4.0, rectangle_width = 2.0;
	int radius, side, width;

	printf("circle area: %.2f\n", circle_area(radius));
	printf("square area: %.2f\n", square_area(side));
	printf("rectangle area; %.2f\n", rectangle_area(length, width));
	return 0;
}
