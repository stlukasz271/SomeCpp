#pragma once
using namespace std;

class Vector{
    private:
        double x=0.0,y=0.0;
    public:
        Vector(double x, double y){
            this->x=x;
            this->y=y;
        }
        double getX(){
            return x;
        }
        double getY(){
            return y;
        }
        double sqlen(){
            return x*x+y*y;
        }
        double len(){
            return sqrt(sqlen());
        }
        void setX(double x){
            this->x=x;
        }
        void setY(double y){
            this->y=y;
        }
        void set(double x, double y){
            this->x=x;
            this->y=y;
        }
        void set(Vector other){
            setX(other.getX());
            setY(other.getY());
        }
        void nulX(){
            setX(0.0);
        }
        void nulY(){
            setY(0.0);
        }
        void nul(){
            nulX();
            nulY();
        }
        void addX(double x){
            setX(this->x+x);
        }
        void addY(double y){
            setY(this->y+y);
        }
        void add(double x, double y){
            addX(x);
            addY(y);
        }
        static Vector add(Vector a, Vector b){
            Vector c(a.getX(),a.getY());
            c.add(b);
            return c;
        }
        Vector& operator+= (Vector other){
            add(other);
            return *this;
        }
        void multX(double x){
            setX(this->x*x);
        }
        void multY(double y){
            setY(this->y*y);
        }
        void mult(double x, double y){
            multX(x);
            multY(y);
        }
        void mult(double k){
            mult(k,k);
        }
        static Vector mult(Vector a,double k){
            Vector c(a.getX(),a.getY());
            c.mult(k);
            return c;
        }
        Vector& operator*= (double k){
            mult(k);
            return *this;
        }
        void add(Vector other){
            add(other.x,other.y);
        }
        double dot(Vector other){
            return (getX()*other.getX()) + (getY()*other.getY());
        }
};


double dotProduct(Vector a, Vector b){
    return (a.getX()*b.getX()) + (a.getY()*b.getY());
}

struct Point{
    double x=0.0,y=0.0;
};

double sqdist(Point a, Point b){
    return (b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y);
}

double dist(Point a, Point b){
    return sqrt(sqdist(a,b));
}

Vector operator *(Vector a, double k){
    return Vector::mult(a,k);
}

Vector operator +(Vector a, Vector b){
    return Vector::add(a,b);
}
