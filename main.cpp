#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>

using namespace std;

// Point in 3d
struct Point3d{
	float x, y, z;
};


// Vector in 3d
struct Vector3d{
	Point3d coordinates;
	float length;
};

// Function creates vector by 2 points
Vector3d createVector(Point3d start, Point3d end){
	Vector3d result;

	result.coordinates.x = end.x - start.x;
	result.coordinates.y = end.y - start.y;
	result.coordinates.z = end.z - start.z;

	float squares = result.coordinates.x * result.coordinates.x;
	squares += result.coordinates.y * result.coordinates.y;
	squares += result.coordinates.z * result.coordinates.z;
	result.length = sqrt(squares);

	return result;
}

// Function returns norm vector
Vector3d norm(const Vector3d& vector){
	Vector3d result;

	result.length = 1.0;
	result.coordinates.x = vector.coordinates.x / vector.length;
	result.coordinates.y = vector.coordinates.y / vector.length;
	result.coordinates.z = vector.coordinates.z / vector.length;

	return result;

}


// Equation of line in 3d
struct Line3d{
	Point3d point;
	Vector3d vector;
};

// Function that creates Line3d through 2 points
Line3d createLine(Point3d point1, Point3d point2){
	Line3d result;
	Vector3d vector;

	vector = createVector(point1, point2);

	result.point = point1;
	result.vector = vector;

	return result;
}

// Function creates Line3d by point and vector
Line3d createLine(Point3d point, Vector3d vector){
	Line3d result;

	result.point = point;
	result.vector = vector;

	return result;
}

// Function checks if point is on the line
bool isOnLine(const Line3d& line, const Point3d& point){
	float first = (point.x - line.point.x) / line.vector.coordinates.x;
	float second = (point.y - line.point.y) / line.vector.coordinates.y;
	float third = (point.z - line.point.z) / line.vector.coordinates.z;

	if (first == second && second == third)
		return true;
	return false;
}


// Sphere
struct Sphere{
	Point3d center;
	float radius;
};

// Function checks if line is interseting sphere
bool isIntersect(Line3d line, Sphere sp){
	// Init vars
	// Line's params
	float p1 = line.vector.coordinates.x;
	float p2 = line.vector.coordinates.y;
	float p3 = line.vector.coordinates.z;
	float x0 = line.point.x;
	float y0 = line.point.y;
	float z0 = line.point.z;

	// Sphere's params
	float x01 = sp.center.x;
	float y01 = sp.center.y;
	float z01 = sp.center.z;
	float r = sp.radius;

	// Find params for discriminant
	float a = (p1 * p1) + (p2 * p2) + (p3 * p3);
	float b = 2 * (p1 * (x0 - x01) + p2 * (y0 -y01) + p3 * (z0 -z01));
	float c = (x0 -x01) * (x0 - x01);
	c += (y0 - y01) * (y0 - y01);
	c += (z0 -z01) * (z0 - z01);
	c -= r * r;

	// Find discriminant
	float d = b * b - 4 * a * c;

	// If there is real solution then they are intersected
	if (d < 0)
		return false;
	return true;
}


void clearScreen(int ROWS, int COLUMNS){
	for(int j = 0; j < ROWS; j++)
		for (int i = 0; i < COLUMNS; i++)
			cout << ' ';
}

// Size of terminal window
const int COLUMNS = 120;
const int ROWS = 36;

int main(){
	float ratio = (float)COLUMNS / ROWS;
	float pixelRatio = (float)11 / 22;

	// Surface to draw (contains all symbols)
	char surface[COLUMNS][ROWS];

	// Clearing screen
	clearScreen(ROWS, COLUMNS);


	// Init camera
	Point3d camera;
	camera.x = -10;
	camera.y = 0;
	camera.z = -15;

	Sphere my_sphere;
	my_sphere.center.x = 0;
	my_sphere.center.y = 0;
	my_sphere.center.z = 0;
	my_sphere.radius = 8.0;

	// Drawing sphere
	for(int t = 0; t <= 360; t++){
		for(int i = 0; i < COLUMNS; i++){
			for(int j = 0; j < ROWS; j++){
				Point3d point0;
				point0.x = 0;
				point0.y = 0;
				point0.z = -5;

				Point3d point1;
				point1.x = (float)i / COLUMNS * 20.0 - 10.0;
				point1.x *= ratio * pixelRatio;
				point1.y = (float)j / ROWS * 20.0 - 10.0;
				point1.y *= -1;
				point1.z = 5.0;

				Vector3d vector;
				vector = createVector(point0, point1);
				vector = norm(vector);

				Line3d ray = createLine(camera, vector);

				if (isIntersect(ray, my_sphere))
					surface[i][j] = '@';
				else
					surface[i][j] = ' ';
			}
		}

		// Displaying
		for(int y = 0; y < ROWS; y++){
			for(int x = 0; x < COLUMNS; x++){
				cout << surface[x][y];
			}
		}

		// Move sphere
		//camera.x = 150 * sin(t);
		//camera.z = 150 * cos(t);
		//camera.z -= 1;
		camera.x += 1;
		if (camera.x == 11)
			camera.x = -10;

		this_thread::sleep_for(chrono::milliseconds(200));
		clearScreen(ROWS, COLUMNS);
	}

	return 0;
}
