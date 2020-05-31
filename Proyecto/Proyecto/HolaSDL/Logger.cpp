#include "Logger.h"



unique_ptr<Logger> Logger::instance_ = nullptr;

Logger::Logger(string log)
{
	//abrir el archivo en modo txt
	log_.open(log);
	//llamar worker para establecer una hebra
	worker_.start();

	path_ = log;
}


Logger::~Logger()
{
	log_.close();
}

void Logger::log(string info)
{
	//PROVSIONAL
	/*string p = path_;
	log_.close();

	worker_.execute([info, p]() {
		ofstream s(p);
		s << info << endl;
		s.close();
	});

	log_.open(path_);*/
	if (log_.is_open()) {

		worker_.execute([info, this]() {
			log_ << info << endl;
		});
	}
}

void Logger::log(std::function<string()> f)
{
	worker_.execute([f]() {cout << f() << endl; });
}





