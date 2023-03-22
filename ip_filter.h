//
//  ip_filter.h
//  02.cpp14
//
//  Created by Dmitrii Zavadskii on 23.03.2023.
//

#ifndef ip_filter_h
#define ip_filter_h

#include "md5.h"

class ip_address;

class ip_filter {
public:
    std::string perform_read_and_sort(const char **argv);
private:
    void prepare_data_vector(const char **argv, std::vector<ip_address> &general_sorted_ips_vector);
    void perform_task_one_vector(const std::vector<ip_address> &general_sorted_ips_vector);
    void perform_task_two_vector(const std::vector<ip_address> &general_sorted_ips_vector);
    void perform_task_three_vector(const std::vector<ip_address> &general_sorted_ips_vector);
    void perform_task_four_vector(const std::vector<ip_address> &general_sorted_ips_vector);
};

#endif /* ip_filter_h */
