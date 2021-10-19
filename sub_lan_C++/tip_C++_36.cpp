class Shape
{
public:
	enum ShapeColor { Red, Green, Blue };
	virtual void draw(ShapeColor color = Red) const = 0;
	...
};

class Rectangle: public ShapeColor{
public:
	virtual void draw(ShapeColor color = Green) const;
	...
};

class Circle: public ShapeColor{
public:
	virtual void draw(ShapeColor color) const;
	...
};

int main()
{
	Shape *ps;														// 정적 타입은 Shape*
	Shape *pc = new Circle;											// 정적 타입은 Shape*
	Shape *pr = new Rectangle;										// 정적 타입은 Shape*

	ps = pc;														// ps의 동적 타입은 Circle*
	ps = pr;														// ps의 동적 타입은 Rectangle*

	pc->draw(Shape::Red);											// Circle::draw(Shape::Red)를 호출한다.
	pr->draw();														// Rectangle::draw(Shape::Red)를 호출한다!
																	// Green이 아닌 이유는 default인자는 정적으로 바인딩 되기 때문이다.
	return 0;
}

// 비가상 함수는 정적 바인딩으로 묶인다!
// 가상 함수는 동적 바인딩으로 묶인다!
// 하지만 가상함수의 매개변수 중 default 매개변수는 정적 바인딩으로 묶인다! <- 효율 때문에

// 해결법(NVI 관용구)
class Shape
{
public:
	enum ShapeColor { Red, Green, Blue };
	void draw(ShapeColor color = Red) const							// 비가상 함수는 파생 클래스에서 오버라이드 되면 안되기 때문에 이렇게 설계하면
	{																// draw 함수의 default color 매개변수를 Red로 고정시킬 수 있다.
		doDraw(color);
	}
private:
	virtual void doDraw(ShapeColor color) const = 0;
};

class Rectangle: public ShapeColor{
public:
	...
private:
	virtual void doDraw(ShapeColor color) const;
	...
};