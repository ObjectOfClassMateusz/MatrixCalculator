#include <iostream>
#include <windows.h>
using namespace std;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Macierz
{
public:
    friend void T(Macierz*&);
    Macierz(unsigned int , unsigned int);
    void Show();
    Macierz* operator + (Macierz* &);
    Macierz* operator - (Macierz* &);
    Macierz* operator * (Macierz* &);
protected:
    Macierz(unsigned int , unsigned int , double[]);
    double** Tab;
    unsigned x;
    unsigned y;
};

void Macierz::Show()
{
    if(this == NULL)
    {
        return ;
    }
    else
    {
        for (size_t i = 0; i < this->y; i++)
        {
            std::cout <<'[' ;
            for (size_t j = 0; j < this->x; j++)
            {
                cout<< this->Tab[i][j] ;
                if(j<this->x-1) {cout<< "_";}
            }std::cout <<']' <<'\n';
        }
          cout<<""<<endl;
    }
}

Macierz::Macierz(unsigned int K , unsigned int W)
{                              //      k1   k2
    this->Tab = new double*[K]; //  a[ []   [] ]                   k1 w1 w2   k2 w1 w2
    for(size_t i=0; i<K; i++) { this->Tab[i] = new double[W]; }//  a[[0][0]]  [[0][0]]

    for(size_t i=0; i<K; i++)
    {
        for(size_t a=0; a<W; a++)
        {
            cout<<"Give Element C:"<<i+1<<"R:"<<a+1<<" = ";
            cin>>this->Tab[i][a];//xd
        }
    }
    cout<<""<<endl;
    this->x = W;
    this->y = K;
}

Macierz::Macierz(unsigned int K , unsigned int W ,double tb_z [])
{
    this->Tab = new double*[K];
    for(size_t i=0; i<K; i++) { this->Tab[i] = new double[W]; }

    int x=0;

    for(size_t i=0; i<K; i++)
    {
        for(size_t a=0; a<W; a++)
        {

            this->Tab[i][a] = tb_z[x];
            x++;
        }
    }
    this->x = W;
    this->y = K;

}

Macierz* Macierz::operator+(Macierz*& L)
{//
    if((this->x != L->x) or (this->y != L->y))
    {
        return NULL;
    }
    else
    {
        double tab_zap[this->x * L->y];
         int x=0;

        for(size_t i=0; i<this->y; i++)
       {
            for(size_t a=0; a<this->x; a++)
            {
               tab_zap[x] = this->Tab[i][a] + L->Tab[i][a];
               x++;
            }
        }

       return new Macierz(this->y,this->x,tab_zap);

    }




}

Macierz* Macierz::operator-(Macierz*& L)
{
    if((this->x != L->x) or (this->y != L->y))
    {
        return NULL;
    }

    double tab_zap[this->x * L->y];

    int x=0;

    for(size_t i=0; i<this->y; i++)
    {
        for(size_t a=0; a<this->x; a++)
        {
            tab_zap[x] = this->Tab[i][a] - L->Tab[i][a];
            x++;
        }
    }

    return new Macierz(this->y,this->x,tab_zap);


}

Macierz* Macierz::operator*(Macierz*& L)
{//
    if(this->x != L->y)
    {
        return NULL;
    }
    else
    {//
        double tab_zap[this->y * L->x];//3*2 = 6
        double it=0;

//                              6
        for(int j=0; j<this->y * L->x;)
        {//                  3
             for(int i=0; i<this->y; i++)
             {//          1       2
                for(int e=0; e<L->x; e++)
                { //          0        3
                    for(int a=0; a<this->x;a++)
                    {//
                        it += (this->Tab[i][a] * L->Tab[a][e]);
                    }
                    tab_zap[j] = it;
                    j++;
                    it=0;
                }

             }
            //tab_zap[j] = it;
        }

        //           1     2



        return new Macierz(this->y,L->x,tab_zap);
    }
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void T(Macierz*&);
void T(Macierz*& M)
{
    unsigned int x_zapasowy = M->x;//3
    unsigned int y_zapasowy = M->y;//2
    double tab_zapasowe[x_zapasowy*y_zapasowy];//6
    int it=0;

    for(size_t i=0; i<x_zapasowy; i++)
    {//
        for(size_t a=0; a<y_zapasowy; a++)
        {
            tab_zapasowe[it] = M->Tab[a][i];
            it++;
        }
    }
    delete M;
    M = new Macierz(x_zapasowy,y_zapasowy,tab_zapasowe);
    M->Show();
}



int main()
{
    unsigned int k1 , k2 , w1 , w2;
    cout<<"Give the columns count of Matrix1 :";cin>>w1;
    cout<<"Give the rows count of Matrix1 :";cin>>k1;
    cout<<"Give the columns count of Matrix2 :";cin>>w2;
    cout<<"Give the rows count of Matrix1 :";cin>>k2;
//                           y x
    Macierz* A = new Macierz(k1,w1);
    Macierz* B = new Macierz(k2,w2);

    Macierz*D = *A + B;
    Macierz*E = *A - B;
    Macierz*C = *A * B;

    D->Show();
    E->Show();
    C->Show();

    char endd;
    cin>>endd;

  return 0;
}
