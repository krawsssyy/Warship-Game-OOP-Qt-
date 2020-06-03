#pragma once
#include "MyException.h"
#include "IElem.h"
#include <vector>
#include <string>
#include <fstream>

const std::string config_PATH = "C:\\Users\\Alex\\Desktop\\fac\\an1\\sem2\\oop\\lab12-14game\\gui\\lab12game\\config.cfg";

const int N = 10;
const int k = 1;
const int p = 1;
const int q = 1;

class Repository {
private:
	std::vector<IE*> m_elems;
public:
	Repository();
	~Repository();
    //how to make this function spit out global const int s
    void parseConfig() {
         std::ifstream f(config_PATH);
         if(f.is_open()) {
            int N = 0, k = 0, p = 0, q = 0;
             bool tableOk = false;
             bool warOk = false;
             bool yaOk = false;
             bool subOk = false;
             std::string line;
             while(std::getline(f, line)) {
                 size_t pos = line.find("=");
                 std::string key = line.substr(0, pos);
                 line.erase(0, pos + 1);
                 if(key == "table_size" && tableOk == false){
                     int val = std::stoi(line);
                     tableOk = true;
                     N = val;

                 }
                 if(key == "warship_count" && warOk == false) {
                     int val = std::stoi(line);
                     warOk = true;
                     k = val;

                 }
                 if(key == "yacht_count" && yaOk == false) {
                     int val = std::stoi(line);
                     yaOk = true;
                     p = val;

                 }
                 if(key == "sub_count" && subOk == false) {
                     int val = std::stoi(line);
                     subOk = true;
                     q = val;

                 }
             }
             f.close();
             if(!tableOk || !warOk || !yaOk || !subOk)
                 throw Exc("Wrong configuration in the config file!");
             if(!N || !k || !p || !q)
                 throw Exc("Invalid values in configuration file!");
             if(N > 26 || k > 3 || p > 3 || q > 3)
                 throw Exc("Invalid values in configuration file!");
             //some return statement
         }
         else
             throw Exc("Unable to open config file!");
     }
    //
	void addElem(IE* elem);
	int getSize();
	std::vector<IE*> getAll();
	void clearRepo();

};





