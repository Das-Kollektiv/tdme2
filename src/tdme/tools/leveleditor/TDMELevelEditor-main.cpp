#include <tdme/tools/leveleditor/TDMELevelEditor.h>

extern void init_jvm();
extern java::lang::StringArray* make_args(int args, char** argv);

int main(int argc, char** argv)
{
    init_jvm();
    
    ::tdme::tools::leveleditor::TDMELevelEditor::main(argc, argv);
    
    return 0;
}
