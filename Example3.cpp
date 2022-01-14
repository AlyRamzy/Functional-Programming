#include <bits/stdc++.h>

using namespace std;

struct Order
{
    double cost;
    double discount;
};

using QualifierFunc = std::function< bool(const Order&) >;
using DiscountFunc  = std::function< double(const Order&) >;
using Rule          = std::pair< QualifierFunc, DiscountFunc >;

bool isAQualified(const Order& r)
{
    return false;
}

double A(const Order& r)
{

    return 1;
}

bool isBQualified(const Order& r)
{
    return true;
}

double B(const Order& r)
{

    return 1;
}

bool isCQualified(const Order& r)
{
    return true;
}

double C(const Order& r)
{

    return 1;
}

vector<Rule>  GetDiscountRules()
{
    vector<Rule> DiscountRules
    { 
        { isAQualified, A },
        { isBQualified, B },
        { isCQualified, C } 
    };

    return DiscountRules;
}

Order GetOrderwithDiscount(Order R,vector<Rule> rules)
{
    rules.erase(remove_if(rules.begin(),rules.end(),[&R](Rule rule){ return !rule.first(R); }),rules.end()); // capture list [&R]
    vector<double> discounts(rules.size());

    transform(rules.begin(),rules.end(),discounts.begin(),[&R](Rule rule){return rule.second(R);});

    sort(discounts.begin(),discounts.end());
    if(discounts.size()>3)
        discounts.erase(discounts.begin()+3, discounts.end());
    double average = discounts.empty() ? 0 : std::accumulate(discounts.begin(), discounts.end(), 0)*1.0/discounts.size();

    Order order {R.cost , average};

    return order;
}

int main()
{
    vector<Order> orders { {10,0}, {20,0} };

    vector<Order> orders_with_discount(orders.size());

    transform(orders.begin(),orders.end(),orders_with_discount.begin(),[](Order order){return GetOrderwithDiscount(order, GetDiscountRules());});
    

    for(auto order : orders_with_discount)
    {
        cout<<order.cost<<"\t"<<order.discount<<endl;
    }
}

// https://www.geeksforgeeks.org/transform-c-stl-perform-operation-elements/
// https://www.geeksforgeeks.org/stdremove-stdremove_if-c/
// https://en.cppreference.com/w/cpp/algorithm/accumulate
// lambda function (capture list) , allocators ,  move semantics without copy