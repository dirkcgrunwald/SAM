#ifndef IDENTITY_HPP
#define IDENTITY_HPP

/**
 * Operator that does nothing to the input. 
 */

#include <iostream>
#include <map>

#include <sam/AbstractConsumer.hpp>
#include <sam/BaseComputation.hpp>
#include <sam/ExponentialHistogram.hpp>
#include <sam/Features.hpp>
#include <sam/Util.hpp>
#include <sam/FeatureProducer.hpp>

namespace sam {
/**
 * For each consumed input, simply grabs the attribute specified by
 * valueField.
 */
template <typename InputType, size_t valueField, size_t... keyFields> 
class Identity: public AbstractConsumer<InputType>, 
                public BaseComputation,
                public FeatureProducer
{
private:
  //TODO remove
  //int numPos = 0;
  //int numNeg = 0;

public:
  /**
   * Constructor.
   * \param nodeId The nodeId of the node that is running this operator.
   * \param featureMap The global featureMap that holds the features produced
   *                   by this operator.
   * \param identifier A unique identifier associated with this operator.
   */
  Identity(size_t nodeId,
           std::shared_ptr<FeatureMap> featureMap,
           std::string identifier) :
           BaseComputation(nodeId, featureMap, identifier) 
                                          
  {}

  bool consume(InputType const& input) {
    this->feedCount++;

    // Generates unique key from key fields
    std::string key = generateKey<keyFields...>(input);

    auto value = std::get<valueField>(input);

    SingleFeature feature(value);

    this->featureMap->updateInsert(key, this->identifier, feature);

    // This assumes the identifier of the tuple is the first element
    //if (value == 0) {
    //  numNeg++;
    //} else if (value == 1) {
    //  numPos++;
    //}
    //std::cout << toString(input) << std::endl;
    std::size_t id = std::get<0>(input);
    this->notifySubscribers(id, value);
    
    //std::cout << "numNeg, numPos " << numNeg << " " << numPos << std::endl;

    return true;
  }

  /// Nothing to do for terminate.
  void terminate() {}

};


}
#endif

