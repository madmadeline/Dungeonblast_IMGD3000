///
/// NetworkNode.h 
///
/// Handle incoming network messages.
///

#ifndef __NETWORK_NODE_H__
#define __NETWORK_NODE_H__

// Engine includes.
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventNetwork.h"
#include "Object.h"

namespace df {

// Network message types.
enum MessageType {
  UNDEFINED_MESSAGE=-1,
  SYNC_OBJECT,    // Create or update object, as appropriate.
  DELETE_OBJECT,  // Delete object.
  SET_GAME_OVER,  // Set game over in GM.
  KEYBOARD_INPUT, // Keyboard event.
  MOUSE_INPUT,    // Mouse event.
  CUSTOM_MESSAGE, // Game code defined.
};

// HEADER:
// 0) Total size is an int (total number of bytes in message).
// 1) Message type is an int (an enum).

// SYNC_OBJECT:
// 2) Object id as int.
// 3) String length as int.
// 4) Object type as string.
// 5) Serialized Object data (string of bytes).

// DELETE_OBJECT:
// 2) Object id as int.

// SET_GAME_OVER:
// (nothing)

// KEYBOARD:
// 2) Keyboard action as int (a EventKeyboardAction enum).
// 3) Key as int (a Keyboard::Key enum).

// MOUSE:
// 2) Mouse action as int (a EventMouseAction enum).
// 3) Mouse button as int (a Mouse::Button enum).
// 4) Mouse-x as float.
// 5) Mouse-y as float.

// CUSTOM:
// 2) Bytes as blob.

class NetworkNode : public Object {

 protected:
  char *m_p_buff;   // Data buffer for network communication.
  int m_buff_size;  // Number of bytes allocated.
  
 public:
  NetworkNode();
  ~NetworkNode();

  /// Handle network event.
  /// Return 1 if handled, else 0 if ignored.
  virtual int eventHandler(const Event *p_e);

  /// Handle connect network event (base class does nothing).
  /// Return 1 if handled, else 0 if ignored.
  virtual int handleConnect(const EventNetwork *p_e);

  /// Handle accept network event (base class does nothing).
  /// Return 1 if handled, else 0 if ignored.
  virtual int handleAccept(const EventNetwork *p_e);

  /// Handle data network event using data in m_p_buff.  
  /// Return 1 if handled, else 0 if ignored.
  virtual int handleData(const EventNetwork *p_e);

  /// Send message (supporting various message types).
  /// Send message from Server to Client.
  /// SET_GAME_OVER
  /// Return 1 if something sent, 0 if nothing sent, -1 if error.
  int sendMessage(MessageType msg_type, int sock_index=-1);

  /// Send message from Server to Client.
  /// SYNC_OBJECT or DELETE_OBJECT
  /// Synchronize attr, passed to serialize().
  /// Return 1 if something sent, 0 if nothing sent, -1 if error.
  int sendMessage(MessageType msg_type, Object *p_obj,
		  std::string attr="", int sock_index=-1);

  /// Send message from Client to Server.
  /// KEYBOARD_INPUT
  /// Return 1 if something sent, 0 if nothing sent, -1 if error.
  int sendMessage(MessageType msg_type, EventKeyboardAction action,
		  Keyboard::Key key, int sock_index=-1);

  /// Send message from Client to Server.
  /// MOUSE_INPUT
  /// Return 1 if something sent, 0 if nothing sent, -1 if error.
  int sendMessage(MessageType msg_type, EventMouseAction action,
		  Mouse::Button button, Vector mouse_position,
		  int sock_index=-1);

  /// Send message from Client to Server.
  /// CUSTOM_MESSAGE
  /// Return 1 if something sent, 0 if nothing sent, -1 if error.
  int sendMessage(MessageType msg_type, int num_bytes, const void *bytes, 
		  int sock_index=-1);

  /// Create Object of given type.
  /// Return pointer to Object.
  virtual Object *createObject(std::string object_type);
  
 private:

  /// Increase size of network message buffer (if needed).
  /// Return 0 if ok, else -1 if error.
  int sizeBuffer(int msg_size);

  /// Prepare message buffer and header.
  /// Return 0 if ok, else -1 if error.
  int prepMessageHeader(MessageType msg_type, int msg_size);
};

} // end of namespace df

#endif // __NETWORK_NODE_H__
