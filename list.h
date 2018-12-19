#ifndef LIST
#define LIST
#include <iostream>
#include <string>
using namespace std;
template<typename T>
class Node{
    public:
        Node* pnext;
        T data;
        Node():T(), pnext(nullptr){}
        Node (T data=T() , Node *pnext = nullptr){//Используется, если при вызове функции не указываются параметры
//        Node (T data , Node *pnext){//Используется, если при вызове функции не указываются параметры
            this->data=data;
            this->pnext=pnext;

        }
};
template<typename T>
class List{
    public:
        List();
        ~List();
        void clear();
        void pop_front();
        void push_back(T data); //Добавиться в конец списка
        int GetSize(){return Size;}
        void setSize(int i){Size=i;}
        void setHead(){head=nullptr;}
        T& operator[](const int index);
    private:
        int Size;
        Node<T> *head;
};
template<typename T>
List<T>::~List()
{
    clear();
    cout<<"Вызвался"<<endl;
}
template<typename T>
void List<T>::clear()
{
    while(Size)
    {
        pop_front();
    }
}
template<typename T>
void List<T>::pop_front()
{
    Node <T>*temp=head;
    head=head->pnext;
    delete temp;
    Size--;
}
template<typename T>
void List<T>::push_back(T data)
{
    if(head==nullptr)
    {
        head=new Node<T> (data);
    }
    else
    {
        Node<T> *current=this->head;
        while(current->pnext!=nullptr)
        {
            current=current->pnext;
        }
        current->pnext=new Node<T> (data);
    }
    Size++;
}
template<typename T>
T &List<T>::operator[](const int index)
{
    int counter=0;
   Node<T> *current=this->head;
   while(current!=nullptr)
   {
        if (counter==index)
        {
            return current->data;
        }
        current=current->pnext;
        ++counter;
   }

}
template<typename T>
List<T>::List()
{
    Size=0;
    head=nullptr;
}

template <typename T>
class MyIterator
{
private:
Node<T>* cur;

public:
Node<T>* get()
{
return cur;
}
int operator !=(MyIterator<T> rigth)
{
if (cur == rigth.cur)
    return 0;
else
    return 1;
}

friend int operator ==(MyIterator<T> left, MyIterator<T> rigth);

Node<T> * operator ->()
{
return &*cur;
}
MyIterator<T> operator ++()
{
    cur++;
    return *this;
}
friend MyIterator<T> operator +(MyIterator <T> left, int num);
MyIterator() { cur = NULL; }
MyIterator(Node<T>* it) :cur(it) {}
~MyIterator()
    {
         cur = nullptr;
    }
};






template <typename T>
int operator ==(MyIterator<T> left, MyIterator<T> rigth)
{
if (left.cur == rigth.cur)
    return 1;
else
    return 0;
}

template <typename T>
MyIterator<T>& operator +(MyIterator < T> left, int num)
{
MyIterator<T> res = left;
for (int i=0; i<num; ++i)
    res.cur=res.cur->pnext;
return left;
}

template <typename T>
int operator !=(Node<T>* left, MyIterator<T> rigth)
{
if (left == rigth.cur)
    return 0;
else
    return 1;
}

#endif
