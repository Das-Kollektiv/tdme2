#include <tdme/tests/PhysicsTest3.h>

extern void init_jvm();
extern java::lang::StringArray* make_args(int args, char** argv);

int main(int argc, char** argv)
{
    init_jvm();
    
    ::tdme::tests::PhysicsTest3::main(make_args(argc, argv));
    
    return 0;
}
