#include <bits/stdc++.h>

using namespace std;

int add_one(int item)
{
    return item+1;
}

int square(int item)
{
    return item*item;
}

int minus_ten(int item)
{
    return item-10;
}

template<int val>
bool greater_than_value(int item)
{
    if(item>val)
        return true;
    return false;
}
int main()
{
    vector<int> data { 7, 4, 5, 6, 3, 8, 10 };

    // the data pipline : add_one , square , select <=70, take the largest 2 , -10

    // 1-Imperative code 

    /*for(auto elem : data)
    {
        elem = minus_ten(square(add_one(elem)));

        cout<<elem<<endl;
        // if you need to select <= 70 you will need to add extra if condition and if you need larges two you will need sorting and selecting outside the loop
    }*/

    // 2- Declarative

    transform(data.begin(),data.end(),data.begin(),add_one);
    transform(data.begin(),data.end(),data.begin(),square);
    data.erase(remove_if(data.begin(),data.end(),greater_than_value<70>),data.end());
    sort(data.begin(), data.end());
	data.erase(data.begin()+2, data.end());
    transform(data.begin(),data.end(),data.begin(),minus_ten);

    for (auto item : data)
	{
		cout << item << endl;
	}

    return 0;
}