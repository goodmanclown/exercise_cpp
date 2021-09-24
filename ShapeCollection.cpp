#define _USE_MATH_DEFINES
#include <cmath>
#include <exception>
#include <limits>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

int main()
{
    // longest name of a polygon has 21 characters
    static const uint MAX_LENGTH_NAME = 21;

    // the maximum length of the side of a square the area of which can be represented 
    // with a double
	static const double MAX_LENGTH_SIDE = sqrt(numeric_limits<double>::max());

    // the maximum length of the radius of a circle the area of which can be represented 
    // with a double
	static const double MAX_LENGTH_RADIUS = sqrt(numeric_limits<double>::max() / M_PI);

    /**
     * a Shape base class with GetArea() and GetName() methods
     */
	class Shape
    {
    public:

        /**
         * @param name - name of the shape represented, cap the length of the string to 
         *               that of a valid name of a polygon
         */
        Shape(const string& name):mName(name.substr(0, MAX_LENGTH_NAME)) {};

        // do not allow calling the empty constructor
		Shape() = delete;

		virtual ~Shape() = default;

        /**
         * @return a string representing the name of the shape
         */
		string GetName() const { return mName; };

        /**
         * @return a double representing the area of the shape
         */
		virtual double GetArea() const = 0;

	private:

        // name of shape
		string mName;
	};
    using ShapePtr = unique_ptr<Shape>;

    /**
     * a Square class derived from Shape with a default side length of 2
     */
	class Square : public Shape
	{
	public:

        /**
         * @param sidelength - length of the side of the square represented.  must be > 0.0
         */
		Square(double sidelength) : Shape("Square")
        {
            if (sidelength <= 0.0)
            {
                // I'm not a fan of exception.  This is just showing the possibility
                // of using exception to handle error condition
                throw out_of_range("length must be greater than 0");
            }

            mSideLength = sidelength;
        }

		Square() : Shape("Square") {};

		virtual ~Square() = default;

        /**
         * @return a double representing the area of a square.  -1 if area out of range
         */
		double GetArea() const override
		{
			if (mSideLength > MAX_LENGTH_SIDE)
			{
				return -1.0;
			}

			return mSideLength * mSideLength;
		}

	private:

        // length of one side of a square
		double mSideLength = 2.0;
	};

    /**
     * a Circle class derived from Shape with a default radius of 2
     */
	class Circle : public Shape
	{
	public:

        /**
         * @param radius - radius of the circle represented.  must be > 0.0
         */
		Circle(double radius) : Shape("Circle")
        {
            if (radius <= 0.0)
            {
                throw out_of_range("radius must be greater than 0");
            }

            mRadiusLength = radius;
        }

		Circle() : Shape("Circle") {};

		virtual ~Circle() = default;

        /**
         * @return a double representing the area of a circle.  -1 if area out of range
         */
		double GetArea() const override
		{
			if (mRadiusLength > MAX_LENGTH_RADIUS)
			{
				return -1.0;
			}

            return M_PI * mRadiusLength * mRadiusLength;
		}

    private:

        // length of the radius of a circle
		double mRadiusLength = 2.0;
	};


	vector<ShapePtr> vShape;
    vShape.reserve(11); 
	vShape.emplace_back(new Square());
	vShape.emplace_back(new Circle());
	vShape.emplace_back(new Square(10));
	vShape.emplace_back(new Circle(400));

    try
    {
	    vShape.emplace_back(new Square(0));
    }
    catch(const exception& ex)
    {
        cerr << "Exception caught: " << ex.what() << endl;
    }

    try
    {
	    vShape.emplace_back(new Square(-1));
    }
    catch (const exception& ex)
    {
        cerr << "Exception caught: " << ex.what() << endl;
    }

    try
    {
	    vShape.emplace_back(new Circle(0));
    }
    catch (const exception& ex)
    {
        cerr << "Exception caught: " << ex.what() << endl;
    }
    
    try
    {
	    vShape.emplace_back(new Circle(-1));
    }
    catch (const exception& ex)
    {
        cerr << "Exception caught: " << ex.what() << endl;
    }
    
    vShape.emplace_back(nullptr);
	vShape.emplace_back(new Square(0.9));
	vShape.emplace_back(new Circle(100000.12313));
	vShape.emplace_back(new Square(numeric_limits<double>::max()));
	vShape.emplace_back(new Circle(numeric_limits<double>::max()));
	vShape.emplace_back(new Square(sqrt(numeric_limits<double>::max())));
	vShape.emplace_back(new Circle(sqrt(numeric_limits<double>::max() / M_PI)));

	cout << "This container has the following shapes and corresponding area: " << endl;
	for (const auto& entry : vShape)
	{
        if (entry == nullptr)
        {
			cerr << "null pointer encountered" << endl;
            continue;
        }

		auto area = entry->GetArea();
		if (area > 0.0)
		{
			cout << "name: " << entry->GetName() << ", area: " << area << endl;
		}
		else
		{
			cerr << "name: " << entry->GetName() << " area exceeds limit" << endl;
		}
	}

    return 0;
}