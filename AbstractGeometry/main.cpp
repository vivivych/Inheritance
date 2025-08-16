#include<iostream>
using namespace std;

enum Color  //enumeration (перечисление в €зыке C. ѕредставл€ет собой набор констант типа int. ѕеречислени€ из других типов создать невозможно (в C++)
{
	Red    = 0x000000FF,
	Green  = 0x0000FF00,
	Blue   = 0x00FF0000,
	Yellow = 0x0000FFFF,
	Purple = 0x00FF00FF,

};
//ѕо умолчанию константам перечислени€ присваиваютс€ 0,1,2... и тд.  аждой константе нужно присвоить свое значение
// ≈сли какой-то константе в начале или в середине присвоить конкретное значение, то это значение станет отправной точкой дл€ последующих констант.
//ѕеречислени€ также как структура или класс €вл€етс€ пользовательским типом данных. ѕеременные которого могут принимать строго определенные значени€, описанные в перечислении. 
class Shape
{
	Color color; //÷вет фигуры

public:
	void set_color(Color color)
	{
		this->color = color;
	}

	Color get_color()const
	{
		return color;
	}
	virtual double get_area()const = 0;
	virtual double get_perimeter()const = 0;
	virtual void draw()const = 0;
	Shape(Color color) :color(color) {}

	virtual void info()const
	{
		cout << "ѕлощадь фигуры: " << get_area() << endl;
		cout << "ѕериметр фигуры: " << get_perimeter() << endl;
		draw();
	}

};

class Square : public Shape
{
	double side;
public:

	void set_side(double side)
	{
		this->side = side;
	}
	double get_side()const
	{
		return side;
	}
	double get_area()const
	{
		return side * side;
	}
	double get_perimeter()const override
	{
		return side * 4;
    }

	void draw()const override
	{
		for (int i = 0; i < side; i++)
		{
			for (int j = 0; j < side; j++)
			{
				cout << "* ";
			}
			cout << endl;
		}
	}

	Square(double side, Color color) :Shape(color)
	{

		set_side(side);
	}

	void info()const override
	{
		cout << typeid(*this).name() << endl;
		cout << "—торона квадрата: " << get_side() << endl;
		Shape::info();
	}
};

void main()
{
	setlocale(LC_ALL, "");

	Square square(5, Color::Red);
	square.info();

}