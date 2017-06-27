#include <tdme/tests/PhysicsTest2.h>

extern void init_jvm();
extern java::lang::StringArray* make_args(int args, char** argv);

int main(int argc, char** argv)
{
    init_jvm();
    
    ::tdme::tests::PhysicsTest2::main(make_args(argc, argv));
    
    return 0;
}
