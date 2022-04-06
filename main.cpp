#include <stdlib.h>
#include <stdio.h>
class Quadra
        {
protected:
    unsigned** tab;
    int row;  					//ряд
    int col;						//столбец
    int degree;
public:
            Quadra(int);
            ~Quadra();
};
Quadra::Quadra(int n)
{
    degree = n;
    tab = new unsigned* [degree];
    for(row=0; row<degree; row++)
        tab[row]=new unsigned [degree];
    for(row=0; row<degree; row++)
        for(col=0; col<degree; col++)
            tab[row][col] = 0;
}
class Magic : public Quadra
        {
/*private:
    unsigned** tab;
    int row;  					//ряд
    int col;						//столбец
    int degree;*/
public:
            Magic(int);
            void print();
    void Delair();
    int reflect(int);
};
Magic::Magic(int n) : Quadra(n){}

Quadra::~Quadra()      				//деструктор
{
    for(row=0; row<degree; row++)
        delete [] tab[row];
    delete []tab;
}

void Magic::print() 				//функция вывода
{
    int degree2;
    int len=0;
    degree2 = degree*degree;
    while(degree2>0)
    {
        degree2/=10;
        len++;
    }
    printf("\t\t Итоговый квадрат:\n");
    for(row=0; row<degree; row++)
    {
        printf("\t\t");
        for(col=0; col<degree; col++)
            printf("%0*d   ", len, tab[row][col]);
        putchar('\n');
        putchar('\n');
    }
    return;
}

int Magic::reflect(int k)		//функция обработки случая когда выходим за левую границу квадрата
{
    if(k<0)
        return (k+degree);
    return k;
}

void Magic::Delair()						//метод Делаира
{
    int num, half_degree=degree/2;
    int col1;	//переменная, которая нужна для проверки на выход за границу массива
    unsigned tab2[degree][degree];
    row = degree-1;
    col = 0;
    for(num=degree-1; num>half_degree; num--)      	 //начало заполнения последней строки
    {
        tab[row][col]=num;
        col++;
    }
    for(num=half_degree-1; num>=0; num--)
    {
        tab[row][col]=num;
        col++;
    }
    tab[row][col]=half_degree;		 //конец заполнения последней строки
    for(row=degree-1; row>0; row--)						  	 //заполнение таблицы с помощью смещения значений последней строки
        for(col=0; col<degree; col++)
        {
            col1 = reflect(col-1);
            tab[row-1][col1]=tab[row][col];
        }
    int degree2;
    int len=0;
    degree2 = degree*degree;
    while(degree2>0)
    {
        degree2/=10;
        len++;
    }
    printf("\t\tНачальный квардрат:\n");
    for(row=0; row<degree; row++)
    {
        printf("\t\t");
        for(col=0; col<degree; col++)
            printf("%0*d   ", len, tab[row][col]);
        putchar('\n');
        putchar('\n');
    }
    printf("\n\n");
    for(row=0; row<degree; row++)   		   	//копирование массива  tab в tab2
        for(col=0; col<degree; col++)
            tab2[row][col]=tab[row][col];
    for(row=0; row<degree; row++)
    {
        for(col=0; col<degree; col++)
            printf("%0*d   ", len, tab2[row][col] * degree);
        printf("\t");
        for(col=0; col<degree; col++)
            printf("%0*d   ", len, tab2[degree-1-row][col] + 1);
        putchar('\n');
        putchar('\n');
    }
    printf("\n\n");
    for(row=0; row<degree; row++)		//получение магического квадрата
        for(col=0; col<degree; col++)
        {
            tab[row][col]=(tab2[row][col]*degree) + (tab2[degree-1-row][col] + 1); //
        }
}

int main(int argc, char* argv[])
{
    if(argc != 2) 		//если не ввели ничего или ввели больше аргументов
        return puts("Ошибка: нужно было ввести только длину магического квадрата");
    int n = atoi(argv[1]);
    if((n%2)==0)		//если ввели чётное число(длину магического квадрата)
        return puts("Ошибка: нужно было ввести нечётную длину магического квадрата");
    Magic mag(n);
    mag.Delair();
    mag.print();
    return 0;
}