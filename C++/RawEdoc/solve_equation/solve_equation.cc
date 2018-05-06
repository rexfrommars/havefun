#include <ostream>
#include <iostream>

// TODO see more about linear-algebra and matrix

using namespace std;

struct Row
{
	int64_t x, y, z, c;

	Row(int const (&row) [4]): x(row[0]), y(row[1]), z(row[2]), c(row[3]) {}
	Row(int64_t const (&row) [4]): x(row[0]), y(row[1]), z(row[2]), c(row[3]) {}

	const Row operator* (int p) const
	{
		return Row({x * p, y * p, z * p, c * p});
	}

	const Row operator- (const Row& r) const
	{
		return Row({x - r.x, y - r.y, z - r.z, c - r.c});
	}
};

void swap(Row& a, Row& b)
{
	swap(a.x, b.x);
	swap(a.y, b.y);
	swap(a.z, b.z);
	swap(a.c, b.c);
}

ostream& operator << (ostream& os, const Row& row)
{
	return os << row.x << ", " << row.y << ", " << row.z << ", " << row.c << ", ";
}

int* solveEq(int eq[3][4]){
	Row r0 = eq[0];
	Row r1 = eq[1];
	Row r2 = eq[2];
	cout << r0 << endl << r1 << endl << r2 << endl << "~~~~" << endl;

	//
	if (r0.z == 0) {
		if (r1.z != 0) { swap(r0, r1); }
		else if (r2.z != 0) { swap(r0, r2); }
	}
	cout << r0 << endl << r1 << endl << r2 << endl << "~~~~" << endl;

	//
	if (r1.z != 0) { r1 = r0 * r1.z - r1 * r0.z; }
	if (r2.z != 0) { r2 = r0 * r2.z - r2 * r0.z; }
	cout << r0 << endl << r1 << endl << r2 << endl << "~~~~" << endl;

	//
	if (r1.y == 0 && r2.y != 0) { swap(r1, r2); }
	if (r2.y != 0) {
		r2 = r1 * r2.y - r2 * r1.y;
		r2.c /= r2.x;
		r2.x = 1;
	}
	cout << r0 << endl << r1 << endl << r2 << endl << "~~~~" << endl;

	//
	if (r1.x != 0) {
		r1 = r1 * r2.x - r2 * r1.x;
		r1.c /= r1.y;
		r1.y = 1;
	}
	cout << r0 << endl << r1 << endl << r2 << endl << "~~~~" << endl;

	//
	if (r0.x != 0) { r0 = r0 - r2 * r0.x; }
	if (r0.y != 0) { r0 = r0 - r1 * r0.y; }
	r0.c /= r0.z;
	r0.z = 1;
	cout << r0 << endl << r1 << endl << r2 << endl << "~~~~" << endl;

	static int results[3];
	results[0] = r2.c;
	results[1] = r1.c;
	results[2] = r0.c;
	return results;
}

int main()
{
	// int matrix[3][4] = {{4, -3, 1, -10}, {2, 1, 3, 0}, {-1, 2, -5, 17}};
	int matrix[3][4] = {
		{8, 97, 77, 10628},
		{95, 83, 9, 11047},
		{99, 76, 87, 15053}};
	int* results = solveEq(matrix);

	cout << results[0] << ", " << results[1] << ", " << results[2] << endl;

	return 0;
}
