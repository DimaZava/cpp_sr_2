#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <numeric>
#include <cstdlib>
#include <algorithm>
#include <limits>
#include <cmath>
#include <string>
#include <sstream>

#define UNUSED(variable) (void)variable

class ip_address;

int perform_read_and_sort(const char **argv);
void prepare_data_vector(const char **argv, std::vector<ip_address> &general_sorted_ips_vector);
void perform_task_one_vector(const std::vector<ip_address> &general_sorted_ips_vector);
void perform_task_two_vector(const std::vector<ip_address> &general_sorted_ips_vector);
void perform_task_three_vector(const std::vector<ip_address> &general_sorted_ips_vector);
void perform_task_four_vector(const std::vector<ip_address> &general_sorted_ips_vector);

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

class ip_address
{
public:
    uint normalized_ip;
    std::string string_representation;
    std::vector<uint> octets;
    
    ip_address(std::vector<std::vector<std::string> >::iterator iterator) {
        // create normalized ip key
        uint index = 4; // starting index = power from 4 for algorithm convenience down to 0
        auto ip_normalizer = [&index](uint partial_result, std::string item) {
            uint ip_part = uint(std::stoul(item));
            index--;
            return partial_result + int(pow(256.0, index)) * ip_part;
        };
        this->normalized_ip = std::reduce(iterator->begin(), iterator->end(), 0, ip_normalizer);
        
        // configure readable ip address
        auto ip_formatter = [](std::string partial_result, std::string item) {
            return partial_result + (!partial_result.empty() ? "." : "") + item;
        };
        this->string_representation = std::reduce(iterator->begin(), iterator->end(), std::string(), ip_formatter);
        
        std::vector<std::string> string_vector = split(string_representation, '.');
        auto octets_formatter = [](std::string item) {
            return uint(std::stoul(item));
        };
        std::transform(string_vector.begin(), string_vector.end(), std::back_inserter(octets), octets_formatter);
    }
    
    friend std::ostream &operator<<(std::ostream &os, const ip_address &ip_address)
    {
        auto octets_formatter = [](std::string partial_result, uint item)
        {
            return partial_result + std::to_string(item);
        };
        
        os << "normalized_ip: " << ip_address.normalized_ip << std::endl
        << "string_representation: " << ip_address.string_representation << std::endl
        << "octets: " << std::reduce(ip_address.octets.begin(), ip_address.octets.end(), std::string(), octets_formatter) << std::endl;
        return os;
    }
};

static std::string logs;

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
    // logs.hash == 24e7a7b2270daee89c64d3ca5fb3da1a
    UNUSED(argc);
    return 0;
}

int perform_read_and_sort(const char **argv) {
    // read data
    std::vector<ip_address> general_sorted_ips_vector;
    
    prepare_data_vector(argv, general_sorted_ips_vector);
    perform_task_one_vector(general_sorted_ips_vector);
    perform_task_two_vector(general_sorted_ips_vector);
    perform_task_three_vector(general_sorted_ips_vector);
    perform_task_four_vector(general_sorted_ips_vector);
    return 0;
}

void prepare_data_vector(const char **argv, std::vector<ip_address> &general_sorted_ips_vector) {
    std::string ip_file_path = (std::string)argv[1];
    if (ip_file_path.find("ip_filter.tsv") == std::string::npos) {
        throw std::runtime_error("Error: Please, pass ip_filter.tsv file as parameter");
    }
    
    // parse
    std::ifstream file_stream(ip_file_path);
    std::vector<std::vector<std::string> > ip_container;
    if (file_stream.is_open()) {
        std::string ip;
        while (file_stream >> ip) {
            file_stream.ignore(std::numeric_limits<std::streamsize>::max(), file_stream.widen('\n'));
            ip_container.push_back(split(ip, '.'));
        }
    }
    
    // perform general sort in the way of fullfill the vector
    for (auto it = ip_container.begin(); it != ip_container.end(); ++it) {
        try
        {
            general_sorted_ips_vector.push_back(ip_address(it));
        }
        catch(const std::exception &e)
        {
            std::ostringstream errorStream;
            errorStream << "Error: " << std::string(e.what()) << std::endl <<
            "Errneous item at: " << std::to_string(it - ip_container.begin()) << std::endl;
            throw std::runtime_error(errorStream.str());
        }
    }
    
    auto comparator = [](const ip_address &lhs, const ip_address &rhs) -> bool {
        return lhs.normalized_ip > rhs.normalized_ip;
    };
    
    std::sort(general_sorted_ips_vector.begin(), general_sorted_ips_vector.end(), comparator);
}

void perform_task_one_vector(const std::vector<ip_address> &general_sorted_ips_vector) {
    // print parsed data
    for (auto element : general_sorted_ips_vector) {
        std::cout << element.string_representation << std::endl;
        logs.append(element.string_representation + '\n');
    }
}

void perform_task_two_vector(const std::vector<ip_address> &general_sorted_ips_vector) {
    std::vector<ip_address> task_two_ips_vector;
    auto octet_one_filter = [](ip_address ip_address) {
        return ip_address.octets.at(0) == 1;
    };
    std::copy_if(
                 general_sorted_ips_vector.begin(),
                 general_sorted_ips_vector.end(),
                 std::back_inserter(task_two_ips_vector),
                 octet_one_filter
                 );
    for (auto element : task_two_ips_vector) {
        std::cout << element.string_representation << std::endl;
        logs.append(element.string_representation + '\n');
    }
}

void perform_task_three_vector(const std::vector<ip_address> &general_sorted_ips_vector) {
    std::vector<ip_address> task_three_ips_vector;
    auto octet_46_70_filter = [](ip_address ip_address) {
        return ip_address.octets.at(0) == 46 && ip_address.octets.at(1) == 70;
    };
    std::copy_if(
                 general_sorted_ips_vector.begin(),
                 general_sorted_ips_vector.end(),
                 std::back_inserter(task_three_ips_vector),
                 octet_46_70_filter
                 );
    for (auto element : task_three_ips_vector) {
        std::cout << element.string_representation << std::endl;
        logs.append(element.string_representation + '\n');
    }
}

void perform_task_four_vector(const std::vector<ip_address> &general_sorted_ips_vector) {
    std::vector<ip_address> task_four_ips_vector;
    auto octet_46_70_filter = [](ip_address ip_address) {
        return ip_address.octets.at(0) == 46 ||
        ip_address.octets.at(1) == 46 ||
        ip_address.octets.at(2) == 46 ||
        ip_address.octets.at(3) == 46;
    };
    std::copy_if(
                 general_sorted_ips_vector.begin(),
                 general_sorted_ips_vector.end(),
                 std::back_inserter(task_four_ips_vector),
                 octet_46_70_filter
                 );
    for (auto element : task_four_ips_vector) {
        std::cout << element.string_representation << std::endl;
        logs.append(element.string_representation + '\n');
    }
}
