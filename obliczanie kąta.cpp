#define M_PI        3.14159265358979323846
#include <cmath>
#include <iostream>

struct Vector {

    double x;
    double y;

};

int main() {

    Vector position;
    double angle;

    std::cin >> position.x;
    std::cin >> position.y;
    std::cout << "position: " << position.x << " " << position.y << std::endl;

    Vector destination;
    std::cin >> destination.x;
    std::cin >> destination.y;
    std::cout << "destination: " << destination.x << " " << destination.y << std::endl;

    double scalar = position.x * destination.x + position.y * destination.y;
    double positionlength = sqrt(pow(position.x, 2) + pow(position.y, 2));
    double destinationlength = sqrt(pow(destination.x, 2) + pow(destination.y, 2));
    double cosinus = scalar / (positionlength * destinationlength);


	if ( destination.y < 0)  angle = 360 - acos(cosinus) * 180 / M_PI;
    else angle = acos(cosinus) * 180 / M_PI;

    std::cout << "scalar: " << scalar << std::endl;
    std::cout << "positionlength: " << positionlength << std::endl;
    std::cout << "destinationlength: " << destinationlength << std::endl;
    std::cout << "cosinus: " << cosinus << std::endl;
    std::cout << "angle: " << angle << std::endl;

return 0;

}
