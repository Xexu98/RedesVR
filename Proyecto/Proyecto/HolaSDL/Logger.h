#include <string>
#include "Worker.h"

#include <iostream>
#include <fstream>



#pragma once

using namespace std;

class Logger
{
	//hide copyBuilder and 	assignment operator
	Logger(Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	static unique_ptr<Logger> instance_; //ptr instance class

public:
	
	Logger(string log);
	~Logger();

	

	//init singletton class
	inline static void initInstance(string filename){
		if (instance_.get() == nullptr) {
			instance_.reset(new Logger(filename));
		}
	}
	//get singletton class
	inline static Logger* getInstance() {	
		//SDL_assert(instance_.get() != nullptr); //lanza una mensaje con la primera llamada a getInstance.
		return instance_.get();
	}

	void log(string info);
	void log(std::function<string()> f);

	//...
private:
	
	Worker worker_; //management threads class
	ofstream log_; 
	string path_;
	
};


