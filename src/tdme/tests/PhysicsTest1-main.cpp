#include <tdme/tests/PhysicsTest1.h>

extern void init_jvm();
extern java::lang::StringArray* make_args(int args, char** argv);

int main(int argc, char** argv)
{
    init_jvm();
    
    ::tdme::tests::PhysicsTest1::main(argc, argv);
    
    return 0;
}
