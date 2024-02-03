#include<iostream>
#include<vector>
#include <math.h>
#include <assert.h>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <numeric>

int r, f, n;

using namespace std;

template<typename InputIterator, typename ValueType>
InputIterator closest(InputIterator first, InputIterator last, ValueType value) {
    return min_element(first, last, [&](ValueType x, ValueType y) {
        return abs(x - value) < abs(y - value);
    });
}

long search_closest(vector<double> sorted_array, double x) {
    auto iter_geq = std::upper_bound(sorted_array.begin(), sorted_array.end(), x);
    if (iter_geq == sorted_array.begin()) {
        return 0;
    }

    double a = *(iter_geq - 1);
    double b = *(iter_geq);
    if (fabs(x - a) < fabs(x - b)) {
        return iter_geq - sorted_array.begin() - 1;
    }
    return iter_geq - sorted_array.begin();

}

double angle(pair<int, int> p) {
    return atan2(double(p.second), double(p.first));// * (180.0 / M_PI);
}

double dis(pair<int, int> p) {
    return sqrt((double(p.first) * double(p.first)) + (double(p.second) * double(p.second)));
}

double dis2(pair<int, int> p, double angle, double radius) {
    double x1 = cos(angle) * radius;
    double y1 = sin(angle) * radius;
    return sqrt(((double(p.first) - (x1)) * (double(p.first) - (x1))) +
                ((double(p.second) - (y1)) * (double(p.second) - (y1))));
}

int main() {
    cin >> r >> f >> n;

    vector<int> radii(r);
    vector<pair<double, double>> angles(3*f);
    vector<pair<int, int>> points(n);

    for (int i = 0; i < r; ++i) {
        cin >> radii[i];
    }
    sort(radii.begin(), radii.end());

    for (int i = 0; i < f; ++i) {
        int x, y;
        cin >> x >> y;
        double a = angle({x, y});;
        angles[3*i + 0] = make_pair(a - M_PI*2, a);
        angles[3*i + 1] = make_pair(a, a);
        angles[3*i + 2] = make_pair(a + M_PI*2, a);
    }
    f *= 3;
    sort(angles.begin(), angles.end());

    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        points[i] = {x, y};
    }

    vector<int> pidxs(n);
    iota(pidxs.begin(), pidxs.end(), 0);
    sort(pidxs.begin(), pidxs.end(), [&points](int a, int b) { return dis(points[a]) < dis(points[b]); });

    vector<double> out(n);
    int minD = 0;
    for (int i : pidxs) {
        double pAng = angle(points[i]);
        double pDst = dis(points[i]);

        while(minD < r-1 && fabs(radii[minD] - pDst) > 10) minD++;

        int maxD = minD;
        while(maxD < r-1 && fabs(radii[maxD] - pDst) < 10) maxD++;

        int oMinA = f-1, oMaxA = f-1;
        auto minAi = std::lower_bound(angles.begin(), angles.end(), make_pair(pAng, 2147483647.0));
        if (minAi != angles.end()) {
            oMinA = std::min((int) (minAi - angles.begin()), 0);
            oMaxA = minAi - angles.begin();
        }

        int minA = oMinA, maxA = oMaxA;
        while(minA > 0 && fabs(angles[minA].first - angles[oMinA].first) < 0.01) minA--;
        while(maxA < f-1 && fabs(angles[maxA].first - angles[oMaxA].first) < 0.01) maxA++;

        // printf("POINT: %d %d\n", points[i].first, points[i].second);
        // printf("RAD: %lf %lf-%lf [%d-%d]\n", pDst, radii[minD], radii[maxD], minD, maxD);
        // printf("ANG: %lf %lf-%lf [%d-%d]\n", pAng, angles[minA].second, angles[maxA].second, minA, maxA);

        double minDis = 2147483647;
        for(int j = minA; j <= maxA; j++) {
            for(int k = minD; k <= maxD; k++) {
                double d = dis2(points[i], angles[j].second, radii[k]);
                if (d < minDis) minDis = d;
            }
        }
        out[i] = minDis;
    }

    for (double v : out) cout << fixed << setprecision(12) << v << endl;

    return 0;
}
