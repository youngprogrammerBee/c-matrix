#include<stddef.h>
#include<complex>
#include<iostream>
#include<cstdio>
#include<cstring>
#include <opencv2/opencv.hpp>
using namespace std;

template<typename T>
class matrix{
private:
    int col;
    int row;
    int *col_cnt; //save the number of non-zero cols in each row
    int **col_id; //save non-zero col in each row
    T **data; //save data
    void initialize();

public:
	matrix(){}
	matrix(int r, int c);
	matrix(int r, int c, T *a);
	virtual ~matrix();
	T get(int i, int j);
	int getcol(){return col;}
	int getrow(){return row;}
	void set(int i, int j, T val);
	void show();
	matrix<T>& operator=(const matrix<T>& m);
	template<typename O>friend istream& operator>>(istream&, matrix<O>& m);
	//make virtual anti

	bool isRowVector(matrix<T> a){return a.getrow()==1;}
	bool isColVector(matrix<T> a){return a.getcol()==1;}



	T findMax();
	T findRowMax(int i);
	T findColMax(int j);
	T findMin();
	T findRowMin(int i);
	T findColMin(int j);
	T Sum();
	T findRowSum(int i);
	T findColSum(int j);
	T Aver();
	T findRowAver(int i);
	T findColAver(int j);
};
template<typename T>
cv::Mat convert_toCV(matrix<T> a);
template<typename T>
matrix<T> convert_FromCV(cv::Mat cvMat);
