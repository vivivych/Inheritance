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

	class Point
	{
		int x;
		int y;
	public:
		void set_x(int x)
		{
			this->x = x;
		}
		void set_y(int y)
		{
			this->y = y;
		}
		double get_x() const
		{
			return x;
		}
		double get_y() const
		{
			return y;
		}

	};
	class Shape
	{
		static const int MIN_START_X = 100;
		static const int MIN_START_Y = 100;
		static const int MAX_START_X = 800;
		static const int MAX_START_Y = 600;
		static const int MIN_LINE_WIDTH = 1;
		static const int MAX_LINE_WIDTH = 32;
		static const int MIN_SIZE = 32;
		static const int MAX_SIZE = 800;
	protected:
		int start_x;
		int start_y;
		int line_width;
		Color color; 
	public:
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
		virtual double get_area()const = 0;
		virtual double get_perimeter() const = 0;
		virtual void draw() const = 0;
		Shape(SHAPE_TAKE_PARAMETERS) : color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
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
			this->side_1 = side_1;
		}
		void set_side_2(double side_2)
		{
			this->side_2 = side_2;
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
		void draw() const override
		{

			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd); 
			
			HPEN hPen = CreatePen(PS_SOLID, line_width, color); 
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Rectangle(hdc, start_x, start_y, start_x + side_1, start_y + side_2);

			DeleteObject(hPen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc);

		}
		Rectangle(double side_1, double side_2, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_side_1(side_1);
			set_side_2(side_2);
		}
		void info() const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Side 1: " << get_side_1() << endl;
			cout << "Side 2: " << get_side_2() << endl;
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
			this->radius = radius;
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
		void draw() const override
		{
	
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd); 
		
			HPEN hPen = CreatePen(PS_SOLID, line_width, color); 
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Ellipse(hdc, start_x, start_y, start_x + radius, start_y + radius);

			DeleteObject(hPen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc);
		}
		Circle(double radius, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_radius(radius);
		}
		void info() const override
		{
			cout << typeid(*this).name() << endl;
			cout << "radius: " << get_radius() << endl;
			Shape::info();
		}
	};
	class Triangle :public Shape
	{
		int point1_x;
		int point1_y;
		int point2_x;
		int point2_y;
		int point3_x;
		int point3_y;
	public:
		void set_point1_x(int point1_x)
		{
			this->point1_x = point1_x;
		}
		void set_point1_y(int point1_y)
		{
			this->point1_y = point1_y;
		}
		void set_point2_x(int point2_x)
		{
			this->point2_x = point2_x;
		}
		void set_point2_y(int point2_y)
		{
			this->point2_y = point2_y;
		}
		void set_point3_x(int point3_x)
		{
			this->point3_x = point3_x;
		}
		void set_point3_y(int point3_y)
		{
			this->point3_y = point3_y;
		}

		int get_point1_x() const
		{
			return point1_x;
		}
		int get_point1_y() const
		{
			return point1_y;
		}
		int get_point2_x() const
		{
			return point2_x;
		}
		int get_point2_y() const
		{
			return point2_y;
		}
		int get_point3_x() const
		{
			return point3_x;
		}
		int get_point3_y() const
		{
			return point3_y;
		}

		double get_area() const override
		{
		
			double s12 = sqrt((point1_x - point2_x) * (point1_x - point2_x) + (point1_y - point2_y) * (point1_y - point2_y));
			double s23 = sqrt((point2_x - point3_x) * (point2_x - point3_x) + (point2_y - point3_y) * (point2_y - point3_y));
			double s13 = sqrt((point1_x - point3_x) * (point1_x - point3_x) + (point1_y - point3_y) * (point1_y - point3_y));

			double hp = (s12 + s23 + s13) / 2;

			return sqrt(hp * (hp - s12) * (hp - s23) * (hp - s13));
		}
		double get_perimeter() const override
		{
		
			double s12 = sqrt((point1_x - point2_x) * (point1_x - point2_x) + (point1_y - point2_y) * (point1_y - point2_y));
			double s23 = sqrt((point2_x - point3_x) * (point2_x - point3_x) + (point2_y - point3_y) * (point2_y - point3_y));
			double s13 = sqrt((point1_x - point3_x) * (point1_x - point3_x) + (point1_y - point3_y) * (point1_y - point3_y));

			return (s12 + s23 + s13);
		}
		void draw() const override
		{
			
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd); 
			
			HPEN hPen = CreatePen(PS_SOLID, line_width, color); 
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			DeleteObject(hPen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc);
		}
		Triangle(int point1_x, int point1_y, int point2_x, int point2_y, int point3_x, int point3_y, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_point1_x(point1_x);
			set_point1_y(point1_y);
			set_point2_x(point2_x);
			set_point2_y(point2_y);
			set_point3_x(point3_x);
			set_point3_y(point3_y);
		}
		void info() const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Point1: " << get_point1_x() << " " << get_point1_y() << endl;
			cout << "Point2: " << get_point2_x() << " " << get_point2_y() << endl;
			cout << "Point3: " << get_point3_x() << " " << get_point3_y() << endl;
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
	Geometry::Triangle triangle(700, 500, 730, 500, 720, 520, 0, 0, 3, Geometry::Color::Violet);
	triangle.info();
}