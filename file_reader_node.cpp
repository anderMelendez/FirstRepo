
#include <rclcpp/rclcpp.hpp>
#include <ament_index_cpp/get_package_share_directory.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

class FileReaderNode : public rclcpp::Node
{
public:
    FileReaderNode() : Node("file_reader_node")
    {
        try
        {
            // Locate the package share directory
            std::string package_share_dir = ament_index_cpp::get_package_share_directory("my_package");

            // Build the path to the data file
            std::string file_path = package_share_dir + "/data/example.txt";

            // Try to open the file
            std::ifstream file(file_path);
            if (!file.is_open())
            {
                RCLCPP_ERROR(this->get_logger(), "Could not open file: %s", file_path.c_str());
                return;
            }

            // Read the file content
            std::stringstream buffer;
            buffer << file.rdbuf();
            file.close();

            // Log the content
            RCLCPP_INFO(this->get_logger(), "File content:\n%s", buffer.str().c_str());
        }
        catch (const std::exception &e)
        {
            RCLCPP_ERROR(this->get_logger(), "Exception: %s", e.what());
        }
    }
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<FileReaderNode>();
    rclcpp::spin_some(node); // Run briefly to log output
    rclcpp::shutdown();
    return 0;
}

