# include "classes.h"
# include <math.h>
#include <iostream>
#include <string>
#include <regex>
#include "CircleIntersection.hpp"


double* convert_to_meters(Coordinate C)
{
    double y=C.get_latitude()*111000;
    double x=C.get_longitude()*111000*cos(C.get_latitude()*M_PI/180);
    static double array [2] = { x, y };
    return array;
}

 Coordinate convert_to_coordinates(double* array)
{
    double latitude=array[1]/111000;
    double longitude=array[0]/(111000*cos(latitude*M_PI/180));
    return Coordinate (latitude, longitude);
}

std::vector<Coordinate> get_intersection(Order Order1, Order Order2)

{
    Coordinate C1= Order1.get_user().get_coordinates();
    Coordinate C2= Order2.get_user().get_coordinates();
    double* c1= convert_to_meters(C1);
    double* c2= convert_to_meters(C2);
    double r1=Order1.get_distance();
    double r2=Order2.get_distance();
    double d= C1.get_distance(C2);
    if (d > r1+ r2){
        return std::vector<Coordinate>();}

    double a=(r1*r1-r2*r2+d*d)/(2*d);
    double h=sqrt(r1*r1-a*a);
    double b=d-a;
    double c3x= c1[0] + a*( c2[0] - c1[0] )/d;
    double c3y= c1[1] + a*( c2[1] - c1[1] )/d;
    double c4x = c3x + h*(c2[1] -c1[1]) /d;
    double c4y = c3y - h*( c2[0] - c1[0] )/d;
    double c5x = c3x - h*(c2[1] -c1[1]) /d;
    double c5y = c3y + h*( c2[0] - c1[0] )/d;
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
    Coordinate C1= Order1.get_user().get_coordinates();
    Coordinate C2= Order2.get_user().get_coordinates();
    double* c1= convert_to_meters(C1);
    double* c2= convert_to_meters(C2);
    double r1=Order1.get_distance();
    double r2=Order2.get_distance();
    double d= C1.get_distance(C2);
    if (d<=abs(r1-r2)){
        return true;}
    return false;
}


boolPoint check_if_bucket (std::vector <Order> order_vector)
    \\ Here I determine whether a bucket is valid by using for loops. Every time I take two initial orders, and calculate their intersections. Then,for each intersection I check
    \\ whether it is in every other circle. If it is, it means it is valid, and therefore I will return True and the adress, otherwise I continue, and finish by saying false and returning a 0 address.
    \\ I check whether the intersection is in every circle by comparing the sizes of a vector which contains all of the orders to a number to which I add one every time an order commprises an intersection.    
{
    struct boolPoint p3 = {Coordinate(), false};
    int count0=0;
    for (int i = 0; i < order_vector.size(); i++){
        Order order1 = order_vector[i];
        for (int j = i+1; j < order_vector.size(); j++){
            Order order2 = order_vector[j];
            std::vector <Coordinate> intersection_vector=get_intersection(order1, order2);
            if (intersection_vector.size()== 0 && !check_if_inside(order1, order2)){
                return p3;
            }
            if (intersection_vector.size()== 0 && check_if_inside(order1, order2)){
                count0++;
                continue;
            }
            Coordinate intersection1=intersection_vector[0];
            Coordinate intersection2=intersection_vector[1];
            int count1= 0;
            int count2=0;
            for (int k = 0; k < order_vector.size(); k++)
            {
                if (intersection1.get_distance(order_vector[k].get_user().get_coordinates()) <= order_vector[k].get_distance()){
                        count1++;}
                if (intersection2.get_distance(order_vector[k].get_user().get_coordinates()) <= order_vector[k].get_distance()){
                        count2++;}
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
