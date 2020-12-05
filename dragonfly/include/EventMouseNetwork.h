///
/// A "mouse" event over the network.
///

#ifndef __EVENT_MOUSE_NETWORK_H__
#define __EVENT_MOUSE_NETWORK_H__

// Engine includes.
#include "EventMouse.h"

namespace df {

const std::string NETWORK_MSE_EVENT = "df-mouse-network";

class EventMouseNetwork : public EventMouse {

 private:
  int m_socket_index;	       // Socket index of connection.

 public:
  EventMouseNetwork();

  // Set socket index.
  void setSocketIndex(int new_socket_index);

  // Get socket index.
  int getSocketIndex() const;
};

} // end of namespace df
#endif // __EVENT_MOUSE_H_NETWORK__
