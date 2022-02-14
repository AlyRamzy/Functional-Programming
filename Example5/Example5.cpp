#include <bits/stdc++.h>

#include"compose.h"
using namespace std;

// Structs for data storing
struct Order
{
    double cost;
    int date; // days to deliver 
};

struct Invoice
{
    double cost;
};

struct Shipping
{
    double cost;
    int ShipperID;
};

struct Freight
{
    double cost;
};

struct Availability
{
    int date;
};

struct ShippingDate
{
    int date;
};

// Enums for process configuration
enum InvoiceChoice
{
    Inv1,
    Inv2,
    Inv3,
    Inv4,
    Inv5
};

enum ShippingChoice
{
    Sh1,
    Sh2,
    Sh3,
};

enum FreightChoice
{
    Fr1,
    Fr2,
    Fr3,
    Fr4,
    Fr5,
    Fr6
};

enum AvailabilityChoice
{
    AV1,
    AV2,
    AV3,
    AV4
};

enum ShippingDateChoice
{
    SD1,
    SD2,
    SD3,
    SD4,
    SD5
};

struct ProcessConfiguration
{
    InvoiceChoice invoiceChoice;
    ShippingChoice shippingChoice;
    FreightChoice freightChoice;
    AvailabilityChoice availabilityChoice;
    ShippingDateChoice shippingDateChoice;
};

// Invoice Functions
inline static Invoice calcInvoice1(Order o)
{
    Invoice invoice{ o.cost * 1.1};
    return invoice;
}
inline static Invoice calcInvoice2(Order o)
{
    Invoice invoice{ o.cost * 1.2};
    return invoice;
}
inline static Invoice calcInvoice3(Order o)
{
    Invoice invoice{ o.cost * 1.3};
    return invoice;
}
inline static Invoice calcInvoice4(Order o)
{
    Invoice invoice{ o.cost * 1.4};
    return invoice;

}
inline static Invoice calcInvoice5(Order o)
{
    Invoice invoice{ o.cost * 1.5};
    return invoice;
}

// Shipping Functions
inline static Shipping calcShipping1(Invoice i)
{
    Shipping s;
    s.ShipperID = (i.cost > 1000) ? 1 : 2;
    s.cost = i.cost;
    return s;
}
inline static Shipping calcShipping2(Invoice i)
{
    Shipping s;
    s.ShipperID = (i.cost > 1100) ? 1 : 2;
    s.cost = i.cost;
    return s;
}
inline static Shipping calcShipping3(Invoice i)
{
    Shipping s;
    s.ShipperID = (i.cost > 1200) ? 1 : 2;
    s.cost = i.cost;
    return s;
}

// Freight Functions
inline static Freight calcFreightCost1(Shipping s)
{
    Freight f;
    f.cost = (s.ShipperID == 1) ? s.cost * 0.25 : s.cost * 0.5;
    return f;
}
inline static Freight calcFreightCost2(Shipping s)
{
    Freight f;
    f.cost = (s.ShipperID == 1) ? s.cost * 0.28 : s.cost * 0.52;
    return f;
}
inline static Freight calcFreightCost3(Shipping s)
{
    Freight f;
    f.cost = (s.ShipperID == 1) ? s.cost * 0.3 : s.cost * 0.6;
    return f;
}
inline static Freight calcFreightCost4(Shipping s)
{
    Freight f;
    f.cost = (s.ShipperID == 1) ? s.cost * 0.35 : s.cost * 0.65;
    return f;
}
inline static Freight calcFreightCost5(Shipping s)
{
    Freight f;
    f.cost = (s.ShipperID == 1) ? s.cost * 0.15 : s.cost * 0.2;
    return f;
}
inline static Freight calcFreightCost6(Shipping s)
{
    Freight f;
    f.cost = (s.ShipperID == 1) ? s.cost * 0.1 : s.cost * 0.15;
    return f;
}

// Availability Functions

inline static Availability calcAvailability1(Order o)
{
    Availability a;
    a.date = 3 + o.date;
    return a;
}
inline static Availability calcAvailability2(Order o)
{
    Availability a;
    a.date = 2 + o.date;
    return a;
}
inline static Availability calcAvailability3(Order o)
{
    Availability a;
    a.date = 1 + o.date;
    return a;
}
inline static Availability calcAvailability4(Order o)
{
    Availability a;
    a.date = 4 + o.date;
    return a;
}

// ShippingDate Functions

inline static ShippingDate calcShippingDate1(Availability a)
{
    ShippingDate s;
    s.date = a.date + 1;
    return s;
}
inline static ShippingDate calcShippingDate2(Availability a)
{
    ShippingDate s;
    s.date = a.date + 2;
    return s;
}
inline static ShippingDate calcShippingDate3(Availability a)
{
    ShippingDate s;
    s.date = a.date + 3;
    return s;
}
inline static ShippingDate calcShippingDate4(Availability a)
{
    ShippingDate s;
    s.date = a.date + 4;
    return s;
}
inline static ShippingDate calcShippingDate5(Availability a)
{
    ShippingDate s;
    s.date = a.date + 5;
    return s;
}

////////////////////////////////////////// AvailabilityPath //////////////////////////////////////////////////////////
// List of AvailabilityFunctions
vector<pair<AvailabilityChoice,std::function< Availability(const Order&)>>> AvailabilityFunctions
    {
        {AvailabilityChoice::AV1,calcAvailability1},
        {AvailabilityChoice::AV2,calcAvailability2},
        {AvailabilityChoice::AV3,calcAvailability3},
        {AvailabilityChoice::AV4,calcAvailability4}
    };

// List of ShippingDateFunctions
vector<pair<ShippingDateChoice,std::function< ShippingDate(const Availability&)>>> ShippingDateFunctions
    {
        {ShippingDateChoice::SD1,calcShippingDate1},
        {ShippingDateChoice::SD2,calcShippingDate2},
        {ShippingDateChoice::SD3,calcShippingDate3},
        {ShippingDateChoice::SD4,calcShippingDate4},
        {ShippingDateChoice::SD5,calcShippingDate5},
    };

//  Return AvailabilityPath Composed Funcrtion 
inline static std::function<ShippingDate(Order)> AvailabilityPathFunc(ProcessConfiguration c)
{
    auto cloneAvailable = AvailabilityFunctions;
    cloneAvailable.erase(remove_if(cloneAvailable.begin(),cloneAvailable.end(),[c](auto availablefunc){ return !(c.availabilityChoice==availablefunc.first); }),cloneAvailable.end());
    auto availableFunc = cloneAvailable[0].second;

    auto cloneShippingDate = ShippingDateFunctions;
    cloneShippingDate.erase(remove_if(cloneShippingDate.begin(),cloneShippingDate.end(),[c](auto shippingdatefunc){ return !(c.shippingDateChoice==shippingdatefunc.first); }),cloneShippingDate.end());
    auto shippingdateFunc = cloneShippingDate[0].second;

    return compose(shippingdateFunc,availableFunc);
}
////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////// Invoice Path //////////////////////////////////////////
// List of InvoiceFunctions
vector<pair<InvoiceChoice,std::function< Invoice(const Order&)>>> InvoiceFunctions
    {
        {InvoiceChoice::Inv1,calcInvoice1},
        {InvoiceChoice::Inv2,calcInvoice2},
        {InvoiceChoice::Inv3,calcInvoice3},
        {InvoiceChoice::Inv4,calcInvoice4},
        {InvoiceChoice::Inv5,calcInvoice5}
    };

// List of ShippingFunctions
vector<pair<ShippingChoice,std::function< Shipping(const Invoice&)>>> ShippingFunctions
    {
        {ShippingChoice::Sh1,calcShipping1},
        {ShippingChoice::Sh2,calcShipping2},
        {ShippingChoice::Sh3,calcShipping3}
    };

// List of frieghtFunctions
vector<pair<FreightChoice,std::function< Freight(const Shipping&)>>> frieghtFunctions
    {
        {FreightChoice::Fr1,calcFreightCost1},
        {FreightChoice::Fr2,calcFreightCost2},
        {FreightChoice::Fr3,calcFreightCost3},
        {FreightChoice::Fr4,calcFreightCost4},
        {FreightChoice::Fr5,calcFreightCost5},
        {FreightChoice::Fr6,calcFreightCost6}
    };

//  Return InvoicePath Composed Funcrtion 
inline static std::function<Freight(Order)> InvoicePathFunc(ProcessConfiguration c)
{
    auto cloneInvoiceFunctions = InvoiceFunctions;
    cloneInvoiceFunctions.erase(remove_if(cloneInvoiceFunctions.begin(),cloneInvoiceFunctions.end(),[c](auto invoiceFunc){ return !(c.invoiceChoice==invoiceFunc.first); }),cloneInvoiceFunctions.end());
    auto invoiceFunc = cloneInvoiceFunctions[0].second;

    auto cloneShippingFunctions = ShippingFunctions;
    cloneShippingFunctions.erase(remove_if(cloneShippingFunctions.begin(),cloneShippingFunctions.end(),[c](auto shippingFunc){ return !(c.shippingChoice==shippingFunc.first); }),cloneShippingFunctions.end());
    auto shippingFunc = cloneShippingFunctions[0].second;

    auto clonefrieghtFunctions = frieghtFunctions;
    clonefrieghtFunctions.erase(remove_if(clonefrieghtFunctions.begin(),clonefrieghtFunctions.end(),[c](auto frieghtFunc){ return !(c.freightChoice==frieghtFunc.first); }),clonefrieghtFunctions.end());
    auto frieghtFunc = clonefrieghtFunctions[0].second;

    return compose(frieghtFunc,shippingFunc,invoiceFunc);
}
///////////////////////

//Adjusted Cost
inline static double AdjustCost(Order r,std::function<Freight(Order)> calcFreigt, std::function<ShippingDate(Order)> calcShippingDate)
{

    Freight f = calcFreigt(r);
    ShippingDate s = calcShippingDate(r);
    cout<<"Days To Shipping : " << s.date<<endl;

    double cost = (s.date<5) ? f.cost + 1000 : f.cost + 500;

    ///Finall Cost 
    return cost;
}


//Adjusted Cost for Order
inline static std::function<double(Order&)> CalcAdjustedCostofOrder(ProcessConfiguration c)
{
    return [c](Order r){return AdjustCost(r,InvoicePathFunc(c),AvailabilityPathFunc(c));};
}

int main()
{
    ProcessConfiguration processConfiguration;
    Order order;
    processConfiguration.invoiceChoice = InvoiceChoice::Inv3;
    processConfiguration.shippingChoice = ShippingChoice::Sh2;
    processConfiguration.freightChoice = FreightChoice::Fr3;
    processConfiguration.availabilityChoice = AvailabilityChoice::AV2;
    processConfiguration.shippingDateChoice = ShippingDateChoice::SD2;
    order.date = 2;
    order.cost = 2000;
    cout<<CalcAdjustedCostofOrder(processConfiguration)(order)<<endl;


    return 0;
}