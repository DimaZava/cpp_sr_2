#include <string>
#include "ip_filter.h"

#define UNUSED(variable) (void)variable

int main(int argc, char const *argv[])
{
    std::string md5_digest = "";
    ip_filter *filter = new ip_filter();
    try
    {
        md5_digest = filter->perform_read_and_sort(argv);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    UNUSED(argc);
    return md5_digest == "24e7a7b2270daee89c64d3ca5fb3da1a" ? 0 : -1;
}
