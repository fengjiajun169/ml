#include<iostream>
#include<fstream>
#include<iterator>
#include<cmath>
#include<vector>
#include<cstdlib>
#include<sys/time.h>
#include<iomanip>

#define pi 3.14159
#define ei 2.78281

using namespace std;

//容器类型定义
typedef vector<int> i_vec;
typedef vector<double> d_vec;
typedef vector<d_vec> d_d_vec;
typedef d_vec::iterator d_vec_iter;
typedef d_d_vec::iterator d_d_vec_iter;

class Matrix;

//操作符重载
Matrix operator*(Matrix v1, Matrix v2);     //矩阵的乘法
Matrix operator|(int scalar, Matrix m);     //矩阵的数乘
Matrix operator+(Matrix m1, Matrix m2);     //矩阵的加法
Matrix operator-(Matrix m1, Matrix m2);     //矩阵的减法

void exchangeRow(d_d_vec &v, int des, int src);       //交换矩阵的行

//矩阵类的声明
class Matrix 
{
    public:
        Matrix(d_d_vec m);//构造函数，参数为矩阵
        Matrix();//构造函数
        double getDetValue(); //计算方阵行列式的值
        d_d_vec getInverseMatrix(); //求逆矩阵
        d_d_vec getTrsMatrix(); //矩阵转置
        d_d_vec getAdjMatrix(); //求伴随矩阵
        d_vec computeU(); //计算列的算术平均值
        d_d_vec getCovMatrix(); //计算协方差矩阵

        void setMatrix(d_d_vec m){matrix = m;}
        void setRowNum(int row){rowNum = row;}
        void setColNum(int col){colNum = col;}
        int getRowNum(){return rowNum;}//分别获取行数和列数
        int getColNum(){return colNum;}
        d_d_vec getMatrix(){return matrix;}//求矩阵

        void printMatrix();

    private:
        int rowNum;
        int colNum;
        d_d_vec matrix;

        d_d_vec getCofactor(int r,int c); //根据行号和列号获得余子式
};
