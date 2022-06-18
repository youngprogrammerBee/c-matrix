#include "matrix.h"
#include<complex>
#define NULL_POINTER_EXCEPTION                (0x1 << 0)
#define INVALID_SIZE_EXCEPTION        		  (0x1 << 1)
#define NOT_VECTOR_EXCEPTION                  (0x1 << 2)
#define INVALID_VECTOR_EXCEPTION            (0x1 << 3)
#define INVALID_VECTOR_LENGTH_EXCEPTION     (0x1 << 4)

using namespace std;
template<typename T>
void matrix<T>::initialize(){
	col_cnt = new int[row];
	col_id = new int*[row];
	data = new T*[row];
	for (int i = 0; i < row; ++i) {
		col_id[i] = new int[col];
		data[i] = new T[col];
	}
}

template<typename T>
matrix<T>::matrix(int r, int c){
	T a[r*c];
	memset(a,0,sizeof(a));
	col=c,row=r;
	T zero=0;
	initialize(); 
	
	for (int i = 0; i < r; i++) {
		col_cnt[i]=0;
		for (int j = 0; j < c; j++) {
			if(a[i*col+j]!=zero){
				col_id[i][col_cnt[i]] = j;
				data[i][col_cnt[i]] = a[i*col+j];
				col_cnt[i]++;
			}
		}
	}
}

template<typename T>
matrix<T>::matrix(int r, int c, T a[]){
	col=c,row=r;
	T zero=0;
	initialize(); 
	
	for (int i = 0; i < r; i++) {
		col_cnt[i]=0;
		for (int j = 0; j < c; j++) {
			if(a[i*col+j]!=zero){
				col_id[i][col_cnt[i]] = j;
				data[i][col_cnt[i]] = a[i*col+j];
				col_cnt[i]++;
			}
		}
	}
}

template<typename T>
matrix<T>::~matrix() {
	for (int i = 0; i < row; ++i) {
		delete[] col_id[i];
		delete[] data[i];
	}
	delete[] col_id;
	delete[] data;
	delete[] col_cnt;
}

template<typename T>
T matrix<T>::get(int i, int j){
	for(int k=0;k<col_cnt[i];k++) if(j==col_id[i][k]) return data[i][k];
	return 0;
}

template<typename T>
void matrix<T>::set(int i, int j, T val){
	T* temp = new int[col_cnt[i]+1];
	T* t = new T[col_cnt[i]+1];
	for (int k = 0; k < col_cnt[i]; ++k) {
		temp[k]=col_id[i][k];
		t[k]=data[i][k];
	}
	temp[col_cnt[i]]=j;
	t[col_cnt[i]]=val;
	col_cnt[i]++;
	
	delete[] col_id[i];
	delete[] data[i];
	col_id[i] = temp;
	data[i] = t;
}

template<typename T>
void matrix<T>::show(){
	for (int i = 0; i < row; ++i) {
		T temp[114514]={};
		for (int j = 0; j < col_cnt[i]; j++) {
			temp[col_id[i][j]]=data[i][j];
		}
		for (int j = 0; j < col; j++) {
			cout<<temp[j]<<" ";
		}
		cout<<endl;
	}
}

template<typename T>
matrix<T>& matrix<T>::operator=(const matrix<T>& m){
	if (this == &m) {
		return *this;
	}
	
	for (int i = 0; i < row; ++i) {
		delete[] col_id[i];
		delete[] data[i];
	}
	delete[] col_id;
	delete[] data;
	delete[] col_cnt;
	
	row = m.row;
	col = m.col;
	
	col_cnt = new int[row];
	col_id = new int*[row];
	data = new T*[row];
	
	for (int i = 0; i < row; i++) {
		col_cnt[i] = m.col_cnt[i];
		col_id[i] = new int[col_cnt[i]];
		data[i] = new T[m.col_cnt[i]];
		for (int j = 0; j < col_cnt[i]; j++) {
			col_id[i][j] = m.col_id[i][j];
			data[i][j] = m.data[i][j];
		}
	}
	
	return *this;
}
template<typename T>
cv::Mat convert_toCV(matrix<T> a){
    cv::Mat newMat(cv::Size( a.getrow(),a.getcol()),CV_32FC1);
    for(int i = 0; i <a.getrow();i++){
        for(int j = 0;j < a.getcol();j++){
            newMat.at<float>(i,j) = static_cast<float>(a.get(i,j));
        }
    }
    return newMat;
}

template<typename T>
matrix<T> convert_FromCV(cv::Mat cvMat){
    matrix<T> mat(cvMat.rows,cvMat.cols);
    for(int i = 0;i < cvMat.rows;i++){
        for(int j = 0;j < cvMat.cols;j++){
            mat.set(i + 1,j + 1,cvMat.at<float>(i,j));
        }
    }
    return mat;
}
