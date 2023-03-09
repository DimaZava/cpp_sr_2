#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <numeric>
#include <cstdlib>

#define UNUSED(variable) (void)variable

class ip_address;

int perform_read_and_sort(const char **argv);
int prepare_data(const char **argv, std::multimap<uint, ip_address, std::greater<uint>> &general_sorted_ips);
void perform_task_one(std::multimap<uint, ip_address, std::greater<uint>> &general_sorted_ips);
void perform_task_two(std::multimap<uint, ip_address, std::greater<uint>> &general_sorted_ips);
void perform_task_three(std::multimap<uint, ip_address, std::greater<uint>> &general_sorted_ips);
void perform_task_four(std::multimap<uint, ip_address, std::greater<uint>> &general_sorted_ips);

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;
    
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));
        
        start = stop + 1;
        stop = str.find_first_of(d, start);
    }
    
    r.push_back(str.substr(start));
    
    return r;
}

class ip_address {
public:
    std::string string_representation;
    std::vector<uint> octets;
    
    ip_address(std::string string_representation) {
        this->string_representation = string_representation;
        
        std::vector<std::string> string_vector = split(string_representation, '.');
        auto octets_formatter = [](std::string item) {
            return uint(std::stoul(item));
        };
        std::transform(string_vector.begin(), string_vector.end(), std::back_inserter(octets), octets_formatter);
        // std::vector<uint> test = std::vector<uint>(string_vector.begin(), string_vector.end(), [](std::string item) {
        //     return uint(std::stoul(item));
        // });
        // this->octets
    }
};

int main(int argc, char const *argv[])
{
    try
    {
        perform_read_and_sort(argv);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    UNUSED(argc);
    return 0;
}

int perform_read_and_sort(const char **argv) {
    // read data
    std::multimap<uint, ip_address, std::greater<uint>> general_sorted_ips;
    if (prepare_data(argv, general_sorted_ips) == -1) {
        return  -1;
    }
    perform_task_one(general_sorted_ips);
    perform_task_two(general_sorted_ips);
    perform_task_three(general_sorted_ips);
    perform_task_four(general_sorted_ips);
    // std::cout << "Voila, finish!" << std::endl;
    return 0;
}

int prepare_data(const char **argv, std::multimap<uint, ip_address, std::greater<uint>> &general_sorted_ips) {
    std::string ip_file_path = (std::string)argv[1];
    if (ip_file_path.find("ip_filter.tsv") == std::string::npos) {
        return -1;
    }
    
    // parse
    std::ifstream file_stream(ip_file_path);
    std::vector<std::vector<std::string> > ip_container;
    if (file_stream.is_open()) {
        std::string ip;
        // int extra1, extra2;
        // if (addressesFile.ignore(numeric_limits<streamsize>::max(), addressesFile.widen('\n'))){
        while (file_stream >> ip) {
            file_stream.ignore(std::numeric_limits<std::streamsize>::max(), file_stream.widen('\n'));
            ip_container.push_back(split(ip, '.'));
        }
    }
    
    // print parsed data
    // std::cout << "--------------------" << std::endl;
    // std::cout << "Input Data" << std::endl << "Total Count: " << ip_container.size() << std::endl;
    // for (auto iterator = ip_container.begin(); iterator != ip_container.end(); ++iterator) {
    //     for (auto ip_iterator = iterator->begin(); ip_iterator != iterator->end(); ++ip_iterator) {
    //         std::cout << *ip_iterator;
    //         if (ip_iterator != --iterator->end()) {
    //             std::cout << ".";
    //         }
    //     }
    //     std::cout << std::endl;
    // }
    
    // perform general sort in the way of fullfill the 'ordered' map
    
    for (auto it = ip_container.begin(); it != ip_container.end(); ++it) {
        // configure readable ip address
        auto ip_formatter = [](std::string partial_result, std::string item) {
            return partial_result + (!partial_result.empty() ? "." : "") + item;
        };
        std::string ip_string = std::reduce(it->begin(), it->end(), std::string(), ip_formatter);
        
        // create normalized ip key
        uint index = 4; // starting index = power from 4 for algorithm convenience down to 0
        auto ip_normalizer = [&index](uint partial_result, std::string item) {
            uint ip_part = uint(std::stoul(item));
            index--;
            return partial_result + int(pow(256.0, index)) * ip_part;
        };
        uint normalized_ip = std::reduce(it->begin(), it->end(), 0, ip_normalizer);
        
        general_sorted_ips.insert({normalized_ip, ip_address(ip_string)});
        // auto result = general_sorted_ips.insert({normalized_ip, ip_string});
        // if (!result.second) {
        //     std::cout << "wow wow" << ip_string << ":" << normalized_ip << std::endl;
        // }
        // std::cout << "wow wow" << ip_string << ":" << normalized_ip << std::endl;
    }
    return 0;
}

void perform_task_one(std::multimap<uint, ip_address, std::greater<uint>> &general_sorted_ips) {
    // std::cout << "--------------------" << std::endl;
    // std::cout << "Task #1 General Sorted Data:" << std::endl << "Total Count: " << general_sorted_ips.size() << std::endl;
    for (auto it = general_sorted_ips.begin(); it != general_sorted_ips.end(); ++ it) {
        // std::cout << it->first << "\t" << it->second.string_representation << std::endl;
        std::cout << it->second.string_representation << std::endl;
    }
}

void perform_task_two(std::multimap<uint, ip_address, std::greater<uint>> &general_sorted_ips) {
    // std::cout << "--------------------" << std::endl;
    // std::cout << "Task #2 First Octet == 1:" << std::endl;
    
    std::multimap<uint, ip_address, std::greater<uint>> task_two_ips;
    auto octet_one_filter = [](std::pair<uint, ip_address> ip_address_pair) {
        return ip_address_pair.second.octets.at(0) == 1;
    };
    std::copy_if(
                 general_sorted_ips.begin(),
                 general_sorted_ips.end(),
                 std::inserter(task_two_ips, task_two_ips.end()),
                 octet_one_filter
                 );
    for (auto it = task_two_ips.begin(); it != task_two_ips.end(); ++ it) {
        // std::cout << it->first << "\t" << it->second.string_representation << std::endl;
        std::cout << it->second.string_representation << std::endl;
    }
    // std::cout << "Total Count: " << task_two_ips.size() << std::endl;
}

void perform_task_three(std::multimap<uint, ip_address, std::greater<uint>> &general_sorted_ips) {
    // std::cout << "--------------------" << std::endl;
    // std::cout << "Task #3 First Octet == 46, Second Octet == 70:" << std::endl;
    
    std::multimap<uint, ip_address, std::greater<uint>> task_three_ips;
    auto octet_46_70_filter = [](std::pair<uint, ip_address> ip_address_pair) {
        return ip_address_pair.second.octets.at(0) == 46 &&
        ip_address_pair.second.octets.at(1) == 70;
    };
    std::copy_if(
                 general_sorted_ips.begin(),
                 general_sorted_ips.end(),
                 std::inserter(task_three_ips, task_three_ips.end()),
                 octet_46_70_filter
                 );
    for (auto it = task_three_ips.begin(); it != task_three_ips.end(); ++ it) {
        // std::cout << it->first << "\t" << it->second.string_representation << std::endl;
        std::cout << it->second.string_representation << std::endl;
    }
    // std::cout << "Total Count: " << task_three_ips.size() << std::endl;
}

void perform_task_four(std::multimap<uint, ip_address, std::greater<uint>> &general_sorted_ips) {
    // std::cout << "--------------------" << std::endl;
    // std::cout << "Task #4 Any Octet == 46:" << std::endl;
    
    std::multimap<uint, ip_address, std::greater<uint>> task_four_ips;
    auto octet_46_70_filter = [](std::pair<uint, ip_address> ip_address_pair) {
        return ip_address_pair.second.octets.at(0) == 46 ||
        ip_address_pair.second.octets.at(1) == 46 ||
        ip_address_pair.second.octets.at(2) == 46 ||
        ip_address_pair.second.octets.at(3) == 46;
    };
    std::copy_if(
                 general_sorted_ips.begin(),
                 general_sorted_ips.end(),
                 std::inserter(task_four_ips, task_four_ips.end()),
                 octet_46_70_filter
                 );
    for (auto it = task_four_ips.begin(); it != task_four_ips.end(); ++ it) {
        // std::cout << it->first << "\t" << it->second.string_representation << std::endl;
        std::cout << it->second.string_representation << std::endl;
    }
    // std::cout << "Total Count: " << task_four_ips.size() << std::endl;
}
