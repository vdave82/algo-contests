// Geometry algorithms.
//
// 1) Convex Hull with Graham scan (https://en.wikipedia.org/wiki/Graham_scan)
//    Finds the convex hull of 2D points in O(|N| * log(|N|)) time.

#include <vector>

// Basic Type definitions.

template<class TCoord> struct Point {
	TCoord x = 0;
	TCoord y = 0;

	Point(TCoord a_x, TCoord a_y) : x(a_x), y(a_y) {}
};

typedef Point<int> P2i;
typedef Point<long long> P2l;
typedef Point<double> P2f;

// Convex Hull with Graham Scan.

template<class TCoord> struct SortByAngleFromRefPoint {
	Point<TCoord> ref;

	SortByAngleFromRefPoint(Point<TCoord> a_ref) : ref(a_ref) {}
	SortByAngleFromRefPoint(long long a_refX, long long a_refY) : refX(a_refX), refY(a_refY) {}

	bool operator()(const pair<long long, long long>& A, const pair<long long, long long>& B) const {
		if (A.cx == refX && A.cy == refY) return true;
		if (B.cx == refX && B.cy == refY) return false;

		if (A.cx == refX && B.cx == refX) {
			return (A.cy - refY) < (B.cy - refY);
		}
		if ((A.cy - refY) * (B.cx - refX) == (B.cy - refY) * (A.cx - refX)) {
			long long distA = (A.cx - refX) * (A.cx - refX) + (A.cy - refY) * (A.cy - refY);
			long long distB = (B.cx - refX) * (B.cx - refX) + (B.cy - refY) * (B.cy - refY);
			return distA < distB;
		}

		double angleA = atan2(A.cy - refY, A.cx - refX);
		double angleB = atan2(B.cy - refY, B.cx - refX);

		return angleA < angleB;
	}
};

vector<pair<long long, long long>> ConvexHull(vector<pair<long long, long long>>& P) {
	int startP = 0;
	for (int i = 1; i < P.size(); ++i) {
		if (P[i].cy < P[startP].cy || (P[i].cy == P[startP].cy && P[i].cx < P[startP].cx))
			startP = i;
	}

	SortByAngleFrom cmp(P[startP].cx, P[startP].cy);
	std::sort(P.begin(), P.end(), cmp);

	//for (const auto& x : P) {
	//	printf("O: %lld, %lld\n", x.cx, x.cy);
	//}

	vector<pair<long long, long long>> hull;
	for (const auto& currP : P) {
		while (hull.size() >= 2) {
			pair<long long, long long> secondLastP = hull[hull.size() - 2];
			pair<long long, long long> lastP = hull[hull.size() - 1];
			long long det = (lastP.cx - secondLastP.cx) * (currP.cy - secondLastP.cy) - (currP.cx - secondLastP.cx) * (lastP.cy - secondLastP.cy);
			if (det == 0) {
				long long distNew = (currP.cx - secondLastP.cx) * (currP.cx - secondLastP.cx) + (currP.cy - secondLastP.cy) * (currP.cy - secondLastP.cy);
				long long distOld = (lastP.cx - secondLastP.cx) * (lastP.cx - secondLastP.cx) + (lastP.cy - secondLastP.cy) * (lastP.cy - secondLastP.cy);
				if (distNew > distOld) det = -1; else det = 1;
			}
			if (det <= 0) {
				hull.pop_back();
			}
			else {
				break;
			}

		}
		hull.push_back(currP);
	}

	return hull;
}
