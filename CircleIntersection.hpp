

# include "classes.h"
# include <math.h>
#include <iostream>
#include <string>
#include <regex>

struct boolPoint {    Coordinate p;   bool has_intersection;};


double* convert_to_meters(Coordinate C);

Coordinate convert_to_coordinates(double* array);

std::vector<Coordinate> get_intersection(Order Order1, Order Order2);

boolPoint check_if_bucket (std::vector <Order> order_vector);

bool check_if_inside(Order Order1, Order Order2);



















