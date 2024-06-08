#include <stdio.h> 
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std; 

class Matrix 
{
    
    private:
    int rows, cols;
    double** mat;
    
    public:
        static int count;
        int number;
    
        Matrix(int rows, int cols);
        Matrix(int rows, int cols, double** data);
        Matrix(const Matrix& m);
        ~Matrix();

        Matrix operator+(const Matrix& r);
        Matrix operator-(const Matrix& r);
        Matrix operator*(const Matrix& r);
        Matrix operator*(double c);
        Matrix operator=(const Matrix& r);
        void print() const;
        int getRows() const { return rows; }
        int getCols() const { return cols; }
        double getElem(int i, int j) const { return mat[i][j]; };
        

};

class vect
{ 
    
    private:
	    int dim;
	    double *b;	
	
	public:
	    static int count;  
	    int number; 
	
	    vect (int d);
	    vect (int d,double *x);
	    vect(); 
	    ~vect();
	    vect (const vect &x);
	
	    void printb();
	    vect operator +(const vect &r);
	    friend vect operator -(const vect &l, const vect &r);
	    double operator*(const vect &r);
	    vect& operator=(const vect &r);
    	vect operator-();
	    vect operator*(int c);
	    
	    friend vect operator*(const vect& v, const Matrix& m);
	    
};

int vect::count = 0; 

vect::vect() 
{ 
    count++; 
    number = count;  
    cout<<endl<<"Created vector "<<number<<endl;
}

vect::vect(int d) 
{ 
    count++; 
    number = count; 
	dim=d;
	b=new double [dim];
	for (int i=0; i<dim; i++)
		b[i]=0;
    cout <<endl<<"Created vector "<<number<<endl;
} 

vect::vect(int d, double *x)
{
	count++;
	number=count;
	dim=d;
	b=new double [dim];
	for (int i=0; i<dim; i++)
	b[i]=x[i];
	cout<<endl<<"Created vector "<< number<<endl;
}

vect vect::operator +(const vect& r)
{
	cout<<endl<<"Summa vectora "<<number<<" and "<<r.number<<endl;
		vect tmp (dim);
		for (int i=0; i<dim; i++)
		    tmp.b[i]=b[i]+r.b[i];
		return tmp;
}

vect::~vect()
{
	cout<<endl<<"Destroing vector #"<<number<<endl;
	delete[]b;
}

vect operator-(const vect &l, const vect &r)
{ 
    cout<<endl<<"Subtraction vectors "<<l.number<<" and  "<<r.number<<endl;
    vect tmp (l.dim);
    for (int i = 0; i < l.dim; i++) 
 	    tmp.b[i]=l.b[i]-r.b[i];
	return tmp;

} 

vect::vect(const vect &x)
{
	count++;
	number=count;
	dim=x.dim;
	b = new double[dim];
	for(int i = 0; i<dim; i++)
		b[i]=x.b[i];
	cout<<endl<<"Copy vectors.  Create vector №"<<number<<endl;	
}

double vect::operator*(const vect &r) 
{
    cout<<endl<<"Multiplication(scalar) vectors "<<number<<" and  "<<r.number<<endl;
	int p=0;
	for (int i=0; i<r.dim; i++)
	    p=p+(b[i]*r.b[i]);
	return p;
}

vect vect::operator*(int c) 
{
    cout<<endl<<"Multiplication vector "<<number<<" and const "<<c<<endl;
	vect tmp (dim);
	for (int i=0; i<dim; i++)
		tmp.b[i]=c*b[i];
	return tmp;
}

vect& vect::operator=(const vect &r) 
{ 
    cout << endl << "Operator = for vector" << endl;

    if (b != nullptr) 
        delete[] b;

    dim = r.dim;
    b = new double[dim];
    for (int i = 0; i < dim; i++) 
        b[i] = r.b[i];

    return *this;
}

void vect::printb()
{
    cout<<endl<<"Vector "<<number<<": ";
    for (int i=0; i<dim; i++)
	{
		cout<<b[i];
		if(i<dim-1)
			cout<<",";
	}
}

vect vect::operator-()
{
    cout<<endl<<"Operator - for vector "<<number<<endl;
	vect tmp(dim,b);
	for (int i = 0; i<dim; i++)
		if (tmp.b[i]!=0) 
		    tmp.b[i] = -tmp.b[i];
	return tmp;	
}
	
	

int Matrix::count = 0;

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) 
{
    count++;
    number = count;
    mat = new double*[rows];
    for (int i=0; i<rows; i++) 
    {
        mat[i] = new double[cols];
        for (int j=0; j<cols; j++) 
            mat[i][j] = 0.0;
    }
    cout << "Created matrix " << number << endl;
}

Matrix::Matrix(int rows, int cols, double** data) : rows(rows), cols(cols) 
{
    count++;
    number = count;
    mat = new double*[rows];
    for (int i=0; i<rows; i++) 
    {
        mat[i] = new double[cols];
        for (int j=0; j<cols; j++) 
            mat[i][j] = data[i][j];
    }
    cout << "Created matrix " << number << endl;
}

Matrix::Matrix(const Matrix& m) : rows(m.rows), cols(m.cols) 
{
    count++;
    number = count;
    mat = new double*[rows];
    for (int i=0; i<rows; i++) 
    {
        mat[i] = new double[cols];
        for (int j=0; j<cols; j++) 
            mat[i][j] = m.mat[i][j];
    }
    cout << "Copied matrix " << number << endl;
}

Matrix::~Matrix() 
{
    for (int i=0; i<rows; i++) 
        delete[] mat[i];
    delete[] mat;
    cout << "Destroyed matrix " << number << endl;
}


void Matrix::print() const 
{
    for (int i=0; i<rows; i++) 
    {
        for (int j=0; j<cols; j++)
            cout << setw(8) << mat[i][j];
        cout << endl;
    }
}

Matrix Matrix::operator+(const Matrix& r) 
{    
    if (rows != r.rows || cols != r.cols) 
    {
        cout<<"Matrices dimensions must be the same.";        
        exit(1);
    }
    cout<<endl<<"Summa matrix "<<number<<" and "<<r.number<<endl;
    Matrix result(rows, cols);
    for (int i=0; i<rows; i++) 
    {        
        for (int j=0; j<cols; j++) 
            result.mat[i][j] = mat[i][j] + r.mat[i][j];        
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& r) 
{
    if (rows != r.rows || cols != r.cols) 
    {
        cout<<"Matrices dimensions must be the same.";        
        exit(1);
    }
    
    cout<<endl<<"Subtraction matrix "<<number<<" and "<<r.number<<endl;
    Matrix result(rows, cols);
    for (int i=0; i<rows; i++) 
    {
        for (int j=0; j<cols; j++)
            result.mat[i][j] = mat[i][j] - r.mat[i][j];
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& r) 
{
    if (cols != r.rows) 
    {
        cout<<"Matrices dimensions must be the same.";        
        exit(1);
    }
    
    cout<<endl<<"Multiplication matrix "<<number<<" and "<<r.number<<endl;

    Matrix result(rows, r.cols);
    for (int i=0; i<rows; i++) 
    {
        for (int j=0; j<r.cols; j++) 
        {
            result.mat[i][j] = 0;
            for (int k=0; k<cols; k++) 
                result.mat[i][j] += mat[i][k] * r.mat[k][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(double c) 
{
    cout<<endl<<"Multiplication matrix "<<number<<" and scalar "<<c<<endl;
    Matrix result(rows, cols);
    for (int i=0; i<rows; i++) 
    {
        for (int j=0; j<cols; j++) 
            result.mat[i][j] = mat[i][j] * c;
    }
    return result;
}

Matrix Matrix::operator=(const Matrix& r) 
{
    cout << endl << "Operator = for matrix" << endl;
    for (int i=0; i<rows; i++) 
        delete[] mat[i];
        
    delete[] mat;

    rows = r.rows;
    cols = r.cols;
    mat = new double*[rows];
    for (int i=0; i<rows; i++) 
    {
        mat[i] = new double[cols];
        for (int j=0; j<cols; j++) 
            mat[i][j] = r.mat[i][j];
    }
    return *this;
}

vect operator*(const vect& v, const Matrix& m) 
{
    cout << endl << "Operator * for vector and matrix" << endl;
    double* resultData = new double[m.getCols()];
    for (int i=0; i<m.getCols(); i++) 
    {
        resultData[i] = 0;
        for (int j=0; j<m.getRows(); j++) 
            resultData[i] += v.b[j] * m.getElem(j, i);
    }
    vect result(m.getCols(), resultData);
    
    return result;
}

int main()
{
	double a1[3]={1,10,11}, a2[3]={7,12,-6};
	vect b1(3,a1), b2(3,a2);
	vect r(3);
    
    b1.printb();
	b2.printb();
	int c = b1*b2;
	cout<<endl<<c<<endl;
	
	r=b1+b2;
	r.printb();
	r=b1-b2;
	r.printb();
	r=b1*6;
	r.printb();
	r=-b2;
	r.printb();
	
	cout<<endl<<"____________"<<endl;
	
    const int rows = 2;
    const int cols = 2;
    double** data1 = new double*[rows];
    double** data2 = new double*[rows];
    for (int i=0; i<rows; i++) 
    {
        data1[i] = new double[cols];
        data2[i] = new double[cols];
    }

    data1[0][0] = 1; data1[0][1] = 2;
    data1[1][0] = 3; data1[1][1] = 4;

    data2[0][0] = 5; data2[0][1] = 6;
    data2[1][0] = 7; data2[1][1] = 8;

    Matrix m1(rows, cols, data1);
    Matrix m2(rows, cols, data2);

    Matrix sum = m1 + m2;
    cout << "Sum of matrices:" << endl;
    sum.print();

    Matrix sub = m1 - m2;
    cout << "subctracrion of matrices:" << endl;
    sub.print();

    Matrix mult1 = m1 * 2.0;
    cout << "Multiplication of matrix by constant:" << endl;
    mult1.print();

    Matrix mult2 = m1 * m2;
    cout << "Multiplication of matrices:" << endl;
    mult2.print();
    
    double a[2] = {1, 2};
    vect v1(2, a);
    r = v1*m1;
    cout << "Multiplication of vector and matrix:" << endl;
    r.printb();
    
    return 0;
}