#include <iostream>
#include<algorithm>

using namespace std;

struct Vector2 {
	float x=0;
	float y=0;

	void print() {
		printf("[%.1f; %.1f]\n", x, y);
	}
	void set(float x, float y) {
		this->x = x;
		this->y = y;
	}
	/*bool operator>(Vector2 v) const {
		if ((x > v.x && y >= v.y) || (x >= v.x && y > v.y))
			return true;
	}*/
};

struct Rectangle {
	Vector2 A, B, C, D;
	Vector2 * points[4]={&A, &B, &C, &D};
	float minX =0, maxX=0, minY=0, maxY=0;

	Rectangle(){}
	Rectangle(const char name[]) {
		cout << "Create rectangle "<<name<<"\n";
		cout << "Ax = ";
		cin >> A.x;
		cout << "Ay = ";
		cin >> A.y;
		cout << "A"; A.print();
		cout << "Bx = ";
		cin >> B.x;
		if (B.x != A.x) {
			B.y = A.y;
			C.x = B.x;
			cout << "B"; B.print();
			cout << "Cx = " << C.x << endl;
			cout << "Cy = ";
			cin >> C.y;
			cout << "C"; C.print();
			D.set(A.x, C.y);
			cout << "D";
			D.print();
		}
		else {
			cout << "By = ";
			cin >> B.y;
			cout << "B"; B.print();
			C.y = B.y;
			cout << "Cx = ";
			cin >> C.x;
			cout << "C"; C.print();
			D.set(C.x, A.y);
			cout << "D";
			D.print();
		}

		minX = min({ A.x, B.x, C.x, D.x });
		minY = min({ A.y, B.y, C.y, D.y });
		maxX = max({ A.x, B.x, C.x, D.x });
		maxY = max({ A.y, B.y, C.y, D.y });
		
	}

	bool isInside(Vector2 v) {
		return (v.x >= minX && v.x <= maxX && v.y >= minY && v.y <= maxY);
	}
	void print() {
		cout << "A"; A.print();
		cout << "B"; B.print();
		cout << "C"; C.print();
		cout << "D"; D.print();
		cout << endl;
	}
};

void Collide(Rectangle rec1, Rectangle rec2) {
	Rectangle rect = Rectangle();
	bool collided = false;
	for (Vector2* p : rec1.points)
		if (rec2.isInside(*p)) {
			collided = true;
			rect.A = *p;
		}
	for (Vector2* p : rec2.points)
		if (rec1.isInside(*p)) {
			collided = true;
			rect.C = *p;
		}
	if (collided) {
		rect.B.set(rect.A.x, rect.C.y);
		rect.D.set(rect.C.x, rect.A.y);
		cout << "The Collision result of the two Rectangle has four vertices:\n";
		rect.print();
	}
	else
		cout << "The two Rectangle have no collision!";
}

int main()
{
	
	Collide(Rectangle("2"), Rectangle("1"));
}

/*b = am + d - cm
b=d+m(a-c)
=>m = (b-d)/(a-c)
n = d-cm
y = mx + n

m = (Ay - By)/(Ax - Bx)
n = By - Bx*m

*/