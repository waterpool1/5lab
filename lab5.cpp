
#include <iostream>
#include <clocale>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class IVehicle
{
public:
    virtual bool drive(int kilometers) = 0;
    virtual void refuel() = 0;
    virtual void printStatus() = 0;
};
class AbstractCar : public IVehicle
{
public:
    int tank;
    int fuelrate;
    int fuel;
    int mileage;
    bool drive(int kilometres)
    {
        bool tffuel = true;
        if (fuel >= fuelrate * kilometres) {
            fuel = fuel - fuelrate * kilometres;
            cout << "Пройдено " << kilometres << "км " << endl;
            mileage += kilometres;

        }
        else {
            cout << "Не хватает топлива " << endl;
            tffuel = false;
        }
        return tffuel;
    };
    void refuel()
    {
        fuel = tank; cout << "Вы заправились" << endl;
    };
    void printStatus()
    {
        int pr;
        float pp = 100 * fuel / tank;
        cout << "Топливо: " << fuel / 1000 << "/" << tank / 1000 << " ";
        pr = 10 * fuel / tank;
        cout << "Пробег: " << mileage << "км" << endl;
    };
};
class Sedan : public AbstractCar
{
public:
    Sedan()
    {
        tank = 40000;
        fuelrate = 80;
        fuel = 0;
        mileage = 0;
    }
};
class Bus : public AbstractCar
{
public:
    Bus()
    {
        tank = 120000;
        fuelrate = 200;
        fuel = 0;
        mileage = 0;
    }
};
class Suv : public AbstractCar
{
public:
    Suv()
    {
        tank = 70000;
        fuelrate = 130;
        fuel = 0;
        mileage = 0;
    }
};

class Bicycle : public IVehicle
{
    int mileage;
public:
    Bicycle()
    {
        mileage = 0;
    }
    bool drive(int kilometres)
    {
        cout << "Вы проехали " << kilometres << "км " << endl;
        mileage += kilometres;
        return true;
    };
    void refuel() { cout << "Велосипед нельзя заправить :/" << endl; };
    void printStatus()
    {
        cout << "Пробег: " << mileage << "км" << endl;
    };
};
struct RoutePoint
{
    int xKm = 0;
    int yKm = 0;
    string name;
};
class Route
{
public:
    vector<RoutePoint> vpoint;
    void addPoint(const RoutePoint& point)
    {
        vpoint.push_back(point);

    };
    void run(IVehicle* vehicle)
    {
        if (vpoint.size() < 2)
        {
            cout << "Ошибка. Добавьте более 1 точки маршрута." << endl;
            return;
        }
        else
        {
            int travel = 0;
            for (int i = 1; i < vpoint.size(); i++)
            {
                travel = sqrt(pow(vpoint[i].xKm - vpoint[i - 1].xKm, 2) + pow(vpoint[i].yKm - vpoint[i - 1].yKm, 2));
                if (vehicle->drive(travel) == true)
                {
                    cout << "Вы проехали с точки '" << vpoint[i - 1].name << "' в точку '" << vpoint[i].name << "' " << endl;
                }
                else
                {
                    vehicle->refuel();
                    --i;
                }
            }
        }
    };

};

int main(int argc, char* argv[])
{
    setlocale(LC_CTYPE, "rus");
    Route route;
    RoutePoint routepoint;
    string xstr, ystr, namestr;
    int xx = 0, yy = 0;
    ifstream fin;
    cout << endl << endl;
    if (argc >= 2)
    {
        fin.open(argv[1]);
        if (fin.is_open())
        {
            cout << "-----Файл открыт-----" << endl;


            while (!fin.eof())
            {
                fin >> xstr;
                fin >> ystr;
                fin >> routepoint.name;
                routepoint.xKm = stoi(xstr);
                routepoint.yKm = stoi(ystr);
                route.addPoint(routepoint);
                cout << xstr << " " << ystr << " " << routepoint.name << endl;
            }
        }
        else
        {
            cout << "-----Файл не открыт-----" << endl;
        }

    }
    else
    {
        cout << "-----Параметров меньше двух-----" << endl;
    }
    IVehicle* vehicles[4] = { new Sedan, new Suv, new Bus, new Bicycle }; // Создаем объекты классов для моделирования 
    for (int i = 0; i < 4; ++i)
    {
        route.run(vehicles[i]);
        cout << "------------" << endl << endl;
    }
   /* Route routes[2];
    routes[0].addPoint(RoutePoint(0, 0, "Point1"));
    routes[0].addPoint(RoutePoint(3, 4, "Point2"));
    routes[0].addPoint(RoutePoint(10, 10, "Point3"));
    routes[0].addPoint(RoutePoint(50, 50, "Point4"));
    routes[1].addPoint(RoutePoint(50, 50, "Point1.2"));
    routes[1].addPoint(RoutePoint(140, 100, "Point2.2"));
    routes[1].addPoint(RoutePoint(180, 190, "Point3.2"));
    IVehicle* vehicles[4] = { new Sedan, new Suv, new Bus, new Bicycle }; // Создаем объекты классов для моделирования 
    for (int i = 0; i < 4; ++i)
    {
        routes[0].run(vehicles[i]);
        routes[1].run(vehicles[i]);
        cout << "------------" << endl << endl;
    }*/
    return 0;
}