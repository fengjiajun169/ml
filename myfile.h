/*功能:实现文件的读写以及其它一些操作
 *作者:冯佳军
 *时间:2015/01/15
 *
 * */

#include<iostream>
#include<vector>
#include<iterator>
#include<fstream>
#include<iomanip>
#include<cmath>

using namespace std;

template <typename T> class Myfile
{
    public:
        typedef T valueType;
        typedef vector<valueType> t_vec;    //类型为valueType的容器
        typedef vector<t_vec> t_t_vec;      //类型为valueType的二维容器
        typedef typename vector<valueType>::iterator t_vec_iter; //第一个容器的迭代器
        typedef typename vector<t_vec>::iterator t_t_vec_iter;   //二维容器的迭代器

        //构造函数

        Myfile(string filename);

        void addData(int row, int col, valueType data); //添加一个元素
        void addRowData(int row, t_vec data);       //添加一行元素
        void addColData(int col, t_vec data);       //添加一列元素

        void eraseData(int row, int col);  //删除一个元素
        void eraseRowData(int row);  //删除一行元素
        void eraseColData(int col);  //删除一列元素

        void alterData(int row, int col, valueType data); //修改一个元素
        void alterRowData(int row, t_vec data);       //修改一行元素
        void alterColData(int col, t_vec data);       //修改一列元素

        valueType getData(int row, int col); //根据位置返回数据
        t_vec getRowData(int row);  //返回第row行的数据
        t_vec getColData(int col);  //返回第col行的数据
        int getElementCount(valueType data);    //获取文件中值为data的个数

        void printData();           //打印数据
        void processFile();         //将文件处理成标准格式:首尾无空格,中间以空格隔开
       
        t_t_vec getFileData(){return fileData;}//返回文件数据
        int getRowNum(){return rowNum;}
        vector<int> getColNum(){return colNum;}

    private:
        string fileName;        //待操作文件的文件名
        t_t_vec fileData;           //文件中的数据
        int rowNum;             //行数
        vector<int> colNum;             //保存列数的容器
        void setRowColNum();
        void readFile();                //读取文件中所有的数据
};


template <typename T> Myfile<T>::Myfile(string filename)
{
    fileName = filename;
    processFile();
    setRowColNum();
    readFile();
}

template <typename T> void Myfile<T>::readFile()
{
    ifstream fin;
    fin.open("./inDir/standard.in");
    t_vec rowData;
    valueType value;
    char cha;
    fileData.clear();
    for(int i = 0; i != rowNum; ++i)
    {
        rowData.clear();
        for(int j = 0; j != colNum[i]; ++j)
        {
            fin>>value;
            rowData.push_back(value);
        }
        fileData.push_back(rowData);
    }
    fin.close();
}

template <typename T> void Myfile<T>::setRowColNum()
{
    int rownum = 0;
    int colnum = 0;
    colNum.clear();
    string str;
    int flag = 0;       //排除连续两个空格的情况
    ifstream fin;
    fin.open("./inDir/standard.in");
    while(getline(fin, str))
    {
        rownum++;
        colnum = 1;
        for(int i = 0; i != str.size(); ++i)
        {
            if(str[i] == ' ' && flag == 0)
            {
                colnum++;
                flag = 1;
            }
            else if(str[i] != ' ')
            {
                flag = 0;
            }
        }
        colNum.push_back(colnum);
    }
    fin.close();
    rowNum = rownum;
}

template <typename T> void Myfile<T>::addData(int row, int col, T data)
{
    //行号超过文件行数
    if(row >= fileData.size() || col >= fileData[row].size())
    {
        cout<<"所给行号或列号超过文件总行数或该行列数!"<<endl;
        return ;
    }
    else 
    {
        fileData[row].insert(fileData[row].begin() + col, data);
    }
    return;
}

template <typename T> void Myfile<T>::addRowData(int row, t_vec data)
{
    //行号超过文件行数
    if(row >= fileData.size())
    {
        cout<<"所给行号超过文件总行数!"<<endl;
        return;
    }
    else
    {
        fileData.insert(fileData.begin() + row, data);
    }
    return;
}

template <typename T> void Myfile<T>::addColData(int col, t_vec data)
{
    //判断给的data的元素个数是否与文件的行数相等
    if(data.size() != fileData.size())
    {
        cout<<"所给元素的个数与文件中的行数不相等!"<<endl;
        return;
    }
    //先判断是否超过每行的元素的个数
    for(int i = 0; i != fileData.size(); ++i)
    {
        if(col >= fileData[i].size())
        {
            cout<<"所给列号超过第"<<i<<"行总列数!"<<endl;
            return;
        }
    }
    for(int i = 0; i != fileData.size(); ++i)
    {
        fileData[i].insert(fileData[i].begin() + col, data[i]);
    }
    return;
}

template <typename T> void Myfile<T>::eraseData(int row, int col)
{
    //行号超过文件行数
    if(row >= fileData.size() || col >= fileData[row].size())
    {
        cout<<"所给行号或列号超过文件总行数或该行列数!"<<endl;
        return ;
    }
    else 
    {
        fileData[row].erase(fileData[row].begin() + col);
    }
    return;
}

template <typename T> void Myfile<T>::eraseRowData(int row)
{
    //行号超过文件行数
    if(row >= fileData.size())
    {
        cout<<"所给行号超过文件总行数!"<<endl;
        return;
    }
    else
    {
        fileData.erase(fileData.begin() + row);
    }
    return;
}

template <typename T> void Myfile<T>::eraseColData(int col)
{
    //先判断是否超过每行的元素的个数
    for(int i = 0; i != fileData.size(); ++i)
    {
        if(col >= fileData[i].size())
        {
            cout<<"所给列号超过第"<<i<<"行总列数!"<<endl;
            return;
        }
    }
    for(int i = 0; i != fileData.size(); ++i)
    {
        fileData[i].erase(fileData[i].begin() + col);
    }
    return;
}

template <typename T> void Myfile<T>::alterData(int row, int col, T data)
{
    //行号超过文件行数
    if(row >= fileData.size() || col >= fileData[row].size())
    {
        cout<<"所给行号或列号超过文件总行数或该行列数!"<<endl;
        return ;
    }
    else 
    {
        fileData[row][col] = data;
    }
    return;
}

template <typename T> void Myfile<T>::alterRowData(int row, t_vec data)
{
    //行号超过文件行数
    if(row >= fileData.size())
    {
        cout<<"所给行号超过文件总行数!"<<endl;
        return;
    }
    else if(data.size() != fileData[row].size())
    {
        cout<<"所给数据的个数与待修改行的数据个数不相等"<<endl;
        return;
    }
    else
    {
        for(int i = 0; i != data.size(); ++i)
        {
            fileData[row][i] = data[i];
        }
    }
    return;
}

template <typename T> void Myfile<T>::alterColData(int col, t_vec data)
{
    //判断给的data的元素个数是否与文件的行数相等
    if(data.size() != fileData.size())
    {
        cout<<"所给元素的个数与文件中的行数不相等!"<<endl;
        return;
    }
    //先判断是否超过每行的元素的个数
    for(int i = 0; i != fileData.size(); ++i)
    {
        if(col >= fileData[i].size())
        {
            cout<<"所给列号超过第"<<i<<"行总列数!"<<endl;
            return;
        }
    }
    for(int i = 0; i != fileData.size(); ++i)
    {
        fileData[i][col] = data[i];
    }
    return;
}

template <typename T> T Myfile<T>::getData(int row, int col)
{
    //行号超过文件行数
    if(row >= fileData.size() || col >= fileData[row].size())
    {
        cout<<"所给行号或列号超过文件总行数或该行列数!"<<endl;
        return fileData[0][0];
    }
    return fileData[row][col];
}

template <typename T> vector<T> Myfile<T>::getRowData(int row)
{
    //行号超过文件行数
    if(row >= fileData.size())
    {
        cout<<"所给行号超过文件总行数!"<<endl;
        return fileData[0];
    }
    return fileData[row];
}

template <typename T> vector<T> Myfile<T>::getColData(int col)
{
    t_vec data;
    data.clear();
    for(int i = 0; i != fileData.size(); ++i)
    {
        if(col >= fileData[i].size())
        {
            cout<<"所给列号超过第"<<i<<"行总列数!"<<endl;
        }
        else 
        {
            data.push_back(fileData[i][col]);
        }
    }
    return data;
}

template <typename T> int Myfile<T>::getElementCount(valueType data)
{
    int count = 0;
    for(t_t_vec_iter i = fileData.begin(); i != fileData.end(); ++i)
    {
        for(t_vec_iter j = (*i).begin(); j != (*i).end(); ++j)
        {
            if(*j == data)
            {
                count++;
            }
        }
    }
    return count;
}

template <typename T> void Myfile<T>::processFile()
{
    ifstream fin;
    fin.open(fileName.c_str());
    string str;
    vector<int> flag; //保存操作的动作,第一个元素保存首个非空格字符位置,最后一个元素保存最后一个非空格位置,中间的元素保存逗号的位置
    int startFlag = 0, first = 0, end = 0;
    ofstream fout;
    fout.open("./inDir/standard.in");
    fout.close();
    fout.open("./inDir/standard.in", ofstream::app);
    while(getline(fin, str))
    {
        startFlag = 0;
        first = 0;
        flag.clear();
        end = str.size();
        flag.push_back(first);
        for(int i = 0; i != str.size(); ++i)
        {
            //记录第一个非空格元素位置
            if(startFlag == 0 && str[i] == ' ')
            {
                first = i + 1;
                continue;
            }
            //处理逗号
            else if(str[i] == ',') 
            {
                startFlag = 1;
                flag.push_back(i);
            }
            else
            {
                startFlag = 1;
            }
        }
        flag[0] = first;
        //记录最后一个非空格元素位置
        for(int i = str.size() - 1; i != 0 && str[i] == ' '; --i)
        {
            end = i;
        }
        flag.push_back(end);

        for(vector<int>::iterator i = flag.begin() + 1; i != flag.end() - 1; ++i)
        {
            str[*i] = ' ';
        }
        str = str.substr(flag[0], flag[flag.size() - 1] - flag[0]);
        fout<<str<<endl;
    }
    fout.close();
}

template <typename T> void Myfile<T>::printData()
{
    ofstream fout;
    fout.open("./outDir/result.out", iostream::app);
    for(t_t_vec_iter i = fileData.begin(); i != fileData.end(); ++i)
    {
        for(t_vec_iter j = (*i).begin(); j != (*i).end(); ++j)
        {
            fout<<setw(15)<<*j;
        }
        fout<<endl;
    }
    cout<<"数据输出在./outDir/result.out文件中"<<endl;
}
