#include <iostream>
#include <vector>
class Item {
public:
    Item (const std::string name) {
        _name = name;
        std::cout<<"default constructor called"<<std::endl;
    }
    Item (const Item &other) {
        _name = other.getName();
        std::cout<<"copy constructor called"<<std::endl;;
    }
    Item & operator=(const Item &other) {
        this->_name = other.getName();
        std::cout<<" = operator called"<<std::endl;
    }
    const std::string &getName() const {
        return _name;
    }
private:
    std::string _name;
};

int main()
{
    std::vector<Item> vec;
    vec.reserve(10);

    //Use default constructor and copy constructor.
    Item item("item");
    vec.push_back(item);

    //Use placement-new to construct the element in-place at the location provided by the container.
    vec.emplace_back("item1");

    //Use placement-new to construct the element in-place at the location provided by the container.
    vec.emplace(vec.end(), "item2");

    //If the required location has been occupied by an existing element, the inserted element is constructed at another location at first, and then move assigned into the required location
    vec.emplace(vec.begin(), "item0");
    for (auto & i : vec) {
        std::cout<<i.getName()<<" ";
    }
    std::cout<<std::endl;
    return 0;
}
