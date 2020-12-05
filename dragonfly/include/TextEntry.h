///
/// A basic TextEntry
///
/// Invokes callback() when clicked.
/// Changes to highlight color on mouse over.
/// 

#ifndef __TEXTENTRY_H__
#define __TEXTENTRY_H__

// Engine includes.
#include "EventMouse.h"    
#include "ViewObject.h"

namespace df {

/// Count of number of text entry modified attribute categories.
const int TATTR_COUNT = 8;

/// Categories of text entry attributes that indicate modification.
enum TextEntryAttribute {
  ALL_TEXT,
  MODIFIED_TEXT,
  TEXT,
  LIMIT,
  CURSOR,
  CURSOR_CHAR,
  BLINK_RATE,
  NUMBERS_ONLY,
};

class TextEntry : public ViewObject {

 private:
  std::string m_text;             ///< Text entered.
  int m_limit;                    ///< Character limit in text.
  int m_cursor;			  ///< Cursor location.
  char m_cursor_char;             ///< Cursor character.
  int m_blink_rate;               ///< Cursor blink rate.
  bool m_numbers_only;            ///< True if only numbers.
  bool m_tmodified[TATTR_COUNT];  ///< Modified attribute since serialize().

 public:
  TextEntry();

  /// Set text entered.
  void setText(std::string new_text);

  /// Get text entered.
  std::string getText() const;

  /// Handle "keyboard" events.
  /// Return 0 if ignored, else 1.
  int eventHandler(const Event *p_e);

  /// Called when TextEntry enter hit.
  /// Must be defined by derived class.
  virtual void callback() = 0;

  /// Set limit of number of characters allowed.
  void setLimit(int new_limit);

  /// Get limit of number of characters allowed.
  int getLimit() const;

  /// Set cursor to location.
  void setCursor(int new_cursor);

  /// Get cursor location.
  int getCursor() const;

  /// Set blink rate for cursor (in ticks).
  void setBlinkRate(int new_blink_rate);

  /// Get blink rate for cursor (in ticks).
  int getBlinkRate() const;

  /// Return true if only numbers can be entered.
  bool numbersOnly() const;

  /// Set to allow only numbers to be entered.
  void setNumbersOnly(bool new_numbers_only = true);

  /// Set cursor character.
  void setCursorChar(char new_cursor_char);

  /// Get cursor character.
  char getCursorChar() const;

  /// Draw viewstring + text entered.
  virtual int draw();

  /// Serialize TextEntry attributes to single string.
  /// Can specify attribute to serialize (default "" means all modified).
  /// If attr is "ALL", serialize all attributes (modified or not).
  /// Clear m_tmodified[] array for attributes serialized.
  virtual std::string serialize(std::string attr="");

  /// Deserialize string to become attributes.
  /// Rerturn 0 if no errors, else -1.  
  virtual int deserialize(std::string s);

  /// Return true if attribute modified since last serialize.
  virtual bool isModified(enum TextEntryAttribute attribute) const;
  
  /// Return true if any attribute modified since last serialize.
  virtual bool isModified() const;
};

} // end of namespace df
#endif
