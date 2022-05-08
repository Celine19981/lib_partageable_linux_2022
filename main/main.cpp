
#include <iostream>
#include <dlfcn.h>
// #include "Composant1.h"
// #include "Composant2.h"

int main(int argc, char ** argv)
{
	int data1=3;
	int data2=5;

	int valeur1;
	int valeur2;
    int (*composant1)(int, int);
    int (*composant2)(int, int);
    char* (*getComposant1Version)(void);

	void* comp1 = dlopen("libComposant1.so", RTLD_LAZY);
	if (!comp1) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

	void* comp2 = dlopen("libComposant2.so", RTLD_LAZY);
	if (!comp2) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
	*(void **) (&composant1) = dlsym(comp1, "composant1");
	*(void **) (&composant2) = dlsym(comp2, "composant2");
    *(void **) (&getComposant1Version) = dlsym(comp1, "getComposant1Version");

	valeur1=(*composant1)(data1,data2);
	valeur2=composant2(data1,data2);

	std::cout << (*getComposant1Version)() << std::endl;
	std::cout << "valeur 1 :" << valeur1 << " valeur 2 :" << valeur2 << std::endl;
}
