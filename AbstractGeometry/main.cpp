#include <iostream>
using namespace std;
#include<Windows.h>

namespace Geometry
{
	enum Color //enumeration, перечесления. набор констант типа int
	{
		Red = 0x000000FF,
		Green = 0x0000FF00,
		Blue = 0x00FF0000,
		Yellow = 0x0000FFFF,
		Violet = 0x00FF00FF
	};

#define SHAPE_TAKE_PARAMETERS int start_x, int start_y, int line_width, Color color
#define SHAPE_GIVE_PARAMETERS  start_x,  start_y,  line_width,  color
#define PI 3.14159265358979323846

	class Shape
	{
	
	protected:
		int start_x;
		int start_y;
		int line_width;
		Color color; 
		HDC hdc;
		HPEN hPen;
		HBRUSH hBrush;
	public:
		static const int MIN_START_X = 100;
		static const int MIN_START_Y = 100;
		static const int MAX_START_X = 800;
		static const int MAX_START_Y = 600;
		static const int MIN_LINE_WIDTH = 1;
		static const int MAX_LINE_WIDTH = 32;
		static const int MIN_SIZE = 32;
		static const int MAX_SIZE = 800;

		void set_start_x(int start_x)
		{
			this->start_x =
				start_x < MIN_START_X ? MIN_START_X :
				start_x > MAX_START_X ? MAX_START_X :
				start_x;
		}
		void set_start_y(int start_y)
		{
			this->start_y =
				start_y < MIN_START_Y ? MIN_START_Y :
				start_y > MAX_START_Y ? MAX_START_Y :
				start_y;
		}
		void set_line_width(int line_width)
		{
			this->line_width =
				line_width < MIN_LINE_WIDTH ? MIN_LINE_WIDTH :
				line_width > MAX_LINE_WIDTH ? MAX_LINE_WIDTH :
				line_width;
		}
		void set_color(Color color)
		{
			this->color = color;
		}
		int filter_size(int size) const
		{
			return size < MIN_SIZE ? MIN_SIZE :
				size > MAX_SIZE ? MAX_SIZE :
				size;
		}
		double get_start_x() const
		{
			return start_x;
		}
		double get_start_y() const
		{
			return start_y;
		}
		double get_line_width() const
		{
			return line_width;
		}
		Color get_color() const
		{
			return color;
		}

		Shape(SHAPE_TAKE_PARAMETERS) : color(color)

		{
			hdc = GetDC(GetDesktopWindow());
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);

			hPen = CreatePen(PS_SOLID, line_width, color);
			hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
		}
		~Shape()
		{
			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(GetDesktopWindow(), hdc);
		}
		virtual double get_area()const = 0;
		virtual double get_perimeter() const = 0;
		virtual void draw() const = 0;
	
		virtual void info() const
		{
			cout << "Площадь фигуры : " << get_area() << endl;
			cout << "Периметр фигуры : " << get_perimeter() << endl;
			draw();
		}

	};
	
	class Rectangle :public Shape
	{
		double side_1;
		double side_2;
	public:
		void set_side_1(double side_1)
		{
			this->side_1 = filter_size(side_1);
		}
		void set_side_2(double side_2)
		{
			this->side_2 = filter_size(side_2);
		}
		double get_side_1() const
		{
			return side_1;
		}
		double get_side_2() const
		{
			return side_2;
		}
		double get_area() const override
		{
			return side_1 * side_2;
		}
		double get_perimeter() const override
		{
			return (side_1 + side_2) * 2;
		}

		Rectangle(double side_1, double side_2, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_side_1(side_1);
			set_side_2(side_2);
		}
		void draw() const override
		{
			::Rectangle(hdc, start_x, start_y, start_x + side_1, start_y + side_2);
		}
		
		void info() const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона 1: " << get_side_1() << endl;
			cout << "Сторона 2: " << get_side_2() << endl;
			Shape::info();
		}

	};
	class Square : public Rectangle
	{
	public:
		Square(double side, SHAPE_TAKE_PARAMETERS) : Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}
	};
	class Circle :public Shape
	{
		double radius;
	public:
		void set_radius(double radius)
		{
			this->radius = filter_size(radius);
		}
		double get_radius() const
		{
			return radius;
		}
		double get_area() const override
		{
			return PI * radius * radius;
		}
		double get_perimeter() const override
		{
			return 2 * PI * radius;
		}
		Circle(double radius, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_radius(radius);
		}
		void draw() const override
		{
			::Ellipse(hdc, start_x, start_y, start_x + radius, start_y + radius);
		}
		
		void info() const override
		{
			cout << typeid(*this).name() << endl;
			cout << "radius: " << get_radius() << endl;
			Shape::info();
		}
	};

	class Triangle : public Shape
	{
	public:
		Triangle(SHAPE_TAKE_PARAMETERS) : Shape(SHAPE_GIVE_PARAMETERS) {}

		virtual double get_height() const = 0;
	};

	class EquilateralTriangle : public Triangle
	{
	private:
		double side;

	public:
		
		void set_side(double side)
		{
			this->side = filter_size(side);
		}
		double get_side() const
		{
			return side;
		}
		double get_height() const override
		{
			return sqrt(pow(side, 2) - pow(side, 2) / 2);
		}
		double get_area() const override
		{
			return side * get_height() / 2;
		}
		double get_perimeter() const override
		{
			return side * 3;
		}

		EquilateralTriangle(double side, SHAPE_TAKE_PARAMETERS) : Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}
		void draw() const override
		{
			const POINT vertices[] =
			{
				{ start_x, start_y + get_height() },
				{ start_x + side, start_y + get_height() },
				{ start_x + side / 2, start_y }
			};

			::Polygon(hdc, vertices, 3);
		}
		void info() const override
		{
			cout << typeid(*this).name() << endl;
			cout << "сторона: " << get_side() << endl;
			Shape::info();
		}

	};

}


void main()
{
	setlocale(LC_ALL, "");
	Geometry::Square square(50, 100, 500, 5, Geometry::Color::Green);
	square.info();
	Geometry::Rectangle rectangle(70, 20, 300, 500, 7, Geometry::Color::Red);
	rectangle.info();
	Geometry::Circle circle(75, 500, 500, 3, Geometry::Color::Yellow);
	circle.info();
	Geometry::EquilateralTriangle triangle(80, 500, 350, 1, Geometry::Color::Violet);
	triangle.info();

	while (true)
	{
		square.draw();
		rectangle.draw();
		circle.draw();
		triangle.draw();

	}
}
