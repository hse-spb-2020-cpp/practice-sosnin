#include <iostream>
#include <string>
#include <vector>

namespace hse::cpp {

struct Point3D final {
    double x;
    int a;
    double y;
    bool b;
    int c;
    double z;
};

}  // namespace hse::cpp
int main() {
    using namespace hse::cpp;

    std::cout << "sizeof(Point3D) = " << sizeof(Point3D) << std::endl;
    std::cout << "alignof(Point3D) = " << alignof(Point3D) << std::endl;

    alignas(alignof(Point3D)) char aligned_buffer[sizeof(Point3D)];
    std::cout << "std::size(aligned_buffer) = " << std::size(aligned_buffer)
              << std::endl;

    std::cout << "&aligned_buffer = " << &aligned_buffer << std::endl;

    Point3D *ptr = new (&aligned_buffer) Point3D;
    std::cout << "ptr = " << ptr << std::endl;
    ptr->x = 3.14;
    ptr->y = 2.71;
    ptr->z = 42;

    Point3D &point = reinterpret_cast<Point3D &>(aligned_buffer);
    std::cout << "ptr_cast = " << &point << std::endl;
    std::cout << "point = {" << point.x << "; " << point.y << "; " << point.z
              << "}" << std::endl;

    point.~Point3D();
}
