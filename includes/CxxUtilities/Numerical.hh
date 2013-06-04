/*
 * Numerical.hh
 *
 *  Created on: Apr 22, 2013
 *      Author: yuasa
 */

namespace CxxUtilities {

class Function1D {
public:
	virtual ~Function1D() {
	}

public:
	virtual double dydx(double x, double y) =0;
};

class Points2D {
public:
	std::vector<double> x;
	std::vector<double> y;

public:
	void addPoint(double x, double y){
		this->x.push_back(x);
		this->y.push_back(y);
	}

public:
	void getLastPoint(double &x, double &y){
		x=this->x[this->x.size()-1];
		y=this->y[this->y.size()-1];
	}
};

class Integrator {
public:
	static Points2D* RungeKutta(Function1D* f, double xmin, double xmax, double y_xmin, double dx) {
		double y = y_xmin;
		double x = xmin;
		double k1, k2, k3, k4;
		Points2D* points=new Points2D;
		while (x < xmax) {
			k1 = f->dydx(x, y);
			k2 = f->dydx(x + dx / 2, y + dx / 2 * k1);
			k3 = f->dydx(x + dx / 2, y + dx / 2 * k2);
			k4 = f->dydx(x + dx, y + dx * k3);
			points->addPoint(x,y);
			y += dx * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
			x += dx;
		}
		return points;
	}
};

}
