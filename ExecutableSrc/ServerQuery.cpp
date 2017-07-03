/*
 * Servers.cpp
 * This does the server query as described in Disclosure.
 *
 *  Created on: March 15, 2017
 *      Author: elgood
 */

#include <string>
#include <vector>
#include <list>
#include <stdlib.h>
#include <iostream>
#include <chrono>

#include <boost/program_options.hpp>

#include <mlpack/core.hpp>
#include <mlpack/methods/naive_bayes/naive_bayes_classifier.hpp>

#include "ReadSocket.h"
#include "ReadCSV.hpp"
#include "ZeroMQPushPull.h"
#include "TopK.hpp"
#include "Expression.hpp"
#include "Filter.hpp"
#include "Netflow.hpp"
#include "Learning.hpp"

#define DEBUG 1

using std::string;
using std::vector;
using std::cout;
using std::endl;

namespace po = boost::program_options;

using namespace sam;
using namespace std::chrono;
using namespace mlpack;
using namespace mlpack::naive_bayes;

void createPipeline(std::shared_ptr<ZeroMQPushPull> consumer,
                 FeatureMap& featureMap,
                 int nodeId)
{
    vector<size_t> keyFields;
    keyFields.push_back(6);
    int valueField = 8;
    string identifier = "top2";
    int k = 2;
    int N = 10000;
    int b = 1000;
    auto topk = std::make_shared<TopK<size_t, Netflow, 
                                 DestPort, DestIp>>(
                                 N, b, k, nodeId,
                                 featureMap, identifier);
    consumer->registerConsumer(topk); 

    // Five tokens for the 
    // First function token
    int index1 = 0;
    auto function1 = [&index1](Feature const * feature)->double {
      auto topKFeature = static_cast<TopKFeature const *>(feature);
      return topKFeature->getFrequencies()[index1];    
    };
    auto funcToken1 = std::make_shared<FuncToken<Netflow>>(featureMap, 
                                                      function1, identifier);

    // Addition token
    auto addOper = std::make_shared<AddOperator<Netflow>>(featureMap);

    // Second function token
    int index2 = 0;
    auto function2 = [&index2](Feature const * feature)->double {
      auto topKFeature = static_cast<TopKFeature const *>(feature);
      return topKFeature->getFrequencies()[index2];    
    };

    auto funcToken2 = std::make_shared<FuncToken<Netflow>>(featureMap, 
                                                      function2, identifier);

    // Lessthan token
    auto lessThanToken =std::make_shared<LessThanOperator<Netflow>>(featureMap);
    
    // Number token
    auto numberToken = std::make_shared<NumberToken<Netflow>>(featureMap, 0.9);

    auto infixList = std::make_shared<std::list<std::shared_ptr<
                      ExpressionToken<Netflow>>>>();
    infixList->push_back(funcToken1);
    infixList->push_back(addOper);
    infixList->push_back(funcToken2);
    infixList->push_back(lessThanToken);
    infixList->push_back(numberToken);

    auto filterExpression = std::make_shared<Expression<Netflow>>(*infixList);
     
    int queueLength = 1000; 
    auto filter = std::make_shared<Filter<Netflow, DestIp>>(
      *filterExpression, nodeId, featureMap, "servers", queueLength);
    consumer->registerConsumer(filter);

}

int main(int argc, char** argv) {

#ifdef DEBUG
  cout << "DEBUG: At the beginning of main" << endl;
#endif

  // The ip to read the nc data from.
  string ip;

  // The port to read the nc data from.
  int ncPort;

  // The number of nodes in the cluster
  int numNodes;

  // The node id of this node
  int nodeId;

  // The prefix to the nodes
  string prefix;

  // The starting port number
  int startingPort;

  // The high-water mark
  long hwm;

  // The total number of elements in a sliding window
  int N;

  // The number of elements in a dormant or active window
  int b;

  int nop; //not used

  // The file location of labeled instances. 
  string learnfile;

  time_t timestamp_sec1, timestamp_sec2;

  // The training data if learning the classifier
  arma::mat trainingData;

  // The location of where model should be saved to loaded from
  string modelfile;

  // The model that can be trained from example data or if a trained model
  // exists, can be loaded from the filesystem.
  NBCModel model;

  po::options_description desc("Allowed options");
  desc.add_options()
    ("help", "help message")
    ("ip", po::value<string>(&ip)->default_value("localhost"), 
      "The ip to receive the data from nc")
    ("ncPort", po::value<int>(&ncPort)->default_value(9999), 
      "The port to receive the data from nc")
    ("numNodes", po::value<int>(&numNodes)->default_value(1), 
      "The number of nodes involved in the computation")
    ("nodeId", po::value<int>(&nodeId)->default_value(0), 
      "The node id of this node")
    ("prefix", po::value<string>(&prefix)->default_value("node"), 
      "The prefix common to all nodes")
    ("startingPort", po::value<int>(&startingPort)->default_value(10000), 
      "The starting port for the zeromq communications")
    ("hwm", po::value<long>(&hwm)->default_value(10000), 
      "The high water mark (how many items can queue up before we start "
      "dropping)")
    ("nop", po::value<int>(&nop)->default_value(1),
      "The number of simultaneous operators")
    ("learn", po::value<string>(&learnfile)->default_value(""),
      "The location of labeled instances to learn from.  If supplied, a\n"
      "model will be trained based on the features generated by the pipeline")
    ("model", po::value<string>(&modelfile)->default_value(""),
      "The location of where the model should be saved to or loaded from.")
  ;

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << desc << std::endl;
    return 1;
  }

  vector<string> hostnames(numNodes);
  vector<int> ports(numNodes);

  if (numNodes == 1) {
    hostnames[0] = "127.0.0.1";
    ports[0] = startingPort;
  } else {
    for (int i = 0; i < numNodes; i++) {
      hostnames[i] = prefix + boost::lexical_cast<string>(i);
      ports[i] = (startingPort + i);  
    }
  }

  // Creating the ZeroMQPushPull consumer.  This consumer is responsible for
  // getting the data from the receiver (e.g. a socket or a file) and then
  // publishing it in a load-balanced way to the cluster.
  int queueLength = 1000;
  auto consumer = std::make_shared<ZeroMQPushPull>(queueLength,
                                 numNodes, 
                                 nodeId, 
                                 hostnames, 
                                 ports, 
                                 hwm);

  // The global featureMap (global for all features generated for this node,
  // each node has it's own featuremap.
  FeatureMap featureMap;

  /********************** Learning ******************************/
  if (learnfile != "") {
    // The true parameter transposes the data.  In mlpack, rows are features 
    // and columns are observations, which makes things confusing.
    //data::Load(learnfile, trainingData, true);

    //arma::Row<size_t> labels;

    //data::NormalizeLabels(trainingData.row(trainingData.n_rows - 1), labels,
    //                      model.mappings);
    // Remove the label row
    //trainingData.shed_row(trainingData.n_rows - 1);

    ReadCSV receiver(learnfile);
    receiver.registerConsumer(consumer);    

    createPipeline(consumer, featureMap, nodeId);

    if (!receiver.connect()) {
      std::cout << "Problems opening file " << learnfile << std::endl;
      return -1;
    }

    //Timer::Start("nbc_training");
    //model.nbc = NaiveBayesClassifier<>(trainingData, labels,
    //  model.mappings.n_elem, true);
    //Timer::Stop("nbc_training");

    //if (modelfile != "") {
    //  data::Save(modelfile, "model", model);
    //}
  }
  /********************* Running pipeline *************************/ 
  else 
  {

    if (modelfile != "") {
      //load model
    }

    ReadSocket receiver(ip, ncPort);
    receiver.registerConsumer(consumer);

    createPipeline(consumer, featureMap, nodeId);

    if (!receiver.connect()) {
      std::cout << "Couldn't connected to " << ip << ":" << ncPort << std::endl;
      return -1;
    }

    milliseconds ms1 = duration_cast<milliseconds>(
      system_clock::now().time_since_epoch()
    );
    receiver.receive();
    milliseconds ms2 = duration_cast<milliseconds>(
      system_clock::now().time_since_epoch()
    );
    std::cout << "Seconds for Node" << nodeId << ": "  
      << static_cast<double>(ms2.count() - ms1.count()) / 1000 << std::endl;
  }
}

