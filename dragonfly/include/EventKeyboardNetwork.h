///
/// A "keyboard" event over the network.
/// 

#ifndef __EVENT_KEYBOARD_NETWORK_H__
#define __EVENT_KEYBOARD_NETWORK_H__

// Engine includes.
#include "EventKeyboard.h"

namespace df {

const std::string NETWORK_KEYBOARD_EVENT = "df-keyboard-network";

class EventKeyboardNetwork : public EventKeyboard {

 private:
  int m_socket_index;	       // Socket index of connection.

 public:
  EventKeyboardNetwork();

  // Set socket index.
  void setSocketIndex(int new_socket_index);

  // Get socket index.
  int getSocketIndex() const;
};

} // end of namespace df
#endif // __EVENT_KEYBOARD_NETWORK_H__
