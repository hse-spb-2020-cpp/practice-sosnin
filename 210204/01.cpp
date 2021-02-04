#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <vector>

namespace hse::cpp {

class Shape {
public:
    virtual ~Shape() = default;
    virtual const char *type_name() = 0;
    virtual float area() = 0;
};

class Circle : virtual public Shape {
public:
    Circle(float radius) : radius_(radius) {
    }

    const char *type_name() override {
        return typeid(Circle).name();
    }

    float area() override {
        return M_PI * radius_ * radius_;
    }

public:
    float radius_;
};

class Square : virtual public Shape {
public:
    Square(float side_length) : side_length_(side_length) {
    }

    const char *type_name() override {
        return typeid(Square).name();
    }

    float area() override {
        return side_length_ * side_length_;
    }

public:
    float side_length_;
};

class Rectangle final : public Shape {
public:
    Rectangle(float width, float height) : width_(width), height_(height) {
    }

    const char *type_name() override {
        return typeid(Rectangle).name();
    }

    float area() override {
        return width_ * height_;
    }

public:
    float width_;
    float height_;
};

class CircleSquare final : public Circle, public Square {
public:
    CircleSquare(float side, float radius) : Circle(radius), Square(side) {
    }

    const char *type_name() override {
        return typeid(CircleSquare).name();
    }

    float area() override {
        return Square::area() - Circle::area();
    }

    std::unique_ptr<CircleSquare> clone() {
        return std::make_unique<CircleSquare>(side_length_, radius_);
    }
};

enum class Type { kCircle, kSquare, kRectangle };

std::unique_ptr<Shape> create_shape(Type type,
                                    float width,
                                    float height = 0.f) {
    if (type == Type::kCircle) {
        return std::make_unique<Circle>(width);
    } else if (type == Type::kSquare) {
        return std::make_unique<Square>(width);
    } else if (type == Type::kRectangle) {
        return std::make_unique<Rectangle>(width, height);
    }

    assert(false && "Unregistered shape type");
    return nullptr;
}

// --- Header ---
class Printer {
public:
    explicit Printer(const std::string &meta);
    ~Printer();
    void pretty_print(Shape *shape);

private:
    struct Impl;
    std::unique_ptr<Impl> pimpl_;
};
// --- Header end---

// --- CPP ---
struct Printer::Impl {
    std::string meta;
};

Printer::Printer(const std::string &meta) : pimpl_(std::make_unique<Impl>()) {
    pimpl_->meta = meta;
}

Printer::~Printer() = default;

void Printer::pretty_print(Shape *shape) {
    std::cout << pimpl_->meta << std::endl;
    if (auto p = dynamic_cast<Circle *>(shape)) {
        std::cout << "Circle with radius " << p->radius_;
    }
    if (auto p = dynamic_cast<Square *>(shape)) {
        std::cout << "Square with side " << p->side_length_;
    }
    if (auto p = dynamic_cast<Rectangle *>(shape)) {
        std::cout << "Rectangle with width " << p->width_ << " and height "
                  << p->height_;
    }
    std::cout << " and area " << shape->area() << std::endl;
    std::cout << "Object type name " << shape->type_name() << std::endl;
}
// --- CPP end ---

}  // namespace hse::cpp

int main() {
    using namespace hse::cpp;
    std::vector<std::unique_ptr<Shape>> shapes;

    std::map<size_t, Type> type_names{
        {typeid(Circle).hash_code(), Type::kCircle},
        {typeid(Square).hash_code(), Type::kSquare},
        {typeid(Rectangle).hash_code(), Type::kRectangle},
    };

    shapes.emplace_back(
        create_shape(type_names[typeid(Circle).hash_code()], 3.14));
    shapes.emplace_back(
        create_shape(type_names[typeid(Square).hash_code()], 2.71));
    shapes.emplace_back(
        create_shape(type_names[typeid(Rectangle).hash_code()], 42, 28));

    Printer printer("Shape info:");
    for (const auto &s : shapes) {
        printer.pretty_print(s.get());
    }
}