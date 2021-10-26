#include <list>
#include <QDebug>

int main(int argc, char *argv[])
{
    std::list<int> lista;
    for(int i=0; i < 10;++i)
        lista.push_back(i);

    foreach(int x, lista)
    {
        if (x == 5)
        {
            qDebug() << x;
            lista.remove(x);
        }
    }
    foreach (int x, lista) {
        qDebug() << x;
    }
}
