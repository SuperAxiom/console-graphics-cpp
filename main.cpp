#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>

using namespace std;

/*// Point in 3d
struct Point3d{
	float x, y, z;
};*/

Point3d createPoint3d(float x, float y, float z){
	Point3d result;

	result.x = x;
	result.y = y;
	result.z = z;

	return result;
}

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

// Function cheks if point is on sphere
bool isOnSphere(const Sphere& sp, const Point3d& point){
	float sum = (point.x - sp.center.x) * (point.x - sp.center.x);
	sum += (point.y - sp.center.y) * (point.y - sp.center.y);
	sum += (point.z - sp.center.z) * (point.z - sp.center.z);
	sum -= sp.radius * sp.radius;

	if (sum <= 0)
		return true;
	return false;
}

// Plane
struct Plane{
	float a, b, c, d;
};

// Functions creates Plane
Plane createPlane(float a, float b, float c, float d){
	Plane result;

	result.a = a;
	result.b = b;
	result.c = c;
	result.d = d;

	return result;
}

// Function returns point where line intersect plane
Point3d findIntersection(const Plane& plane, const Line3d& line){
	float t_num = plane.a * line.point.x;
	t_num += plane.b * line.point.y;
	t_num += plane.c * line.point.z;
	t_num += plane.d;

	float t_denum = plane.a * line.vector.coordinates.x;
	t_denum += plane.b * line.vector.coordinates.y;
	t_denum += plane.c * line.vector.coordinates.z;

	float t = -1 * (t_num / t_denum);

	float x = line.vector.coordinates.x * t + line.point.x;
	float y = line.vector.coordinates.y * t + line.point.y;
	float z = line.vector.coordinates.z * t + line.point.z;

	return createPoint3d(x, y, z);
}



struct ImagePlane{
	Plane plane;
	Point3d center;
};


void clearScreen(int ROWS, int COLUMNS){
	for(int j = 0; j < ROWS - 1; j++)
		for (int i = 0; i < COLUMNS; i++)
			cout << ' ';
	cout << endl;
}



// Size of terminal window
const int COLUMNS = 120;
const int ROWS = 36;

int main(){
	float ratio = (float)COLUMNS / ROWS;
	float pixelRatio = (float)11 / 22;

	// Surface to draw (contains all symbols)
	char surface[COLUMNS][ROWS];

	// Init surface as blank
	for(int i = 0; i < COLUMNS; i++)
		for(int j = 0; j < ROWS; j++)
			surface[i][j] = ' ';

	// Scene
	char scene[COLUMNS][ROWS][ROWS];

	// Init scene as blank
	for (int i = 0; i < COLUMNS; i++)
		for (int j = 0; j < ROWS; j++)
			for (int k = 0; k < ROWS; k++)
				scene[i][j][k] = ' ';


	// Clearing screen
	clearScreen(ROWS, COLUMNS);

	// Creating image plane (console in real world)
	ImagePlane imgPl;
	imgPl.plane = createPlane(0, 0, 1, 10);
	imgPl.center = createPoint3d(0, 0, -10);

	Sphere my_sphere;
	my_sphere.center.x = 0;
	my_sphere.center.y = 0;
	my_sphere.center.z = 0;
	my_sphere.radius = 5.0;

	// Adding sphere to the scene
	for (int i = 0; i < COLUMNS; i++){
		for (int j = 0; j < ROWS; j++){
			for (int k = 0; k < ROWS; k++){
				float x = (float)i / COLUMNS * 20 - 10;
				x *= ratio * pixelRatio;
				float y = (float)j / ROWS * 20 - 10;
				y *= -1;
				float z = (float)k / ROWS * 20 - 10;
				if (isOnSphere(my_sphere, createPoint3d(x, y, z)))
					scene[i][j][k] = '1';
			}
		}
	}


	// Drawing sphere
	for (int t = 0; t <= 1000000000; t++){
		Point3d camera;
		camera = createPoint3d(imgPl.center.x, imgPl.center.y, imgPl.center.z - 5);

		for (int i = 0; i < COLUMNS; i++){
			for (int j = 0; j < ROWS; j++){
				for (int k = 0; k < ROWS; k++){
					if (scene[i][j][k] == '1'){
						float x = (float)i / COLUMNS * 20 - 10;
						x *= ratio * pixelRatio;
						float y = (float)j / ROWS * 20 - 10;
						y *= -1;
						float z = (float)k / ROWS * 20 - 10;

						Line3d ray = createLine(camera, createPoint3d(x, y, z));
						Point3d intersection = findIntersection(imgPl.plane, ray);
						Point3d imagePoint;

						imagePoint.x = intersection.x / (ratio * pixelRatio);
						imagePoint.x += 10;
						imagePoint.x *= (float)COLUMNS / 20;
						imagePoint.y = intersection.y + 10;
						imagePoint.y *= (float)ROWS / 20;

						if (imagePoint.x < COLUMNS && imagePoint.y >= 0){
							if(imagePoint.y < ROWS && imagePoint.y >= 0){
								int i = (int)imagePoint.x;
								int j = (int)imagePoint.y;
								surface[i][j] = '@';
							}
						}
					}
				}
			}
		}

		// Displaying
		for(int y = 0; y < ROWS; y++){
			for(int x = 0; x < COLUMNS; x++){
				cout << surface[x][y];
			}
		}

		// Move imgage plane

	}

	return 0;
}
