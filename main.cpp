#include <string>
#include <iostream>
#include <filesystem>
#include <vector>

std::string RemoveBeginning(std::string s)
{
	s = s.substr(3, s.size() - 3);
	return s;
}
int NumberOfDecimals(int number)
{
	int count = 0;
	while (number > 0)
	{
		number /= 10;
		++count;
	}
	return count;
}
std::string NumberAsString(int number, int decimals)
{
	std::string text = std::to_string(number);
	
	for (int text_size = text.size(); text_size < decimals; --decimals)
	{
		text = '0' + text;
	}
	return text;
}

int main()
{
	std::vector<std::string> file_names;

	for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(".//"))
	{
		if (!entry.is_directory())
		{
			std::string record = RemoveBeginning(entry.path().string());
			if (record != "EnumerateFiles.exe")
			{
				file_names.emplace_back(record);
			}
		}
	}

	int number_of_files = file_names.size();
	int number_of_decimals = NumberOfDecimals(number_of_files);

	for (int i = 0; i < number_of_files; ++i)
	{
		std::cout << file_names[i] <<'\n';
		if (std::rename(file_names[i].c_str(), (NumberAsString(i+1, number_of_decimals) + " - " + file_names[i]).c_str()))
		{
			std::cout << "Error";
		}
	}

	std::cin.get();
}