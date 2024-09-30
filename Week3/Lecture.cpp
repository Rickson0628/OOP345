#include <iostream>

class Horse
{
    unsigned double age;             // <-- this is an instance variable
    unsigned double id;              // <-- this is an instance variable
public:
    static unsigned noHorses; // <-- this is a class variable

    Horse(unsigned a);
    ~Horse();

    void display() const;
};
unsigned Horse::noHorses = 0; // this is how class variables are initialized

// the constructor increments the class variable, but is not initialize it
Horse::Horse(unsigned a) : age{ a }, id{ ++Horse::noHorses } {}

// the destructor decrements the class variable
Horse::~Horse() { --Horse::noHorses; }

void Horse::display() const
{
    std::cout << "Horse " << id << " is " << age << " years old\n";
}

int main()
{
    // no need for an instance to access the class variable
    std::cout << Horse::noHorses << " horses\n";

    {
        // create a local scope
        Horse silver(3), northernDancer(4);

        silver.display();
        northernDancer.display();

        std::cout << Horse::noHorses << " horses" << std::endl;
        std::cout << silver.noHorses << " horses" << std::endl;
        std::cout << northernDancer.noHorses << " horses" << std::endl;

        // local scope ends: variables created in this scope will be destroyed
    }

    std::cout << Horse::noHorses << " horses" << std::endl;
}