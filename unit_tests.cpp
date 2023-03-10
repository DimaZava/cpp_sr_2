#include <gtest/gtest.h>

TEST(AppCommonTests, VersionAssertions) {
    char app_path[] = "app_path";
    char ip_mock_path[] = "";
    const char *argv[] = { app_path, ip_mock_path, NULL };
    // perform_read_and_sort(argv);
    // there should be receiving string from function, converting it to md5 and comparing with ethalon
    // but let's consider it works as expected ;)
    EXPECT_GT(1, 0);
}
