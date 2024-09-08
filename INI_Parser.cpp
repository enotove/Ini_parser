#include <iostream>
#include <fstream>
#include <string>
class Ini_parser
{
private:
    std::string letter;
    

    
public:
    Ini_parser(const std::string& adress)
    {
        std::string string;
        std::ifstream file(adress);
        if (file.is_open())
        {
            while (!file.eof())
            {
                std::getline(file, string);
                letter += string + ' ';
            }
            
            file.close();
        }
        else
        {
            throw std::exception("Not found file");
            return;
        }
       
    }

    template<typename T>
    T get_value(std::string string)
    {
        std::string section = "[" + string.substr(0, string.find(".")) + "]";
        std::string parameter = string.substr(string.find(".")+1, string.size()-1) + "=";
        if (letter.find(section) == std::string::npos)
        {
            throw std::exception("Not found this section");
        }
        
        size_t index_section = letter.find(section) + section.size();
        std::string section_text = letter.substr(index_section, letter.find("[", index_section) - index_section);
        //std::cout << section_text << std::endl;
        if (section_text.find(parameter) == std::string::npos)
        {
            throw std::exception("Not found this parameter in section");
        }
        size_t index_parameter = section_text.find(parameter) + parameter.size();
        std::string value = section_text.substr(index_parameter, section_text.find(' ', index_parameter) - index_parameter);
        T result = std::stoi(value);
        return result;  
    }
    template<>
    std::string get_value(std::string string)
    {
        std::string section = "[" + string.substr(0, string.find(".")) + "]";
        std::string parameter = string.substr(string.find(".") + 1, string.size() - 1) + "=";
        if (letter.find(section) == std::string::npos)
        {

            throw std::exception("Not found this section");
        }

        size_t index_section = letter.find(section) + section.size();
        std::string section_text = letter.substr(index_section, letter.find("[", index_section) - index_section);
        //std::cout << section_text << std::endl;
        if (section_text.find(parameter) == std::string::npos)
        {
            throw std::exception("Not found this parameter in section");
        }
        size_t index_parameter = section_text.find(parameter) + parameter.size();
        std::string value = section_text.substr(index_parameter, section_text.find(' ', index_parameter) - index_parameter);
        return value;
    }
};

int main()
{
    try {
        Ini_parser pars("pars.txt");
        auto value = pars.get_value<std::string>("Section3.var1");
        std::cout << value << std::endl;
    }
    catch (std::exception ex)
    {
        std::cout << ex.what() << std::endl;
    }
    
}