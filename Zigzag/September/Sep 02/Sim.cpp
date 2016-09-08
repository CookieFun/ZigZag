#include <cstdio>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include  <vector>
#include  <fstream>
#include <set>
using namespace std;
vector<vector<double> > Matrix;
double Z;
set<int> P;
int cn, bn;

bool Pivot(pair<int, int> &p)//返回0表示所有的非轴元素都小于0
{
    int x = 0, y = 0;
    double cmax = -INT_MAX;
    vector<double> C = Matrix[0];
    vector<double> B;

    for( int i = 0 ; i < bn ; i++ )
    {
        B.push_back(Matrix[i][cn-1]);
    }
    
    for( int i = 0 ; i < C.size(); i++ )//在非轴元素中找最大的c
    {
        if( cmax < C[i] && P.find(i) == P.end())
        {
            cmax = C[i];
            y = i;
        }
    }
    if( cmax < 0 )
    {
        return 0;
    }

    double bmin = INT_MAX;
    for( int i = 1 ; i < bn ; i++ )
    {
        double tmp = B[i]/Matrix[i][y];
       if( Matrix[i][y] != 0 && bmin > tmp )
       {
           bmin = tmp;
           x = i;
       }
    }

    p = make_pair(x, y);

    for( set<int>::iterator it = P.begin() ; it != P.end() ; it++)
    {
        if( Matrix[x][*it] != 0 )
        {
            //cout<<"erase "<<*it<<endl;
            P.erase(*it);
            break;
        }
    }
    P.insert(y);
    //cout<<"add "<<y<<endl;
    return true;
}

void pnt()
{
    for( int i = 0 ; i < Matrix.size() ; i++ )
    {
        for( int j = 0 ; j < Matrix[0].size() ; j++ )
        {
            cout<<Matrix[i][j]<<"\t";
        }
    cout<<endl;
    }
    cout<<"result z:"<<-Matrix[0][cn-1]<<endl;
}

void Gaussian(pair<int, int> p)//行变换
{
    int  x = p.first;
    int y = p.second;
    double norm = Matrix[x][y];
    for( int i = 0 ; i < cn ; i++ )//主行归一化
    {
        Matrix[x][i] /= norm;
    }
    for( int i = 0 ; i < bn && i != x; i++ )
    {
        if( Matrix[i][y] != 0)
        {
            double tmpnorm = Matrix[i][y];
            for( int j = 0 ; j < cn ; j++ )
            {
                Matrix[i][j] = Matrix[i][j] - tmpnorm * Matrix[x][j];
            }
        }
    }
}

void solve()
{
    pair<int, int> t;
    while(1)
    {

        pnt();
        if( Pivot(t) == 0 )
        {
            return;
        }        
        cout<<t.first<<" "<<t.second<<endl;
        for( set<int>::iterator it = P.begin(); it != P.end()  ; it++ )
        {
            cout<<*it<<" ";
        }
        cout<<endl;
        Gaussian(t);
    }
}

int main()
{
    cin>>bn>>cn;
    for( int i = 0 ; i < bn ; i++ )
    {
        vector<double> vectmp;
        for( int j = 0 ; j < cn ; j++)
        {
            double tmp = 0;
            cin>>tmp;
            vectmp.push_back(tmp);
        }
        Matrix.push_back(vectmp);
    }

    for( int i = 0 ; i < bn-1 ; i++ )
    {
        P.insert(cn-i-2);
    }
    solve();
    return 0;
}

// 5 8
// 5 1 4 0 0 0 0 0
// 1 1 1 1 0 0 0 4
// 1 2 3 0 1 0 0 6
// -1 -1 -1 -1 0 1 0 -4
// -1 -2 -3 0 0 0 1 -6
/////////////////////////////////////
//glpk input:
///* Variables */
//var x1 >= 0;
//var x2 >= 0;
//var x3 >= 0;
///* Object function */
//maximize z: x1 + 14*x2 + 6*x3;
///* Constrains */
//s.t. con1: x1 + x2 + x3 <= 4;
//s.t. con2: x1  <= 2;
//s.t. con3: x3  <= 3;
//s.t. con4: 3*x2 + x3  <= 6;
//end;
/////////////////////////////////////
//myinput:
// 5 8
// 1 14 6 0 0 0 0 0
// 1 1 1 1 0 0 0 4
// 1 0 0 0 1 0 0 2
// 0 0 1 0 0 1 0 3
// 0 3 1 0 0 0 1 6
/////////////////////////////////////