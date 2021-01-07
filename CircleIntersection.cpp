

# include "classes.h"
# include <math.h>
#include <iostream>
#include <string>
#include <regex>
#include "CircleIntersection.hpp"



//double* convert_to_meters(Coordinate C)
{
	//double y=C.get_latitude()*111000;
	//double x=C.get_longitude()*111000*cos(C.get_latitude()*M_PI/180);
	//static double array [2] = { x, y };
	//return array;
}

 Coordinate convert_to_coordinates(double* array)
{
 	double latitude=array[1]/111000;
 	double longitude=array[0]/(111000*cos(latitude*M_PI/180));
	return Coordinate (latitude, longitude);
}

std::vector<Coordinate> get_intersection(Order Order1, Order Order2)
// this function is the mathematical way to get the intersection of the radius between two orders, this is necessary in order for the next one to be able to take in a vector of orders, and say wether or not they can all fit in one bucket.
{
	Coordinate C1= Order1.get_user().get_coordinates();	
	Coordinate C2= Order2.get_user().get_coordinates();
	//double* c1= convert_to_meters(C1);
	//double* c2= convert_to_meters(C2);
	double y=C1.get_latitude()*111000;
	double x=C1.get_longitude()*111000*cos(C1.get_latitude()*M_PI/180);
	double y1=C2.get_latitude()*111000;
	double x2=C2.get_longitude()*111000*cos(C2.get_latitude()*M_PI/180);
	double r1=Order1.get_distance();
	double r2=Order2.get_distance();
	double d= C1.get_distance(C2);
	if (d > r1+ r2)
		return std::vector<Coordinate>();
	double a=(r1*r1-r2*r2+d*d)/(2*d);
	double h=sqrt(r1*r1-a*a);
	double b=d-a;
	double c3x= x + a*( x1 - x )/d;
	double c3y= y + a*( y1 - y )/d;
	double c4x = c3x + h*(y1 -y) /d;
	double c4y = c3y - h*( x1 - x )/d;
	double c5x = c3x - h*(y1 -y) /d;
	double c5y = c3y + h*(  x1 - x )/d;
	double c4[2]={c4x, c4y};
	double c5[2]={c5x, c5y};

	Coordinate Intersection1= convert_to_coordinates(c4);
	Coordinate Intersection2= convert_to_coordinates(c5);
	std::vector<Coordinate> vect;
              vect.push_back(Intersection1); 
              vect.push_back(Intersection2);
              return vect;
}

bool check_if_inside(Order Order1, Order Order2){
	// this one simply checks if an order is inside another order when there is no intersection. 
	Coordinate C1= Order1.get_user().get_coordinates();	
	Coordinate C2= Order2.get_user().get_coordinates();
	double* c1= convert_to_meters(C1);
	double* c2= convert_to_meters(C2);
	double r1=Order1.get_distance();
	double r2=Order2.get_distance();
	double d= C1.get_distance(C2);
	if (d<=abs(r1-r2))
		return true;
	return false;
}

boolPoint check_if_bucket (std::vector <Order> order_vector)
	// This function takes in a vector of orders, so a potential bucket, and says whether or not they could all fit in a bucket, and returns the intersection where to deliver if it is true.
	//If it its false it will return an empty coordinate and false. 
	//In order to check if an other order can be added to a bucket we could simply take the vector and pushback the new order. And say if check_if_bucket then its good.
{
	struct boolPoint p3 = {Coordinate(), false};
	int count0=0;
	for (int i = 0; i < order_vector.size(); i++){
		Order order1 = order_vector[i];
		for (int j = i+1; j < order_vector.size(); j++){
			Order order2 = order_vector[j];
			std::vector <Coordinate> intersection_vector=get_intersection(order1, order2);
			if (intersection_vector.size()== 0 && !check_if_inside(order1, order2))
				return p3;
			if (intersection_vector.size()== 0 && check_if_inside(order1, order2))
			{
				count0++;
				continue;
			}
			Coordinate intersection1=intersection_vector[0];
			Coordinate intersection2=intersection_vector[1];
			int count1= 0;
			int count2=0;
			for (int k = 0; k < order_vector.size(); k++)
			{
				if (intersection1.get_distance(order_vector[k].get_user().get_coordinates()) <= order_vector[k].get_distance())
						count1++;
				if (intersection2.get_distance(order_vector[k].get_user().get_coordinates()) <= order_vector[k].get_distance())
						count2++;
			}
			if (order_vector.size()==count1)
			{
				struct boolPoint p1 = {intersection1, true};
				return p1;
			}
			if (order_vector.size()==count2)
			{
				struct boolPoint p2 = {intersection2, true};
				return p2;
			}

	}}
	if (count0==(order_vector.size()*order_vector.size()-order_vector.size())/2)
	{
		struct boolPoint p4 = {order_vector[0].get_user().get_coordinates(), true};
				return p4;
	}
	return p3;
}
















