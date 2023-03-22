#include <gtest/gtest.h>
#include "ip_filter.h"

TEST(AppCommonTests, VersionAssertions) {
    char app_path[] = "app_path";
    char ip_mock_path[] = "ip_filter.tsv";
    const char *argv[] = { app_path, ip_mock_path, NULL };
    ip_filter *filter = new ip_filter();
    std::string md5_digest = filter->perform_read_and_sort(argv);
    // perform_read_and_sort(argv);
    // there should be receiving string from function, converting it to md5 and comparing with ethalon
    // but let's consider it works as expected ;)
    EXPECT_EQ(md5_digest, "24e7a7b2270daee89c64d3ca5fb3da1a");
}
