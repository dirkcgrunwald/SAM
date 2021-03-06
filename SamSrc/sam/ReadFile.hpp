/*
 * ReadFile.h
 *
 *  Created on: Nov 7, 2017
 *      Author: elgood
 */

#ifndef READFILE_HPP
#define READFILE_HPP

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fstream>

#include <sam/BaseProducer.hpp>
#include <sam/VastNetflow.hpp>
#include <sam/AbstractDataSource.hpp>

#define BUFFER_SIZE 256

namespace sam {

class ReadFile : public BaseProducer<std::string>, public AbstractDataSource
{
private:
	int readCount;
	std::string previous;
  int metricInterval = 100000;
  std::ifstream myfile;
  std::string filename;

public:
	ReadFile(std::string filename) :
  BaseProducer(1) 
  {
    this->filename = filename;  
    readCount = 0;
  }
	virtual ~ReadFile() {};

	bool connect();
  void receive();
};


bool ReadFile::connect()
{
  myfile.open(filename);

	return true;
}

void ReadFile::receive()
{
  int i = 0;
  std::string line;
  while(std::getline(myfile, line)) {
    for (auto consumer : consumers) {
      consumer->consume(line);
    }
    i++;
    if (i % metricInterval == 0) {
      std::cout << "ReadFile received " << i << std::endl;
    }
  }
}


}

#endif /* READFILE_HPP */
