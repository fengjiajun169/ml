/*功能:实现BP反向传播算法
 *作者:冯佳军
 *时间:2015/0117
 * */

#include"myfile.h"
#include"matrix.h"

//sigmoid函数计算       
inline double sigmoid(double value)
{
    return 1.0/(1.0 + pow(ei, -value));
}

//sigmoid导函数的计算
inline double desigmoid(double value)
{
    double sig = 1.0/(1.0 + pow(ei, -value));
    return sig * (1 - sig);
}

class Bp
{
    public:
        typedef vector<double> d_vec;
        typedef vector<d_vec> d_d_vec;
        typedef d_vec::iterator d_vec_iter;
        typedef d_d_vec::iterator d_d_vec_iter;

        Bp(Matrix trainData, Matrix target, int hide);           //构造函数
        void train();   //训练函数

        void classify(d_d_vec testData, d_d_vec label); //分类函数

        //get函数
        Matrix getX(){return x;}
        Matrix getY(){return y;}
        Matrix getZ(){return z;}
        Matrix getT(){return t;}
        Matrix getWx(){return Wx;}
        Matrix getWy(){return Wy;}
        double getJ(){return J;}

    private:
        //网络的参数
        int d;          //输入数据的维度,即x的个数
        int h;          //隐藏单元的个数
        int c;          //类别数,即分为c类
        int n;          //训练样本数

        //各层的数据
        Matrix x;       //单个训练数据输入增广矩阵x=[1,x1,x2,...xd]的转置
        Matrix y;       //单个隐藏单元输出增广矩阵y=[1,y1,y2,...yh]的转置,y=Wx*x
        Matrix z;       //单个输出层的输出z=[z1,z2,...zc],z=Wy*y
        Matrix t;       //单个目标向量输出t=[t1,t2,...tc]的转置
        Matrix Wx;      //计算隐藏层y所用的权值,[hx(d+1)]维
        Matrix Wy;      //计算输出层z所用的权值,[cx(h+1)]维
        d_d_vec p;       //反向传播的误差
        double J;       //目标输出与输出的误差,即J=1/2(t-z)^2
        double threshold;    //阈值
        double rate;   //学习率

    public:
        //函数
        Matrix detaWx();                //Wx的增量计算
        Matrix detaWy();                //Wy的增量计算
        void initWx();                //随机初始化Wx权值
        void initWy();                //随机初始化Wy权值
        Matrix augMatrix(Matrix m);     //求增广矩阵,即前面添1
        void updateY();                 //更新y的输出,经过sigmoid函数转换后的
        void updateZ();                 //更新z的输出,经过sigmoid函数转换后的
        void updateJ();                 //更新误差J
        void normalize(Matrix &m);       //规范化矩阵m,列最大值为1,其它为0
};
