#include <tdme/tools/particlesystem/TDMEParticleSystem.h>

extern void init_jvm();
extern java::lang::StringArray* make_args(int args, char** argv);

int main(int argc, char** argv)
{
    init_jvm();
    
    ::tdme::tools::particlesystem::TDMEParticleSystem::main(argc, argv);
    
    return 0;
}
