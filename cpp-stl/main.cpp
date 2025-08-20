#include <iostream>
#include <string>

struct address
{
    char* name;
    long int number;
    char* city;
    char* bloodtype[2];

    void set_name(char* new_name)
    {
        name = new_name;
    }

    char* get_name();
};

char* address::get_name()
{
    return name;
}

int main()
{
    address myaddress;
    char* name;
    strcpy(name, "Yusuf");
    myaddress.set_name(name);
    

    return EXIT_SUCCESS;
}