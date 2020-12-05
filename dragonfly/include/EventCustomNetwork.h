///
/// A "custom" event over the network.
///

#ifndef __EVENT_CUSTOM_NETWORK_H__
#define __EVENT_CUSTOM_NETWORK_H__

// Engine includes.
#include "EventNetwork.h"

namespace df {

const std::string NETWORK_CUSTOM_EVENT = "df-custom-network";

class EventCustomNetwork : public EventNetwork {

 private:
  const void *m_p_message;

 public:

  // Constructor (with label).
  EventCustomNetwork(Network::Label label);
  
  // Set message.
  void setMessage(const void *new_message);

  // Get message.
  const void *getMessage() const;
};

} // end of namespace df
#endif // __EVENT_CUSTOM_H_NETWORK__
