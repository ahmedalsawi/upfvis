#include <UPFEngine.h>

int main(int argc, char **argv)
{
    UPFEngine upf_instance;

    upf_instance.run();
    upf_instance.dump_upf();
}