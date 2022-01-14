#include <bits/stdc++.h>

using namespace std;
enum ProductType
{
    Food,
    Beverage,
    RawMaterial
};

struct Order
{
    int OrderID;
    int ProductIndex;
    double Quantity;
    double UnitPrice;
};

tuple<double, double> product_paramters_food(int ProductIndex)
{
    return { ProductIndex / (double)(ProductIndex + 100), ProductIndex / (double)(ProductIndex + 300) };

}

tuple<double, double> product_paramters_beverage(int ProductIndex)
{
    return { ProductIndex / (double)(ProductIndex + 300), ProductIndex / (double)(ProductIndex + 400) };
}

tuple<double, double> product_paramters_rawmaterial(int ProductIndex)
{
    return { ProductIndex / (double)(ProductIndex + 400), ProductIndex / (double)(ProductIndex + 700) };
}

double calculate_discount(tuple<double,double> (*ProductParamterCalc)(int), Order r)
{
    auto [x1,x2]  = ProductParamterCalc(r.ProductIndex);
    return x1* r.Quantity + x2* r.UnitPrice;
}

int main()
{
    auto A = &product_paramters_food;
    auto B = &product_paramters_beverage;
    auto C = &product_paramters_rawmaterial;

    Order o {10, 100, 20, 4};

    ProductType product = Food;
    auto p = ((product==Food) ?A :((product==Beverage)?B :C));
    double discount = calculate_discount(p, o);
	cout << discount << endl;


    return 0;
}