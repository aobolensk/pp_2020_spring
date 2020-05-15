// Copyright 2020 Trenina Elizaveta

#include <algorithm>
#include <utility>
#include <random>
#include <vector>
#include <ctime>
#include "../../../modules/task_1/trenina_e_convex_hull_graham/convex_hull_graham.h"

bool rotate(const point& A, const point& B, const point& C) {// left?
	return (B.x - A.x) * (C.y - B.y) - (B.y - A.y) * (C.x - B.x) >= 0;
}

bool cmp(point B, point C) {
//bool cmp(const point& B, const point& C) {// B<C?
	return B.x * (C.y - B.y) - B.y * (C.x - B.y) < 0 ||
		B.x * (C.y - B.y) - B.y * (C.x - B.y) == 0 &&
		B.x * B.x + B.y * B.y < C.x* C.x + C.y * C.y;

}


std::vector<point> Graham(std::vector<point> Q) {
	if (Q.size() < 3) throw "|Q|<3";

	point p0 = Q[0];
	for (int i = 1; i < Q.size(); i++) {
		if ((Q[i].y < p0.y) || (Q[i].y == p0.y) && (Q[i].x < p0.x))
			p0 = Q[i];
	}
	//p0

	for (auto i : Q) {
		i.x -= p0.x;
		i.y -= p0.y;
	}
	//p0.x = 0.0;
	//p0.y = 0.0;
	//std::sort(Q.begin()+1, Q.end(), &cmp);

	std::vector<point> hull;
	hull.push_back(Q[0]);
	hull.push_back(Q[1]);

	size_t i = 2, k = 0;
	do {
		point t = Q[i++];

		while (!rotate(hull[k], hull[k + 1], t)) {
			hull.pop_back();
			--k;
		}
		hull.push_back(t);
		++k;
	} while (i < Q.size());

	return hull;
}


std::vector<point> GetRandSet(int n) {
	if (n < 3) throw;
	std::vector<point> result(n);

	//std::srand(std::time(nullptr));

	//std::generate(result.begin(), result.end(), []() {
	//	return point{ static_cast<double>(std::rand() % 100 - 50),
	//				 static_cast<double>(std::rand() % 100 - 50) };
	//	});
	//return result;



	std::mt19937 gen(time(0));
	//std::uniform_double_distribution<> uid(0, 100);
	std::uniform_real_distribution<> uid(-100, 100);

	for (int i = 0; i < n; i++) {
		result[i].x = uid(gen);
		result[i].y = uid(gen);
	}

	return result;
}


