
/************************************************************************
* This program is free software: you can redistribute it and/or modify  *
* it under the terms of the GNU General Public License as published by  *
* the Free Software Foundation, either version 3 of the License, or     *
* (at your option) any later version.                                   *
*                                                                       *
* This program is distributed in the hope that it will be useful,       *
* but WITHOUT ANY WARRANTY; without even the implied warranty of        *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
* GNU General Public License for more details.                          *
*                                                                       *
* You should have received a copy of the GNU General Public License     *
* along with this program.  If not, see <http://www.gnu.org/licenses/>. *
************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <boost/algorithm/string.hpp> 

#define SEPARATORS       " \t"
#define COMMENTS         "#"

bool Belongs_to(char, std::string);
double Calculate_average(std::vector<std::vector<double>>, int);
double Calculate_stddev(std::vector<std::vector<double>>, int, double);
std::vector<std::vector<double>> Filter(std::vector<std::vector<double>>, int, double, double);
std::vector<std::vector<double>> Convert_to_double_vector(std::vector<std::vector<std::string>>);
std::vector<std::vector<std::string>> Parse_file(std::string, std::string, std::string);




int main(int argc, char*argv[]) {
  std::string filename;
  int col_number, filter_col_number;
  std::vector<double> min_values, max_values;


  filename = "prova.tab";
  col_number = 2;
  filter_col_number = 1;
  min_values = { 200.0, 250.0, 300.0, 350.0 };
  max_values = { 400.0, 400.0, 400.0, 400.0 };


  std::vector< std::vector<std::string> > parsed_file = Parse_file(filename, SEPARATORS, COMMENTS);
  std::vector< std::vector<double> > doubled_file = Convert_to_double_vector(parsed_file);
  if (col_number - 1 < 0 || col_number >= (int)doubled_file.at(0).size()) std::cout << "Colonna non valida" << std::endl, exit(2);
  if (filter_col_number >= (int)doubled_file.at(0).size()) std::cout << "Colonna filtro non valida" << std::endl, exit(3);

  double average_tot = Calculate_average(doubled_file, col_number - 1);
  double stddev_tot = Calculate_stddev(doubled_file, col_number - 1, average_tot);

  std::cout << "Righe tot: " << doubled_file.size() << ", colonne tot: " << doubled_file.at(0).size() << std::endl;
  std::cout << "Media tot: " << average_tot << ", dev.std. tot: " << stddev_tot << ", errore tot: " << stddev_tot / sqrt(doubled_file.size()) << std::endl;

  for (size_t i = 0; i < min_values.size(); i++) {
    std::cout << min_values[i] << ':' << max_values[i] << std::endl;
    std::vector< std::vector<double> > filtered_file;
    if (filter_col_number > 0) filtered_file = Filter(doubled_file, filter_col_number - 1, min_values[i], max_values[i]);
    else filtered_file = doubled_file;
    double average = Calculate_average(filtered_file, col_number - 1);
    double stddev = Calculate_stddev(filtered_file, col_number - 1, average);
    std::cout << "Righe selezionate: " << filtered_file.size() << std::endl;
    std::cout << "Media: " << average << ", dev.std.: " << stddev << ", errore: " << stddev / sqrt(filtered_file.size()) << std::endl;
    std::cout << std::endl;
  }

  return 0;
}


bool Belongs_to(char c, std::string s) {
  for (size_t i = 0; i < s.size(); i++) { if (c == s.at(i)) return true; }
  return false;
}


double Calculate_average(std::vector< std::vector<double> > doubled_file, int col_number) {
  double average = 0;
  for (auto &i : doubled_file) {
    average += i[col_number];
  }
  average /= (double)(doubled_file.size());
  return average;
}


double Calculate_stddev(std::vector< std::vector<double> > doubled_file, int col_number, double average) {
  double stddev = 0;
  for (auto &i : doubled_file) {
    stddev += (i[col_number] - average)*(i[col_number] - average);
  }
  stddev /= (double)(doubled_file.size() - 1.0);
  stddev = sqrt(stddev);
  return stddev;
}


std::vector< std::vector<double> > Filter(std::vector< std::vector<double> > doubled_file, int col_number, double min_value, double max_value) {
  std::vector< std::vector<double> > filtered_file;
  for (auto i : doubled_file) if (i.at(col_number) >= min_value && i.at(col_number) <= max_value) filtered_file.push_back(i);
  return filtered_file;
}


std::vector< std::vector<double> > Convert_to_double_vector(std::vector< std::vector<std::string> > parsed_file) {
  std::vector<double> doubled_line;
  std::vector< std::vector<double> > doubled_file;

  for (auto &i : parsed_file) {
    doubled_line.clear();
    doubled_line.resize(i.size());
    for (size_t j = 0; j < i.size(); j++) doubled_line[j] = atof(i[j].c_str());
    doubled_file.push_back(doubled_line);
  }
  return doubled_file;
}


std::vector< std::vector<std::string> > Parse_file(std::string file_name, std::string separators, std::string comment) {
  // Safe file opening
  std::ifstream file_to_parse(file_name, std::ios::in);
  if (!file_to_parse) {
    std::cout << "Cannot open " << file_name << ". Quitting..." << std::endl;
    exit(12);
  }
  // Internal variables
  std::string line;
  std::vector<std::string> tokens;
  std::vector< std::vector<std::string> > parsed;
  while (getline(file_to_parse, line)) {
    boost::algorithm::trim(line);  // remove leading/trailing spaces
    if (Belongs_to(line[0], comment) || !line.size()) continue;
    boost::algorithm::split(tokens, line, boost::algorithm::is_any_of(separators), boost::token_compress_on);
    //std::transform(tokens[0].begin(), tokens[0].end(), tokens[0].begin(), ::tolower);
    for (size_t i = 0; i < tokens.size(); i++) {  // remove inline comments
      if (Belongs_to(tokens[i][0], comment)) { tokens.erase(tokens.begin() + i, tokens.end()); }
    }
    if (tokens.size()) {
      parsed.push_back(tokens);
    }
    line.clear(); tokens.clear();
  }
  file_to_parse.close();
  return parsed;
}


